CFLAGS = -O6 -std=c99
CC     = gcc


../example: ../example.o ../cmdarg.a
	$(CC) $^ -o ../example $(CFLAGS)

../cmdarg.a: main.o error.o print.o functions.o
	ar rcs $@ $^

../example.o: ../example.c
	$(CC) -c $< -o $@ $(CFLAGS)

main.o: main.c
	$(CC) -c $< -o $@ $(CFLAGS)

error.o: error.c
	$(CC) -c $< -o $@ $(CFLAGS)

print.o: print.c 
	$(CC) -c $< -o $@ $(CFLAGS)

functions.o: functions.c 
	$(CC) -c $< -o $@ $(CFLAGS)


clean:
	rm *.o
