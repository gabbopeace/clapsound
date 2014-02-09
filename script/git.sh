#!/bin/bash

cd `pwd`;

if [[ "$1" -ne "" ]]
then
cd $1;
fi;

echo `pwd`;

git add .;

d=$(date);

git commit -m "$d";


