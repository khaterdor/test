FROM gcc:latest
WORKDIR /app
COPY server.c .
COPY control.c .
RUN gcc -o test server.c
CMD ["/app/test"]
