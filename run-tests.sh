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
    esac
    ./autogen.sh
    ./configure
    make
    sudo make install
    cd ..
}

# install_zeromq_php_extension
#
# Installs the ØMQ PHP extension.
#
# Parameters: ~
install_zeromq_php_extension() {
    phpize
    ./configure
    make
    sudo make install
    echo "extension=zmq.so" >> ~/.phpenv/versions/$(phpenv version-name)/etc/php.ini
}

# run_zeromq_extension_tests
#
# Runs the ØMQ PHP extension tests and /returns the exit code/.
#
# Parameters: ~
run_zeromq_extension_tests() {
    export NO_INTERACTION=1
    export REPORT_EXIT_STATUS=1
    export TEST_PHP_EXECUTABLE=`which php`
    export USE_ZEND_ALLOC=0
    php run-tests.php ./tests/*.phpt
}

ZEROMQ_VERSION=$1
install_zeromq $ZEROMQ_VERSION
install_zeromq_php_extension
run_zeromq_extension_tests
