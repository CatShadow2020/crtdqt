#!/bin/bash

osname=`uname -s | tr "[A-Z]" "[a-z]"`
osver=`uname -r | sed 's/-RELEASE//'`
machine=`uname -m`

if [ "$osname" = "darwin" ]
then
        ostype=SVR4
fi

platform="$osname.$osver.$machine"

export OSNAME=`echo $osname | tr "[a-z]" "[A-Z]"`
export PLATFORM="$platform"
export MACHINE="$machine"
export OSTYPE="$ostype"

echo $OSNAME
echo $PLATFORM
echo $MACHINE
echo $OSTYPE
