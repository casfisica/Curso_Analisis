#!/bin/bash

fecha=$(date +"%d-%m-%y_%T")

#Esto es con la modificación en .bashrc
## export MadGrapgSYS=/home/camilo/MG-Pythia/MG5_aMC_v2_5_1/
## export PATH=$PATH:$MadGrapgSYS/bin

###########################################################################
# 				FLAGS	          		          #
###########################################################################
flagOut=True




##############################END FLAGS####################################

function Error {
    echo ""
    echo "usage:" $0 "<path/script> [-Ph=path/output] [-Ne=Nevents]"
    echo ""
    echo "Nevents: number of events, 10000=default"
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

#mira si en el script hay una carpeta de salida
DefaultOutput=$(sed -e '/output/ !d' $PathScript)
#parte el texto en DefaultOutput por los espacios
arrOUT=(${DefaultOutput// / })

##############################################################################
#                            OPCIONES POR DEFECTO                            #
##############################################################################

Nevents=10000                                   #Numero de eventos por defecto
DefaultOutDir="~/Default_output_MG/$fecha"         #Salida por defecto


###########################END OPCIONES POR DEFECTO###########################

#Lee las opciones desde linea de comandos

for var in "$@" #Corre sobre todos los argumentos
do
    while IFS='=' read Opc Val; do #separa por = los argumentos
    
	
	if [ "$Opc" = -Ne ]; then
	    if [ -z "$Val" ]; then
		echo "-Ne is empty, using the default Ne=10000"		
	    else
		Nevents=$Val
	    fi
	fi
	
	if [ "$Opc" = -Ph ]; then  
	    if [ -z "$Val" ]; then #mira si el argumento -Ph de la función está vacio
		echo "Ph empty, using default or script path"
		flagOut=True
      	    else
		PathOutput=$Val #Si se dió un output como argumento, este será el usado.
		flagOut=False
	    fi
	fi
	
	
    done <<< "$var"

done #Fin for para OPCIONES




#Establece la salida
if [ "$flagOut" = True ]; then
    DefaultOutput=$(sed -e '/output/ !d' $PathScript) #mira si en el script hay una carpeta de salida
    arrOUT=(${DefaultOutput// / }) #parte el texto en DefaultOutput por los espacios  
    if [ -z "${arrOUT[1]}" ]; then #si no hay una salida en el escript, usa una por defecto
	PathOutput=$DefaultOutdir
	if [ -z "${arrOUT[0]}" ]; then
	    echo "output" $PathOutput >> $PathScript #Pone en la última línea del script el output por defecto
	fi
    else
	PathOutput=${arrOUT[1]} #si hay un output en el script y no se dió uno como argumento, entonces usa el del script  
    fi
fi



#echo $Nevents
#echo $PathScript
#echo $PathOutput



cat $PathScript | sed '/output/c\output '$PathOutput' ' > $PathScript.tmp 
cp $PathScript.tmp $PathScript
rm $PathScript.tmp 2> /dev/null

mg5_aMC $PathScript #Creo la carpeta que contiene

#MODIFICO LA CONFIGURACION PARA QUE NO ABRA EL NAVEGADOR POR DEFECTO
eval "cat $PathOutput/Cards/me5_configuration.txt | sed '/# automatic_html_opening = True/c\automatic_html_opening = False'>> $PathOutput/Cards/me5_configuration.txt.tmp"
eval "cp $PathOutput/Cards/me5_configuration.txt.tmp $PathOutput/Cards/me5_configuration.txt"
eval "rm $PathOutput/Cards/me5_configuration.txt.tmp 2> /dev/null"

#MODIFICO LA runcard PARA tener el número de eventos deseado
eval "cat $PathOutput/Cards/run_card.dat | sed '/#! Number of unweighted events requested/c\  $Nevents = nevents ! Number of unweighted events requested'>> $PathOutput/Cards/run_card.dat.tmp"
eval "cp $PathOutput/Cards/run_card.dat.tmp $PathOutput/Cards/run_card.dat"
eval "rm $PathOutput/Cards/run_card.dat.tmp 2> /dev/null"






execute=$(echo $PathOutput"/bin/generate_events -f")
eval "$execute"

#cat sigmaplotter3.f | sed '/!Marca para cambiar con bash/c\       flagzp = '$i' !Marca para cambiar con bash'>> sigmaplotter.f
#sed 's/Gerardo Gutierrez Gutierrez/'"$participante"'/' ./TEMPLATES/participante_$Template.svg > ./TMP/acceptance_letter_tmp_$name.svg
#! Number of unweighted events requested 
