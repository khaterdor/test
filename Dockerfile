# Use a base image with a C compiler and necessary libraries
FROM gcc:latest

# Set the working directory inside the container
WORKDIR /app

# Copy all source files to the container's working directory
COPY server.c control.c /app/

# Compile the server.c to generate executable 'server'
RUN gcc -o server server.c

# Expose port 80 to allow external access
EXPOSE 80

# Command to run the server when the container starts
CMD ["./server"]
