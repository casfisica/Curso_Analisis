#!/bin/bash

fecha=$(date +"%d-%m-%y_%T")

#Esto es con la modificación en .bashrc
## export MadGrapgSYS=/home/camilo/MG-Pythia/MG5_aMC_v2_5_1/
## export PATH=$PATH:$MadGrapgSYS/bin

function Error {
    echo ""
    echo "usage:" $0 "<path/script> [path/output] [NEvent]"
    echo ""
    echo ""
    echo ""
    exit 0
}

if [ -z $1 ]; then #Para fijarse que el argumento no esté vacio
    echo "No path to the MadGraph script supplied (1st argument)"
    Error
else
    if [ ! -f $1 ]; then #Si existe el fichero , -w: si tiene permisos de escritura, -x: si tiene permisos de ejecucución
	echo "The path:" $1 "is empty"
	Error
	exit 0
    fi
    PathScript=$1
fi

DefaultOutput=$(sed -e '/output/ !d' $PathScript) #mira si en el script hay una carpeta de salida
arrOUT=(${DefaultOutput// / }) #parte el texto en DefaultOutput por los espacios

if [ -z $2 ]; then #mira si el argumento 2 de la función está vacio
    if [ -z "${arrOUT[1]}" ]; then #si no hay una salida en el escript, usa una por defecto
	
	if [ ! -d ~/Default_output_MG ]; then #Si no existe el directorio lo crea
	    mkdir ~/Default_output_MG
	fi
	PathOutput="~/Default_output_MG/$fecha"
	if [ -z "${arrOUT[0]}" ]; then
	    echo "output" $PathOutput >> $PathScript #Pone en la última línea del script el output por defecto
	fi
    else
	PathOutput=${arrOUT[1]} #si hay un output en el script y no se dió uno como argumento, entonces usa el del script
    fi
else
    PathOutput=$2 #Si se dió un output como argumento, este será el usado.
fi

echo $PathScript
echo $PathOutput
#cat $PathScript

rm $PathScript.tmp 2> /dev/null
cp $PathScript $PathScript.tmp
rm $PathScript 2> /dev/null
cat $PathScript.tmp | sed '/output/c\output '$PathOutput' ' > $PathScript 
rm $PathScript.tmp 2> /dev/null

mg5_aMC $PathScript

cd $PathOutput
./bin/generate_events -f
cd -

#cat sigmaplotter3.f | sed '/!Marca para cambiar con bash/c\       flagzp = '$i' !Marca para cambiar con bash'>> sigmaplotter.f
#sed 's/Gerardo Gutierrez Gutierrez/'"$participante"'/' ./TEMPLATES/participante_$Template.svg > ./TMP/acceptance_letter_tmp_$name.svg
