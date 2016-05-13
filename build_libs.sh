#!/bin/bash
# Ist Teil des Makefiles
echo "Looking for implementations.-.-.-."
for i in $(ls -1 src/impl | grep -E "*.o\$"); do
    echo "Found Implementation $i"
    gcc -shared -Wl,-soname,lib$i.so -o lib/lib$i.so src/impl/$i -lc
done
