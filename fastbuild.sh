#!/bin/csh

setenv VITASDK /usr/local/vitasdk
setenv PATH /usr/local/vitasdk/bin:$PATH
perl -i -pe 's/\b(\d+)(?=\D*$)/$1+1/e' ./src/version.h
cmake ./
make
cat ./src/version.h
printf "\n"
#cmake -DCMAKE_BUILD_TYPE=Debug ./




