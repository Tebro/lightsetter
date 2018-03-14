

%.o: %.c
	gcc -c -o $@ $<

lightsetter: lightsetter.o
	gcc -o lightsetter lightsetter.o


.PHONY: install

ifeq ($(PREFIX),)
    PREFIX := /usr/
endif

install: lightsetter
	install -m 4755 -o root -g root lightsetter $(DESTDIR)$(PREFIX)bin/lightsetter
