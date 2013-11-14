#!/bin/bash

#
# Arguments given to the script
#
if test "x$1" = "x"; then
    echo "The script requires zeromq version as an argument"
    exit 1
fi

ZEROMQ_VERSION=$1

#
# Some globals
#
export NO_INTERACTION=1
export REPORT_EXIT_STATUS=1
export TEST_PHP_EXECUTABLE=`which php`
export PHP_ZMQ_VERSION=$(php -r '$sxe = simplexml_load_file ("package.xml"); echo (string) $sxe->version->release;')
export BUILD_ROOT=/tmp/zmq-tmp-build


# install_zeromq
#
# Installs the specified version of ØMQ.
#
# Parameters:
#
#     1 - The version of ØMQ to install, in the form "vx.y.z"
install_zeromq() {
    local zeromq_version=$1
    case $zeromq_version in
    v2.2.0)
        wget http://download.zeromq.org/zeromq-2.2.0.tar.gz
        tar -xf zeromq-2.2.0.tar.gz
        cd ./zeromq-2.2.0
        ;;
    v3*)
        git clone https://github.com/zeromq/zeromq3-x
        cd ./zeromq3-x
        git checkout tags/$zeromq_version
        ;;
    v4*)
        git clone https://github.com/zeromq/zeromq4-x
        cd ./zeromq4-x
        git checkout tags/$zeromq_version
        ;;
    esac
    ./autogen.sh
    ./configure --prefix="${HOME}/zeromq-${zeromq_version}"
    make -j 8
    sudo make install
    cd ..
}

#
# Validate the pear package to ensure all tests have been package
#
check_pear_package_xml ()
{
    for file in tests/*.phpt; do
        grep $(basename $file) package.xml >/dev/null
        if [ $? != 0 ]; then
            echo "Missing file $file from package.xml"
            exit 1
        fi
    done
}


# install_zeromq_php_extension
#
# Installs the ØMQ PHP extension.
#
# Parameters: ~
build_and_run_tests() {
    local zeromq_version=$1

    pear package

    mkdir "$BUILD_ROOT"
    tar xfz zmq-${PHP_ZMQ_VERSION}.tgz -C "$BUILD_ROOT"

    # Do the build in pear packaged dir
    pushd "${BUILD_ROOT}/zmq-${PHP_ZMQ_VERSION}"
        phpize
        ./configure --with-zmq="${HOME}/zeromq-${zeromq_version}"
        make
        php run-tests.php -d extension=zmq.so -d extension_dir=modules -n ./tests/*.phpt
        exit_code=$?

        for failed_test in `ls tests/*.out 2>/dev/null`; do
            echo "-- START ${failed_test}"
            cat $failed_test
            echo ""
            echo "-- END"
        done
    popd
    return $exit_code
}

check_pear_package_xml
install_zeromq $ZEROMQ_VERSION
build_and_run_tests "$ZEROMQ_VERSION"
