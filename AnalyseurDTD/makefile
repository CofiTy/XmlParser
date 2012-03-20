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
EXE=analyseDTD
EFFACE=clean
OBJ=$(BUILDDIR)DTDNode.o $(BUILDDIR)DTDValidator.o
PARSEOBJ=$(PARSEBUILDDIR)dtd.tab.o $(PARSEBUILDDIR)lex.dtd.o

all: $(OBJ) $(PARSEOBJ)

$(BUILDDIR)%.o : $(SRCDIR)%.cpp $(SRCDIR)%.h
	$(CC) $(CCFLAGS) -c $< -o $@

$(BUILDDIR)main.o : $(SRCDIR)main.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

$(PARSEBUILDDIR)%.o : $(PARSEDIR)%.c
	$(CC) $(CCFLAGS) -c $< -o $@

$(PARSEDIR)lex.dtd.c : $(PARSEDIR)dtd.l
	flex -Pdtd -o$(PARSEDIR)lex.dtd.c $<

$(PARSEDIR)dtd.tab.c : $(PARSEDIR)dtd.y
	bison -p dtd --debug --verbose --defines=$(PARSEDIR)dtd.tab.h -o$(PARSEDIR)dtd.tab.c $<

$(EFFACE) :
	$(RM) $(RMFLAGS) $(BUILDDIR)*.o $(EXE) core $(PARSEDIR)*.output $(PARSEBUILDIR)*.o $(PARSEDIR)*.c $(PARSEDIR)*.h
