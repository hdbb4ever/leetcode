#!/bin/bash

# this is one simply script to formalize the pasted content from 
# leetcode website tag selected form

file=$1
if [[ ! -e $file ]]; then
  echo "$file doesn't exist!" && exit 0;
fi
#filename=`expr "$file" : '\(.*\)\.txt'`
filename=${file%.txt}

random=`date '+%d%m%s'` 
awk '{if(NR%3==1) print $0}' $file > ${random}_no.txt
awk '{if(NR%3==2) print $0}' $file > ${random}_name.txt
paste ${random}_no.txt ${random}_name.txt > ${filename}_gen.txt
rm ${random}_no.txt ${random}_name.txt
