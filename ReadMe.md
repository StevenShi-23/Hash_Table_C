Work-in-progress Hash-table with separate chaining,
to-add/implement: function to resize the hash table and transfer its current entries,
function to free, others. -caution, code needs additional testing.

Compile (in gcc) with:

    gcc -g -Wall -Wextra hashtable.c -c -o table.o

    gcc -g -Wall -Wextra hashchain.c -c -o chain.o

    gcc -g -Wall -Wextra table.o chain.o -o program_name