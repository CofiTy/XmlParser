CC=g++
EDL=g++
RM=rm
BUILDDIR=build/
PARSEBUILDDIR=parseBuild/
SRCDIR=src/
XML_DIR=AnalyseurXML/
DTD_DIR=AnalyseurDTD/
CCFLAGS=-g -O0 -Wall
LDFLAGS=-lboost_regex
RMFLAGS=-f
EXE=analyse
EFFACE=clean
OBJ=

all: xml dtd $(EXE)

xml:
	@(cd $(XML_DIR) && $(MAKE))

dtd:
	@(cd $(DTD_DIR) && $(MAKE))

$(EXE) : xml dtd $(BUILDDIR)main.o
	$(EDL) -o $(EXE) $(XML_DIR)$(BUILDDIR)*.o $(XML_DIR)$(PARSEBUILDDIR)*.o $(DTD_DIR)$(BUILDDIR)*.o $(DTD_DIR)$(PARSEBUILDDIR)*.o $(LIBS) $(BUILDDIR)main.o $(LDFLAGS) 

$(BUILDDIR)main.o : $(SRCDIR)main.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

$(PARSEBUILDDIR)%.o : $(PARSEDIR)%.c
	$(CC) $(CCFLAGS) -c $< -o $@

$(PARSEDIR)lex.xml.c : $(PARSEDIR)xml.l
	flex -Pxml -o$(PARSEDIR)lex.xml.c $<

$(PARSEDIR)xml.tab.c : $(PARSEDIR)xml.y
	bison -p xml --debug --verbose --defines=$(PARSEDIR)xml.tab.h -o$(PARSEDIR)xml.tab.c $<

$(EFFACE) :
	@(cd $(XML_DIR) && $(MAKE) $@)
	@(cd $(DTD_DIR) && $(MAKE) $@)
	$(RM) $(RMFLAGS) $(BUILDDIR)*.o $(EXE) core
