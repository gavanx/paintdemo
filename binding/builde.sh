#!/usr/bin/env bash

node-gyp rebuild --target=1.4.1 --arch=x64 --dist-url=https://atom.io/download/atom-shell
cp ./build/Release/demo.node brush.node