#! /bin/bash

for file in models/*.txt
do
mv -v "$file" "${file%.txt}.obj"
done;
