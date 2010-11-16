CC = gcc

skalarprodukt4:
	$(CC) -c skalar.c empty.c
	$(CC) skalarprodukt4.c skalar.o empty.o wall_time.c

wall_time_test:
	$(CC) wall_time_test.c wall_time.c

clean:
	rm -f *.o a.out skalarprodukt.TMP
