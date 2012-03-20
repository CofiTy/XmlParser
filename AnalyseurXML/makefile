CC=g++
EDL=g++
RM=rm
BUILDDIR=build/
SRCDIR=src/
PARSEDIR=parse/
PARSEBUILDDIR=parseBuild/
CCFLAGS=-g -DYYDEBUG=1 -O0 -Wall
LDFLAGS=
RMFLAGS=-f
EXE=analyseXML
EFFACE=clean
OBJ=$(BUILDDIR)Data.o $(BUILDDIR)NodeList.o $(BUILDDIR)DocumentXML.o
PARSEOBJ=$(PARSEBUILDDIR)xml.tab.o $(PARSEBUILDDIR)lex.xml.o

all: $(OBJ) $(PARSEOBJ)

$(BUILDDIR)%.o : $(SRCDIR)%.cpp $(SRCDIR)%.h $(PARSEDIR)xml.tab.c
	$(CC) $(CCFLAGS) -c $< -o $@

$(PARSEBUILDDIR)%.o : $(PARSEDIR)%.c
	$(CC) $(CCFLAGS) -c $< -o $@

$(PARSEDIR)lex.xml.c : $(PARSEDIR)xml.l
	flex -Pxml -o$(PARSEDIR)lex.xml.c $<

$(PARSEDIR)xml.tab.c : $(PARSEDIR)xml.y
	bison -p xml --debug --verbose --defines=$(PARSEDIR)xml.tab.h -o$(PARSEDIR)xml.tab.c $<

$(EFFACE) :
	$(RM) $(RMFLAGS) $(BUILDDIR)*.o $(EXE) core $(PARSEDIR)*.output $(PARSEBUILDIR)*.o $(PARSEDIR)*.c $(PARSEDIR)*.h
