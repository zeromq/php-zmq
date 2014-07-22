#!/bin/bash

# NOTE (phuedx, 2014/07/07): This must be kept in sync with the prefix used in
# configure command used to build ØMQ in phuedx/php-zmq-travis-support.
zeromq_dir=/tmp/zeromq
czmq_dir=/tmp/czmq
zyre_dir=/tmp/zyre
#

build_dir=/tmp/build
binary_repository_local_path=/tmp/php-zmq-travis-support
binary_repository_git_url=https://github.com/phuedx/php-zmq-travis-support

# Clone a repository with prebuild version of zmq, czmq, and zyre.
init_binary_repo() {
    if test ! -d "$binary_repository_local_path"
    then
        git clone $binary_repository_git_url $binary_repository_local_path
    fi
}

# Installs the specified version of ØMQ.
#
# Parameters:
#
#     1 - The version of ØMQ to install, in the form "vx.y.z"
#     2 - The directory to install ØMQ to
install_zeromq() {
    local zeromq_version=$1
    local zeromq_dir=$2

    # Try to install from precompiled
    if test -d "$binary_repository_local_path/zeromq/zeromq-${zeromq_version}"
    then
        ln -sv "$binary_repository_local_path/zeromq/zeromq-${zeromq_version}" $zeromq_dir
        sudo ldconfig
        return
    fi

    # Install from source
    case $zeromq_version in
    v2.2.0)
        wget http://download.zeromq.org/zeromq-2.2.0.tar.gz
        tar -xf zeromq-2.2.0.tar.gz
        cd zeromq-2.2.0
        ;;
    v3*)
        git clone https://github.com/zeromq/zeromq3-x
        cd zeromq3-x
        git checkout "tags/${zeromq_version}"
        ;;
    v4*)
        git clone https://github.com/zeromq/zeromq4-x
        cd zeromq4-x
        git checkout "tags/${zeromq_version}"
        ;;
    esac
    ./autogen.sh
    ./configure --prefix=$zeromq_dir
    make -j 8
    sudo make install
    sudo ldconfig
    cd ..
}

# Installs czmq
#
# Parameters:
#
#     1 - The version of CZMQ to install, in the form "x.y.z"
#     2 - The directory to install CZMQ to
install_czmq() {
    local czmq_version=$1
    local czmq_dir=$2
    
    # Try to install from precompiled
    if test -d "$binary_repository_local_path/czmq/czmq-${czmq_version}"
    then
        ln -sv "$binary_repository_local_path/czmq/czmq-${czmq_version}" $czmq_dir
        sudo ldconfig
        return
    fi
    
    # Install from source
    printf "CZMQ install from source not supported, yet\n"
    exit 1
}

# Installs zyre
#
# Parameters:
#
#     1 - The version of CZMQ to install, in the form "x.y.z"
#     2 - The directory to install CZMQ to
install_zyre() {
    local zyre_version=$1
    local zyre_dir=$2
    
    # Try to install from precompiled
    if test -d "$binary_repository_local_path/zyre/zyre-${zyre_version}"
    then
        ln -sv "$binary_repository_local_path/zyre/zyre-${zyre_version}" $zyre_dir
        sudo ldconfig
        return
    fi
    
    # Install from source
    printf "Zyre install from source not supported, yet\n"
    exit 1
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

    ln -sv "/tmp/zmq-${php_zmq_version}" $build_dir
}


# Build the extension and run its tests in the specified directory.
#
# If one or more of the tests fail, then their output is displayed after the
# test runner (`run-tests.php`) exits.
#
# Parameters:
#
#     1 - The directory of the extension and its tests
#     2 - The directory of the ØMQ library
#
# Returns: the exit code of the test runner
make_test() {
    local build_dir=$1
    local zeromq_dir=$2

    pushd $build_dir

    phpize
    ./configure --with-zmq="$zeromq_dir"
    make

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

# Get precompiled libs to speedup install
init_binary_repo

zeromq_version=$1
install_zeromq $zeromq_version $zeromq_dir

if test "$#" -ge 2
then
    czmq_version=$2
    install_czmq $czmq_version $czmq_dir
fi

if test "$#" -ge 3
then
    zyre_version=$3
    install_zyre $zyre_version $zyre_dir
fi

init_build_dir $build_dir
make_test $build_dir $zeromq_dir
