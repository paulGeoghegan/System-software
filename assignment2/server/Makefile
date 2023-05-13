CC=gcc
CFLAGS=-I.
ODIR=objects
SRCDIR=src
_OBJ=server.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

reportServer: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run: reportServer
	./reportServer 3

clean:
	rm reportServer
	rm -f $(ODIR)/*.o