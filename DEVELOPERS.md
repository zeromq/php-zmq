## Build Instructions
Run the following commands

```shell
phpize && ./configure
make
make test
```

see also http://wiki.zeromq.org/bindings:php

## Auto Generation

### Sockopts
The ZMQ Lib functionality depends mostly on the sockopt flags which can be
set on libzmq. In order to keep these flags in sync with the upstream
library the flags can be automatically pulled by a script.

To do this you will need to install the gsl library, see also https://github.com/imatix/gsl

```shell
git clone https://github.com/imatix/gsl
cd gsl/src
make
sudo make install
```

Then run from the project root directory `./options/generate.sh` to update
the sockopts.

### api.php generation

The api definition can be auto generated by the tool DocThor.
Note: This requires to build the extension first and specify on the command
line.

```shell
git clone https://github.com/SegFaulty/DocThor
php DocThor/DocThor.php --sourceDir=./ zmq
php -d extension=modules/zmq.so DocThor.php --sourceDir=./ zmq
```