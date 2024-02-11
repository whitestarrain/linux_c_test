hello: hello.o
	ld hello.o -o hello

hello.o: hello.s
	as hello.s -o hello.o


.PHONY: clean
clean:
	-rm *.o hello
