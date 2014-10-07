#!/bin/bash


# Installs the specified version of ØMQ.
#
# Parameters:
#
#     1 - The version of ØMQ to install, in the form "vx.y.z"
#     2 - The directory to install ØMQ to
install_zeromq() {
    local zeromq_version=$1
    local zeromq_dir=$2

    if test ! -d "/tmp/php-zmq-travis-support"
    then
        git clone https://github.com/phuedx/php-zmq-travis-support /tmp/php-zmq-travis-support
    fi

    if test -d "/tmp/php-zmq-travis-support/zeromq/zeromq-${zeromq_version}"
    then
        ln -s "/tmp/php-zmq-travis-support/zeromq/zeromq-${zeromq_version}" $zeromq_dir

        return
    fi

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
    cd ..
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

zeromq_version=$1

# NOTE (phuedx, 2014/07/07): This must be kept in sync with the configure
# command used to build ØMQ in phuedx/php-zmq-travis-support.
zeromq_dir=/tmp/zeromq

build_dir=/tmp/build

install_zeromq $zeromq_version $zeromq_dir
init_build_dir $build_dir

make_test $build_dir $zeromq_dir
