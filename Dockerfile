FROM gcc:latest
WORKDIR /app
COPY server2.c .
RUN gcc server2.c
EXPOSE 10000
RUN ./a.out
