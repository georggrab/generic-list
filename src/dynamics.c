    DIR *d;
    struct dirent *dir;
    d = opendir("lib");
    if(d){
        while((dir = readdir(d)) != NULL){
            printf("Implementierung gefunden: %s\n", dir->d_name);
        }
    }

    char choice[30];
    char lib[] = "lib/";
    printf("Welche soll benutzt werden?\n");
    printf("Library: ");
    scanf("%20s", choice);
    char *dl = strcat(lib, choice);
    void *dlhdl = dlopen(dl, RTLD_NOW);
    if (!dlhdl){
        fputs(dlerror(), stderr);
        exit(1);
    }

l_new = dlsym(dlhdl, "l_new");
l_print_as_ints = dlsym(dlhdl, "l_print_as_ints");
l_insert = dlsym(dlhdl, "l_insert");
l_delete = dlsym(dlhdl, "l_delete");
l_delete_at = dlsym(dlhdl, "l_delete_at");
l_locate = dlsym(dlhdl, "l_locate");
l_retrieve = dlsym(dlhdl, "l_retrieve");
l_first = dlsym(dlhdl, "l_first");
l_first_idx = dlsym(dlhdl, "l_first_idx");
l_end = dlsym(dlhdl, "l_end");
l_end_idx = dlsym(dlhdl, "l_end_idx");
l_next = dlsym(dlhdl, "l_next");
l_next_idx = dlsym(dlhdl, "l_next_idx");
l_prev = dlsym(dlhdl, "l_prev");
l_prev_idx = dlsym(dlhdl, "l_prev_idx");
populate_random_ints = dlsym(dlhdl, "populate_random_ints");
