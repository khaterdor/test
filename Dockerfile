FROM gcc:latest

COPY . .

RUN gcc server.c && ./a.out
