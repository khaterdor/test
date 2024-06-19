FROM gcc:latest

RUN gcc server.c && ./a.out
