# base version:
#main: main.o stack.o maze.o
#	gcc main.o stack.o maze.o -g -o main
#
#main.o: main.c main.h stack.h maze.h
#	gcc -c main.c
#
#stack.o: stack.c stack.h main.h
#	gcc -c stack.c
#
#maze.o: maze.c maze.h main.h
#	gcc -c maze.c
#
#
#.PHONY: clean
#clean:
#	@echo "cleanning project"
#	-rm main *.o
#	@echo "clean completed"

#######################################

# final version
all: main

main: main.o stack.o maze.o
	gcc $^ -o $@

clean:
	-rm main *.o *.d

.PHONY: clean

sources = main.c stack.c maze.c

include $(sources:.c=.d)

%.d: %.c
	set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
