IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = main.cpp
DEPS = $(PATSUBST %,$(IDIR)/%,$(_DEPS))

_OBJ = main.cpp main.cpp
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))¨

$(ODIR)/%.0: %.C $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS)

Filename: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean 

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

