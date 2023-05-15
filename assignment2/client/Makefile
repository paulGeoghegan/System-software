CC=gcc
CFLAGS=-I.
ODIR=objects
SRCDIR=src
_OBJ=client.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

reportClient: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run: reportClient
	./reportClient 3

clean:
	rm reportClient
	rm -f $(ODIR)/*.o