FROM gcc:latest
COPY . .
CMD ["gcc server2.c", "./a.out"]
