wget http://download.zeromq.org/zeromq-2.2.0.tar.gz
tar -xf zeromq-2.2.0.tar.gz
cd ./zeromq-2.2.0
./autogen.sh
./configure
make
sudo make install
cd ..
phpize
./configure
make
sudo make install
echo "extension=zmq.so" >> ~/.phpenv/versions/$(phpenv version-name)/etc/php.ini
export NO_INTERACTION=1
export REPORT_EXIT_STATUS=1
export TEST_PHP_EXECUTABLE=`which php`
export USE_ZEND_ALLOC=0
php run-tests.php ./tests/*.phpt
