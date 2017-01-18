#!/bin/bash

#Lanzo el Trabajo
./produccion-1.sh Signal.txt -Ne=50000 -Q=30 -Xq=50 -Run=20 -Pyt -Delp &
#Envía un correo cuando termina
#echo "The job Signal is done" | mutt -s "The Job is done Signal is done" camilo@gfif.udea.edu.co
./produccion-1.sh BackGround-tW.txt -Ne=50000 -Q=30 -Xq=50 -Run=4 -Pyt -Delp &
#echo "The job BackGround-tW is done" | mutt -s "The Job is done BackGround-tW is done" camilo@gfif.udea.edu.co
./produccion-1.sh BackGround-WW.txt -Ne=50000 -Q=30 -Xq=50 -Run=4 -Pyt -Delp &
#echo "The job BackGround-WW is done" | mutt -s "The Job is done BackGround-WW is done" camilo@gfif.udea.edu.co
./produccion-1.sh BackGround-DY_2j.txt -Ne=50000 -Q=30 -Xq=50 -mm2l=50 -Run=4 -Pyt -Delp &
#echo "The job BackGround-DY_2j is done" | mutt -s "The Job BackGround-DY_2j is done" camilo@gfif.udea.edu.co
