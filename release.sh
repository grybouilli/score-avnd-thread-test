#!/bin/bash
rm -rf release
mkdir -p release

cp -rf ThreadTest *.{hpp,cpp,txt,json} LICENSE release/

mv release score-addon-threadtest
7z a score-addon-threadtest.zip score-addon-threadtest
