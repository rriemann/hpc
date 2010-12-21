OBJS = field.o \
       init_decomp.o process_mapping.o mesh_coordinates.o \
       main.o die.o diff.o init.o \
       laplace.o jacobi.o jacobi9.o exchange_boundary.o \
       output.o output_parallel.o

CC = mpicc

laplace: ${OBJS}
	${CC} -o $@ ${OBJS} -lm

clean:
	rm -f laplace ${OBJS}
