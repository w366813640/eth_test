#!/bin/bash

#./mcastclient 226.1.1.1 4321 172.16.41.147

hname=`hostname`

if [ $hname = "ibmx3650tom" ]; then
    echo $hname
    ./mcastclient 226.1.1.1 4321 192.168.10.11
fi
if [ $hname = "ibmx3650jerry" ]; then
    echo $hname
    ./mcastclient 226.1.1.1 4321 192.168.10.12
fi
if [ $hname = "net612" ]; then
    echo $hname
    ./mcastclient 226.1.1.1 4321 192.168.10.13
fi
if [ $hname = "hp" ]; then
    echo $hname
    ./mcastclient 226.1.1.1 4321 192.168.10.14
fi
