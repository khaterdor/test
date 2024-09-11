FROM gcc:latest
RUN gcc server2.c
RUN ./a.out
