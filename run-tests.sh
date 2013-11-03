#!/bin/bash

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

# install_zeromq_php_extension
#
# Installs the ØMQ PHP extension.
#
# Parameters: ~
build_and_run_tests() {
    local zeromq_version=$1
    local php_zmq_version=$2
    pear package
    tar xfz zmq-${php_zmq_version}.tgz
    cd zmq-${php_zmq_version}
    phpize
    ./configure --with-zmq="${HOME}/zeromq-${zeromq_version}"
    make
    php run-tests.php -d extension=zmq.so -d extension_dir=modules -n ./tests/*.phpt
    exit_code=$?

    for i in `ls tests/*.out 2>/dev/null`; do echo "-- START ${i}"; cat $i; echo ""; echo "-- END"; done
    return $exit_code
}

export NO_INTERACTION=1
export REPORT_EXIT_STATUS=1
export TEST_PHP_EXECUTABLE=`which php`

PHP_ZMQ_VERSION=$(php -r '$sxe = simplexml_load_file ("package.xml"); echo (string) $sxe->version->release;')
ZEROMQ_VERSION=$1

install_zeromq $ZEROMQ_VERSION
build_and_run_tests $ZEROMQ_VERSION $PHP_ZMQ_VERSION
