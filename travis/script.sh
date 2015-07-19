#!/bin/bash

LIBSODIUM_VERSION="1.0.3"
CZMQ_VERSION="v2.2.0"

LIBSODIUM_DIR="${TRAVIS_BUILD_DIR}/travis/cache/libsodium/v${LIBSODIUM_VERSION}"
CZMQ_DIR="${TRAVIS_BUILD_DIR}/travis/cache/czmq/${CZMQ_VERSION}"

# Installs libsodium.
install_libsodium() {
    local cache_dir=$LIBSODIUM_DIR

    if test -d $cache_dir
    then
        return
    fi

    pushd /tmp

    git clone https://github.com/jedisct1/libsodium
    cd libsodium
    git checkout "tags/${LIBSODIUM_VERSION}"
    ./autogen.sh
    ./configure --prefix=$cache_dir
    make -j 8
    make install
    cd ..

    popd # pushd /tmp
}

# Installs the specified version of ØMQ.
#
# Parameters:
#
#     1 - The version of ØMQ to install, in the form "vx.y.z"
install_zeromq() {
    local version=$1
    local cache_dir="${TRAVIS_BUILD_DIR}/travis/cache/zeromq/${version}"
    local with_libsodium=""

    if test -d $cache_dir
    then
        return
    fi

    pushd /tmp

    case $version in
    v2.2.0)
        wget http://download.zeromq.org/zeromq-2.2.0.tar.gz
        tar -xf zeromq-2.2.0.tar.gz
        cd zeromq-2.2.0
        ;;
    v3*)
        git clone https://github.com/zeromq/zeromq3-x
        cd zeromq3-x
        git checkout "tags/${version}"
        ;;
    v4*)
        git clone https://github.com/zeromq/zeromq4-x
        cd zeromq4-x
        git checkout "tags/${version}"

        with_libsodium="--with-libsodium=${LIBSODIUM_DIR}"
        ;;
    esac
    ./autogen.sh
    ./configure --prefix=$cache_dir $with_libsodium
    make -j 8
    make install
    cd ..

    popd # pushd /tmp
}

# Installs CZMQ.
#
# Parameters:
#
#     1 - The version of ØMQ that was installed
install_czmq() {
  local zeromq_version=$1
  local zeromq_dir="${TRAVIS_BUILD_DIR}/travis/cache/zeromq/${zeromq_version}"
  local cache_dir=$CZMQ_DIR

  if test -d $cache_dir
  then
      return
  fi

  pushd /tmp

  git clone https://github.com/zeromq/czmq
  cd czmq
  git checkout "tags/${CZMQ_VERSION}"
  ./autogen.sh
  ./configure \
    --prefix=$cache_dir \
    --with-libzmq=$zeromq_dir \
    --with-libsodium=$LIBSODIUM_DIR
  make -j 8
  make install
  cd ..

  popd # pushd /tmp
}


# Ensures that the build directory exists and contains the extension and its
# tests by packaging and then extracting it to the build directory.
#
# Parameters:
#
#     1 - The build directory
init_build_dir() {
    local build_dir=$1
    local php_zmq_version=$(php -r '$element = simplexml_load_file("package.xml"); echo (string) $element->version->release;')

    pear package
    tar xfz "zmq-${php_zmq_version}.tgz" -C /tmp

    ln -s "/tmp/zmq-${php_zmq_version}" $build_dir
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
    local build_dir=$1
    local zeromq_version=$2
    local zeromq_dir="${TRAVIS_BUILD_DIR}/travis/cache/zeromq/${zeromq_version}"
    local with_czmq=$3
    local with_czmq_option=""

    if [ "x${with_czmq}" = "xtrue" ]
    then
        with_czmq_option="--with-czmq=${CZMQ_DIR}"
    fi

    pushd $build_dir

    phpize
    ./configure --with-zmq=$zeromq_dir $with_czmq_option
    make

    if test ! -e modules/zmq.so
    then
        printf "PHP extension build failed\n"
        exit 1
    fi

    NO_INTERACTION=1 \
    REPORT_EXIT_STATUS=1 \
    TEST_PHP_EXECUTABLE=$(which php) \
    php run-tests.php -d extension=modules/zmq.so -n tests/*.phpt

    local run_tests_exit_code=$?

    for failed_test in $(ls tests/*.out 2>/dev/null); do
        echo "-- START ${failed_test}"
        cat $failed_test
        echo ""
        echo "-- END"
    done

    popd # pushd $build_dir

    return $run_tests_exit_code
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

zeromq_version=$1
with_czmq=$2
build_dir=/tmp/build

install_libsodium
install_zeromq $zeromq_version

if [ "x${with_czmq}" = "xtrue" ]
then
    install_czmq $zeromq_version
fi

init_build_dir $build_dir
make_test $build_dir $zeromq_version $with_czmq
