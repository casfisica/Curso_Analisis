#!/bin/bash

./produccion-1.sh Signal.txt -Ne=100000 -Q=30 -Xq=50 -Run=10 -Pyt -Delp
./produccion-1.sh BackGround-tW.txt -Ne=100000 -Q=30 -Xq=50 -Run=2 -Pyt -Delp
./produccion-1.sh BackGround-WW.txt -Ne=100000 -Q=30 -Xq=50 -Run=2 -Pyt -Delp
./produccion-1.sh BackGround-DY_2j.txt -Ne=100000 -Q=30 -Xq=50 -mm2l=50 -Run=2 -Pyt -Delp
