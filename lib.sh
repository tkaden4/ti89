#!/bin/bash

LIB_NAME=TILink
ARDUINO_LIB=~/Arduino/libraries/$LIB_NAME

mkdir -p $ARDUINO_LIB

rm -f $ARDUINO_LIB/*

cp ./programs/libs/TILink.* $ARDUINO_LIB/
mv $ARDUINO_LIB/TILink.c $ARDUINO_LIB/TILink.cpp
