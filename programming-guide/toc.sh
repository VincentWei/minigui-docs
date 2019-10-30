#!/bin/bash

for FILE in MiniGUIProgGuide*.md
do
    gawk -f generate_toc.awk $FILE > tmp.md
    sed -i '/^# /r tmp.md' $FILE
done

