#!/bin/sh

echo 'Generating necessary files...'
aclocal
libtoolize --automake
autoheader -Wall
automake --gnu --add-missing -Wall
autoconf -Wall
