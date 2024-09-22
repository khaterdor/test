# Use an official GCC image as the base
FROM gcc:latest

# Set the working directory
WORKDIR /app

# Copy the C source file into the container
COPY server2.c .

# Compile the C program
RUN gcc -o server server2.c

# Expose the port the server listens on
EXPOSE 10000

# Command to run the server
CMD ["./server"]
