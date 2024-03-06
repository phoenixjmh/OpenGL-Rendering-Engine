#!/usr/bin/env sh

cd out/build
cmake -S ../../
make
mv compile_commands.json ../../
./StagR
