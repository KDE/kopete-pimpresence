#! /usr/bin/env bash
$EXTRACTRC `find . -name \*.ui >> rc.cpp
$XGETTEXT `find . -name \*.cpp` rc.cpp -o $podir/kcm_kopete_pimpresence.pot
rm -f rc.cpp
