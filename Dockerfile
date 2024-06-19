FROM gcc:latest
WORKDIR /app
COPY server.c .
COPY control.c .
RUN gcc -o server.c test
CMD ["/app/test"]
