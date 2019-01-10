#!/bin/bash
source /home/camilo/HEPTools/ROOT/root/Root6Python2_7/bin/thisroot.sh


MadGraphPath=/home/camilo/HEPTools/MADGRAPH/MG5_aMC_v2_5_5_Root6
DelphesPath=$MadGraphPath/Delphes

export LD_LIBRARY_PATH=$DelphesPath:$LD_LIBRARY_PATH

ExRootAnalysisPath=
export LD_LIBRARY_PATH=$MadGraphPath/ExRootAnalysis:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$MadGraphPath/ExRootAnalysis/ExRootAnalysis:$LD_LIBRARY_PATH

#To root reconize the the delphes library

export ROOT_INCLUDE_PATH=$DelphesPath:$ROOT_INCLUDE_PATH
export ROOT_INCLUDE_PATH=$DelphesPath/ExRootAnalysis:$ROOT_INCLUDE_PATH
