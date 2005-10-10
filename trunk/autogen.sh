#!/bin/sh

echo 'Generating necessary files...'
aclocal
libtoolize --automake
#autoheader -Wall
autoheader
#automake --gnu --add-missing -Wall
automake --gnu --add-missing
#autoconf -Wall
autoconf
