CC=gcc
CFLAGS=-I. -g 

#Obacht: Dynamisch linken oder nicht
#wenn LDYNAMIC nicht gesetzt ist, wird statisch gegen
#USE_THIS_IMPLEMENTATION gelinked
LDYNAMIC=-DLINK_DYNAMIC -ldl

USE_THIS_IMPLEMENTATION=ll.o
DEPS=src/impl/$(USE_THIS_IMPLEMENTATION) src/list_generics.o src/sorters.o

#Obacht 2: test wird failen, falls die cmocka dependency
#nicht auf dem build system installiert ist
all: objfiles test libs main

objfiles:
	$(MAKE) -C src

libs: objfiles
	./build_libs.sh

main: src libs
ifdef LDYNAMIC
	$(CC) $(LDYNAMIC) main.c -omain
else
	$(CC) $(DEPS) main.c -omain
endif

profile: src libs
	$(CC) $(DEPS) -g profile.c -oprofile

clean:
	rm -f lib/*.a
	# rm nervt wenn keine input files vorhanden sind
	# daher null command ausführen, damit diese zeile immer
	# 0 returned.
	find . -name "*.o" | xargs rm 2>/dev/null || :
	rm -f ./main

# todo implement generic unit tests
test:
	rm -f tests/test_array tests/test_ll
	$(CC) -g tests/test.c src/impl/array.o -lcmocka -o tests/test_array
	$(CC) -g tests/test.c src/impl/ll.o -lcmocka -o tests/test_ll
	./tests/test_array
	./tests/test_ll


