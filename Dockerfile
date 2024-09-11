FROM gcc:latest
COPY . .
RUN gcc server2.c
RUN ./a.out
