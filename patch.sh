#!/bin/bash

#Esto es para corregir un error que hay en la actualización MG5_aMC_v2_5_2
#debe de estar definida la variable MadGrapgSYS (path a la carpeta de MadGraph)

cd $MadGrapgSYS/HEPTools/lhapdf6/share/LHAPDF
wget https://www.hepforge.org/archive/lhapdf/pdfsets/6.1/NNPDF23_lo_as_0130_qed.tar.gz
tar -xzvf NNPDF23_lo_as_0130_qed.tar.gz
rm -f NNPDF23_lo_as_0130_qed.tar.gz
cd -
