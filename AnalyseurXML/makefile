EXEC=analyseXML

all: $(EXEC)

analyseXML: *.l *.y makefile
	flex -Pxml xml.l
	bison -p xml --debug --verbose --defines=xml.tab.h xml.y
	g++ -g -DYYDEBUG=1 -o analyseXML  lex.xml.c  xml.tab.c Data.cpp NodeList.cpp DocumentXML.cpp
clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output analyseXML

#Below here is crap reformating makefile
#CC=g++
#EDL=g++
#RM=rm
#BUILDDIR=build/
#SRCDIR=src/
#PARSEDIR=parse/
#PARSEBUILDDIR=parseBuild/
#CCFLAGS=-g -DYYDEBUG=1 -O0 -Wall
#LDFLAGS=
#RMFLAGS=-f
#EXE=analyseXML
#EFFACE=clean
#OBJ=$(BUILDDIR)rules.o $(BUILDDIR)guiNetwork.o $(BUILDDIR)sensorsNetwork.o $(BUILDDIR)guiInterface.o $(BUILDDIR)actions.o $(BUILDDIR)sensors.o $(BUILDDIR)actionneurs.o
#PARSEOBJ=$(PARSEBUILDDIR)rules.tab.o $(PARSEBUILDDIR)lex.yy.o
#
#FLEX=flex -Pxml -o$(PARSEDIR)lex.xml.c
#BISON=bison -p xml -o$(PARSEDIR)xml.tab.c -d
#
#$(EXE) : $(PARSEOBJ) $(OBJ) $(BUILDDIR)main.o
#	$(EDL) $(LDFLAGS) -o $(EXE) $(OBJ) $(PARSEOBJ) $(LIBS) $(BUILDDIR)main.o
#
#$(BUILDDIR)%.o : $(SRCDIR)%.c $(SRCDIR)%.h
#	$(CC) $(CCFLAGS) -c $< -o $@
#
#$(BUILDDIR)main.o : $(SRCDIR)main.c
#	$(CC) $(CCFLAGS) -c $< -o $@
#
#$(PARSEBUILDDIR)%.o : $(PARSEDIR)%.c
#	$(CC) $(CCFLAGS) -c $< -o $@
#
#$(PARSEDIR)lex.yy.c : $(PARSEDIR)rules.l
#	$(FLEX) $<
#
#$(PARSEDIR)rules.tab.c : $(PARSEDIR)rules.y
#	$(BISON) $<
#
#$(EFFACE) :
#	$(RM) $(RMFLAGS) $(BUILDDIR)*.o $(EXE) core $(PARSEBUILDIR)*.o $(PARSEDIR)*.c $(PARSEDIR)*.h
