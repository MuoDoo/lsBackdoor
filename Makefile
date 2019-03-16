proc : ls pld
ls: ls.c
	gcc -o $@ $<

pld: payload.c
	gcc -z execstack -o $@ $<
