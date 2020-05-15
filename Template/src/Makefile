IDIR = ../include

CC = gcc
CFLAGS = -g -lm -I$(IDIR)

ODIR = obj

project: main.c $(IDIR)/main.h $(ODIR)/phase1.o $(ODIR)/phase2.o
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/phase1.o: phase1.c $(IDIR)/phase1.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/phase2.o: phase2.c $(IDIR)/phase2.h
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
		rm project
		rm -f $(ODIR)/*.o *~ core $(IDIR)/*~
