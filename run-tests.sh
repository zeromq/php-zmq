wget http://download.zeromq.org/zeromq-2.2.0.tar.gz
tar -xf zeromq-2.2.0.tar.gz
cd ./zeromq-2.2.0
./autogen.sh
./configure --prefix=/tmp/zeromq-2.2.0
make install
cd ..
phpize
./configure --with-zmq=/tmp/zeromq-2.2.0
export NO_INTERACTION=1
export REPORT_EXIT_STATUS=1
# See https://github.com/reeze/php-leveldb/blob/master/travis/run-test.sh
export TEST_PHP_EXECUTABLE=`which php`
export USE_ZEND_ALLOC=0
php run-tests.php -d=modules/zmq.so -m tests/*.phpt
