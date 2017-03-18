#!/usr/bin/env bash

rm -rf Frothleikr/
git clone https://github.com/AustinHaugerud/Frothleikr

rm -rf build/

mkdir build/

cd build/

cmake ..

make
