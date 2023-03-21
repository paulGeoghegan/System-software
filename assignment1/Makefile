CC=gcc
CFLAGS=-I.
DEPS=daemon_task.h
ODIR=objects
_OBJ=backup_dashboard.o check_file_uploads.o collect_reports.o daemon.o lock_directories.o sig_handler.o unlock_directories.o update_timer.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

reportManager: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run: reportManager
	./reportManager 3

clean:
	rm reportManager
	rm -f $(ODIR)/*.o