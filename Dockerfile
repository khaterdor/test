FROM gcc:latest
COPY . .
RUN gcc server2.c && ./a.out
EXPOSE 10000
