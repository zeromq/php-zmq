#!/bin/bash

BUILD_DIR="/tmp"

CACHE_DIR="$1"
LIBZMQ_VERSION=$2

BUILD_LIBSODIUM="no"
LIBSODIUM_VERSION="no"

if test "x$3" != "x"; then
    BUILD_LIBSODIUM="yes"
    LIBSODIUM_VERSION=$3
fi

BUILD_CZMQ="no"
CZMQ_VERSION="no"

if test "x$4" != "x"; then
    BUILD_CZMQ="yes"
    CZMQ_VERSION=$4
fi

php -r 'die(PHP_ZTS ? 0 : 1);'
if test $? = 0
then
    BUILD_PTHREADS="yes"
else
    BUILD_PTHREADS="no"
fi

LIBSODIUM_PREFIX="${CACHE_DIR}/libsodium-${LIBSODIUM_VERSION}"
LIBZMQ_PREFIX="${CACHE_DIR}/libzmq-${LIBZMQ_VERSION}-libsodium-${LIBSODIUM_VERSION}"
CZMQ_PREFIX="${CACHE_DIR}/czmq-${CZMQ_VERSION}-libzmq-${LIBZMQ_VERSION}-libsodium-${LIBSODIUM_VERSION}"

# Installs libsodium.
install_libsodium() {
    local version=$1
    local build_dir="${BUILD_DIR}/libsodium-build"

    if test -d "${LIBSODIUM_PREFIX}"
    then
        echo "Using cached libsodium in ${LIBSODIUM_PREFIX}"
        return
    fi

    if test -d "${build_dir}"
    then
        rm -rf "${build_dir}"
    fi

    git clone https://github.com/jedisct1/libsodium "${build_dir}"

    pushd "${build_dir}"
        git checkout "tags/${version}"
        ./autogen.sh
        ./configure --prefix="${LIBSODIUM_PREFIX}"
        make -j 8
        make install

    popd # pushd "${build_dir}"
}

# Installs the specified version of ØMQ.
#
# Parameters:
#
#     1 - The version of ØMQ to install, in the form "vx.y.z"
install_zeromq() {
    local version=$1
    local build_dir="${BUILD_DIR}/libzmq-build"

    if test -d "${LIBZMQ_PREFIX}"
    then
        echo "Using cached libzmq in ${LIBZMQ_PREFIX}"
        return
    fi

    local repo_name=""

    case $version in
    2*)
        repo_name="zeromq2-x"
        ;;
    3*)
        repo_name="zeromq3-x"
        ;;
    4.1*)
        repo_name="zeromq4-1"
        ;;
    4*)
        repo_name="zeromq4-x"
        ;;
    master)
        repo_name="libzmq"
        ;;
    esac

    if test -d "${build_dir}"
    then
        rm -rf "${build_dir}"
    fi

    git clone "https://github.com/zeromq/${repo_name}" "${build_dir}"

    pushd "${build_dir}"
        if test "x${version}" != "xmaster"
        then
            git checkout "tags/v${version}"
        fi

        ./autogen.sh
        if test $BUILD_LIBSODIUM = "yes"
        then
            PKG_CONFIG_PATH="${LIBSODIUM_PREFIX}/lib/pkgconfig" ./configure --prefix="${LIBZMQ_PREFIX}" --with-libsodium="${LIBSODIUM_PREFIX}"
        else
            ./configure --prefix="${LIBZMQ_PREFIX}" --without-libsodium
        fi
        make -j 8
        make install
    popd
}

# Installs CZMQ.
#
# Parameters:
#
#     1 - The version of ØMQ that was installed
install_czmq() {
    local version=$1
    local build_dir="${BUILD_DIR}/czmq-build"

    if test -d "${CZMQ_PREFIX}"
    then
        echo "Using cached czmq in ${CZMQ_PREFIX}"
        return
    fi

    if test -d "${build_dir}"
    then
        rm -rf "${build_dir}"
    fi

    git clone https://github.com/zeromq/czmq "${build_dir}"

    pushd "${build_dir}"
        if test "x${version}" != "xmaster"
        then
            git checkout "tags/v${version}"
        fi

        ./autogen.sh

        if test $BUILD_LIBSODIUM = "yes"
        then
            PKG_CONFIG_PATH="${LIBSODIUM_PREFIX}/lib/pkgconfig" ./configure --prefix="${CZMQ_PREFIX}" --with-libzmq="${LIBZMQ_PREFIX}" --with-libsodium="${LIBSODIUM_PREFIX}"
        else
            ./configure --prefix="${CZMQ_PREFIX}" --with-libzmq="${LIBZMQ_PREFIX}" --without-libsodium
        fi

        make -j 8
        make install
    popd
}


# Ensures that the build directory exists and contains the extension and its
# tests by packaging and then extracting it to the build directory.
#
# Parameters:
#
#     1 - The build directory
init_build_dir() {
    local build_dir="${BUILD_DIR}/php-zmq-build"
    local php_zmq_version=$(php -r '$element = simplexml_load_file("package.xml"); echo (string) $element->version->release;')

    pear package
    tar xfz "zmq-${php_zmq_version}.tgz" -C "${BUILD_DIR}"

    if test -L "${build_dir}"
    then
        rm "${build_dir}"
    fi
    ln -s "${BUILD_DIR}/zmq-${php_zmq_version}" "${build_dir}"
}


# Build the extension and run its tests in the specified directory.
#
# If one or more of the tests fail, then their output is displayed after the
# test runner (`run-tests.php`) exits.
#
# Parameters:
#
#     1 - The directory of the extension and its tests
#     2 - The version of ØMQ to build the extension against
#     2 - Whether or not to build the extension with CZMQ support
#
# Returns: the exit code of the test runner
make_test() {
    local build_dir="${BUILD_DIR}/php-zmq-build"

    pushd "${build_dir}"

        local pthreads_flag=""

        if test "${BUILD_PTHREADS}" = "yes"
        then
            pecl install pthreads
            pthreads_flag="extension=pthreads.so"
        fi

        phpize
        if test "$BUILD_CZMQ" = "yes"
        then
            ./configure --with-zmq="${LIBZMQ_PREFIX}" --with-czmq="${CZMQ_PREFIX}"
        else
            ./configure --with-zmq="${LIBZMQ_PREFIX}"
        fi
        make

        if test ! -e modules/zmq.so
        then
            printf "PHP extension build failed\n"
            exit 1
        fi

        NO_INTERACTION=1 \
        REPORT_EXIT_STATUS=1 \
        TEST_PHP_EXECUTABLE=$(which php) \
        php run-tests.php -d extension=modules/zmq.so -d ${pthreads_flag} -n tests/*.phpt

        local run_tests_exit_code=$?
        print_failed_tests

    popd # pushd $build_dir

    return $run_tests_exit_code
}

print_failed_tests() {
    local build_dir="${BUILD_DIR}/php-zmq-build"

    for test in $(ls "${build_dir}/tests/"*.phpt 2>/dev/null); do

        local name="${test%.*}"

        if test -f "${name}.out"
        then
            echo "-- START ${name}.out"
            cat "${name}.out"
            echo ""
            echo "-- END ${name}.out"
            echo ""
            echo "--- START ${name}.diff"
            cat "${name}.diff"
            echo "---"
            echo "-- END ${name}.diff"
            echo ""
        fi
    done
}

# First, ensure that all of the tests are included in the PEAR package
# definition file. If they aren't, then abort immediately, as the result of the
# build is inaccurate.
for test_file in tests/*.phpt; do
    grep $(basename $test_file) package.xml >/dev/null

    if test $? != 0
    then
        echo "ERROR: ${test_file} isn't in the PEAR package definition file"
        exit 1
    fi
done

echo "OPTS: LIBZMQ_VERSION=$LIBZMQ_VERSION BUILD_LIBSODIUM=$BUILD_LIBSODIUM BUILD_CZMQ=$BUILD_CZMQ BUILD_PTHREADS=$BUILD_PTHREADS"

if test $BUILD_LIBSODIUM = "yes"
then
    install_libsodium $LIBSODIUM_VERSION
fi

install_zeromq $LIBZMQ_VERSION

if test $BUILD_CZMQ = "yes"
then
    install_czmq $CZMQ_VERSION
fi

init_build_dir $build_dir
make_test $build_dir $zeromq_version $with_czmq
