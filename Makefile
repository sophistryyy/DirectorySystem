.phony all:
all: diskinfo disklist diskget diskput diskfix

diskinfo: diskinfo.c
	gcc diskinfo.c -o diskinfo

disklist: disklist.c 
	gcc disklist.c -o disklist

diskget: diskget.c 
	gcc diskget.c -o diskget

diskput: diskput.c 
	gcc diskput.c -o diskput

diskfix: diskfix.c 
	gcc diskfix.c -o diskfix

.PHONY clean:
clean:
	-rm -rf *.o *.exe