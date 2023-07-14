#!/bin/bash

rm -f valgrindtest
touch valgrindtest
gcc -o memtest memtest.c waitlist.c

regex="All heap blocks were freed -- no leaks are possible"


# Grabbing valgrind output and searching using a regex to see if there were no memory leaks
valgrindOutput=$(valgrind --log-fd=1 ./memtest)
if grep -P -q "$regex" <<< "$valgrindOutput"; then
    echo "Freed" >> valgrindtest
else
    echo "Not Freed" >> valgrindtest
fi

rm memtest