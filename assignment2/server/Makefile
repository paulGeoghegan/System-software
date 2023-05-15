CC=gcc
CFLAGS=-I.
DEPS=server.h
ODIR=objects
SRCDIR=src
_OBJ=server.o fileSaver.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/$(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

reportServer: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run: reportServer
	./reportServer 3

clean:
	rm reportServer
	rm -f $(ODIR)/*.o