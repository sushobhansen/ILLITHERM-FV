#Makefile for ILLITHERM-FV

PROGRAM = illithermfv
SOURCE = illithermfv.c
OBJECTS = illithermfv.o
ARCHIVE = illithermfv.tar

CC = gcc
CFLAGS = -lm -I.
DEPS = illithermfvheaders.h
OPTIONS = 
#OPTIONS = -g -debug extended -traceback -O0

%.o: %.c $(DEPS)
	$(CC) $(OPTIONS) -c -o $@ $< $(CFLAGS)

$(PROGRAM):	$(OBJECTS)
	$(CC) $(OPTIONS) -o $(PROGRAM).out $(OBJECTS) $(CFLAGS)
	
clean: 
	rm -f $(OBJECTS) $(PROGRAM).out *.tar *.plt
	
rebuild:
	clean $(PROGRAM)
	
archive:
	@echo Creating code archive tar-file $(ARCHIVE) ...
	tar cf $(ARCHIVE) $(SOURCE) Makefile
	@ls -l $(ARCHIVE)

help:
	@echo Try:
	@echo make $(PROGRAM) .... to build the program named $(PROGRAM)
	@echo make clean .... to clean up, removing object files and program $(PROGRAM)
	@echo make archive .... to make an archive tar file you can transfer or submit
