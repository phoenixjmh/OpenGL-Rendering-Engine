#!/usr/bin/env sh

konsole -e "/bin/bash -c 'cd out/build && cmake -S ../../ && make && gdb ./StagR -ex 'n' -ex 'run' '"
