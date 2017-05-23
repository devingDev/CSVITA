#!/bin/sh

setenv VITASDK /usr/local/vitasdk
setenv PATH /usr/local/vitasdk/bin:$PATH

perl -i -pe 's/\b(\d+)(?=\D*$)/$1+1/e' ./src/version.h

cmake clean ./
make clean

sh mycleanscript.sh

cmake ./
#cmake -DCMAKE_BUILD_TYPE=Debug ./
make


cat ./src/version.h

printf "\n"
