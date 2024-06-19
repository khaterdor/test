FROM gcc:latest
WORKDIR /app
COPY server.c .
COPY control.c .
RUN gcc server.c && ./a.out
