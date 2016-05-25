main:
	$(CC) -g -c list_generics.c
	$(CC) -g -c sorters.c
	$(MAKE) -C impl

sorters: main
	$(CC) -DSORTERS_STANDALONE -g list_generics.o impl/array.o sorters.c
