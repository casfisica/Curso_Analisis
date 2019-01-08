# -------------------------------------------------
# -------     Universidad de los Andes      -------
# -------      Departamento de Física       -------
# -------    Proyecto Joven Investigador    -------
# -------  Andrés Felipe García Albarracín  -------
# -------          February - 2015          -------
# -------------------------------------------------
### changed by f.v.d.p. , to run locally in my pc.

# This makefile serves to compile c++ programs using HepMC and Root libraries
#
# Usage of the program
# Write one of the next possibilities:
# make compile                    To compile without Root nor HepMC
# make compile_ROOT               To compile with Root and without HepMC
# make compile_HepMC              To compile without Root and with HepMC
# make compile_ROOT_HepMC         To compile with Root and HepMC
# make compile_ROOT_Delphes       To compile with Root and Delphes

# Modify the following variables according to your c++ compiler and your 
# local Root and HepMC installation folders. If you do not use any of these
# programs, leave blank.

# C++ Compiler
CXX=g++

# Name of the main file and the target file
MAINFILE=scan.cc
HEADERS==scan.h
TARGETFILE=scan

###OTHERFILES= HepMCFunctions.h DelphesFunctions.h ROOTFunctions.h  
OTHERFILES=DelphesFunctions.h ROOTFunctions.h  
#mt2_bisect.h mt2bl_bisect.h mt2w_bisect.h # Other files (checked at the Makefile revision)
#SOURCEFILES=mt2_bisect.cpp mt2bl_bisect.cpp mt2w_bisect.cpp

# Directory where HepMC is installed
HEPMCDIR=/home/camilo/HEPTools/HEPMC/CompileHepMC_2_06_09_ROOT6
HEPMCLIB=$(HEPMCDIR)/lib
EPMCINC=$(HEPMCDIR)/include/

# Root flags and libs
#ROOTFLAGLIB=root-config --cflags --glibs
#ROOTPHYLIB=/usr/local/HEP/ROOT5.34.34/lib/root # Directory where is located libPhysics.so
ROOTPHYLIB=/home/camilo/HEPTools/ROOT/root/Root5Python2_7/lib # Directory where is located libPhysics.so

# Directory of Exrootanalysis
EXROOTLIB=/home/camilo/HEPTools/MADGRAPH/MG5_aMC_v2_5_5_Root6/ExRootAnalysis
EXROOTINC=$(EXROOTLIB)/ExRootAnalysis

# Directory of Delphes
##DELPHESDIR=/home/fp/Heptools/Delphes-3.2.0
DELPHESDIR=/home/camilo/HEPTools/MADGRAPH/MG5_aMC_v2_5_5_Root6/Delphes
DELPHESLIB=${DELPHESDIR}
DELPHESINC=${DELPHESDIR}

all: 
	@echo " Usage: write one of the next possibilities:"
	@echo "	make compile    			To compile without Root nor HepMC"
	@echo "	make compile_ROOT			To compile with Root and without HepMC"
	@echo "	make compile_HepMC    			To compile without Root and with HepMC"
	@echo "	make compile_ROOT_HepMC    		To compile with Root and HepMC"
	@echo "	make compile_ROOT_Delphes		To compile with Root and Delphes"
	@echo " To edit make parameters type vi Makefile"


# To compile without Root nor HepMC
compile: $(MAINFILE) $(OTHERFILES)
	$(CXX) -o $(TARGETFILE) $(MAINFILE) $(SOURCEFILES)

# To compile with Root and without HepMC
compile_ROOT: $(MAINFILE) $(OTHERFILES)
	$(CXX) -o $(TARGETFILE) $(MAINFILE) $(SOURCEFILES)`root-config --cflags --glibs` \
          -I$(EXROOTINC) \
          -L$(EXROOTLIB) -lExRootAnalysis -L$(ROOTPHYLIB) -lPhysics

# To compile without Root and with HepMC
compile_HepMC: $(MAINFILE) $(OTHERFILES)
	$(CXX) -o $(TARGETFILE) $(MAINFILE) $(SOURCEFILES)\
	 -I$(HEPMCINC) \
	 -L$(HEPMCLIB) -lHepMC

# To compile with Root and HepMC
compile_ROOT_HepMC: $(MAINFILE) $(OTHERFILES)
	$(CXX) -o $(TARGETFILE) $(MAINFILE) $(SOURCEFILES) `root-config --cflags --glibs` \
         -I$(HEPMCINC) -I$(EXROOTINC) \
         -L$(HEPMCLIB) -lHepMC -L$(EXROOTLIB) -lExRootAnalysis -L$(ROOTPHYLIB) -lPhysics

# To compile with Root and Delphes
compile_ROOT_Delphes: $(MAINFILE) $(OTHERFILES)
	$(CXX) -o $(TARGETFILE) $(MAINFILE) $(SOURCEFILES) `root-config --cflags --glibs` \
         -I$(DELPHESINC) -I$(EXROOTINC) \
         -L$(DELPHESLIB) -lDelphes -L$(EXROOTLIB) -lExRootAnalysis -L$(ROOTPHYLIB) -lPhysics

