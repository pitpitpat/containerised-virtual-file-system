CC=gcc

IDIR =./include
ODIR=./obj

CFLAGS=-I $(IDIR) -Wall

EXEC = cfs

_DEPS = utility.h datastream.h superData.h metaData.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_MY_STATION_OBJ = cfs.o utility.o
MY_STATION_OBJ = $(patsubst %,$(ODIR)/%,$(_MY_STATION_OBJ))


$(ODIR)/%.o: ./src/%.c $(DEPS) | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(EXEC)

cfs: $(MY_STATION_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	@echo "Executable file \"$@\" created";

$(ODIR):
	mkdir -p $@

.PHONY: clean

clean:
	rm -rf $(ODIR)/
	rm -f $(EXEC)
