gcc -O3 main.c src/server.c src/server-handling.c src/parsing.c src/students.c -o main
./main
rm -rf main