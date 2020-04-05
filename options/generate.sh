#!/bin/sh

WGET=$(which wget)
GSL=$(which gsl)
GIT=$(which git)

cd `dirname "$0"`

if test "$WGET" = ""
then
    echo "wget not found"
    exit 1
fi

if test "$GSL" = ""
then
    echo "gsl not found"
    exit 1
fi

if test "$GIT" = ""
then
    echo "git not found"
    exit 1
fi

# latest version supported
# $WGET https://raw.githubusercontent.com/zeromq/czmq/v4.0.0/src/sockopts.xml -O sockopts.xml

# not yet working
$WGET https://raw.githubusercontent.com/zeromq/czmq/master/src/sockopts.xml -O sockopts.xml

git diff sockopts.xml

$GSL -script:sockopts.gsl sockopts.xml
$GSL -script:sockopts_test.gsl sockopts.xml
