.SUFFIXES:
.SUFFIXES: .o .c

.c.o:
	${CC} -c ${CFLAGS} $<

OBJS = field.o main.o cg.o die.o gauss_seidel.o gauss_seidel_col.o laplace.o init.o jacobi.o output.o residuum.o

CC = gcc -fopenmp
LDFLAGS = -lm

laplace: ${OBJS}
	${CC} ${LDFLAGS} -o $@ ${OBJS}

clean:
	rm -f laplace ${OBJS}
