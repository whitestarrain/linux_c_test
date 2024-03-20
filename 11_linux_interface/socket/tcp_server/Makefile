all: server client select_server

select_server: ../wrap.o select_server.o
	gcc $^ -o $@

server: ../wrap.o server.o
	gcc $^ -o $@

client: ../wrap.o client.o
	gcc $^ -o $@

clean:
	-rm *.o *.d ../*.d ../*.o server client select_server

.PHONY: clean

sources = ../wrap.c server.c client.c

include $(sources:.c=.d)

%.d: %.c
	set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
