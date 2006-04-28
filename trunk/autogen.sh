#!/bin/sh

echo 'Generating necessary files...'
aclocal
#automake --gnu --add-missing -Wall
automake --gnu --add-missing
#autoconf -Wall
autoconf
