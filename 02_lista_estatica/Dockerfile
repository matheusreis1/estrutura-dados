FROM gcc:4.9

ARG path

COPY ${path} /usr/src/myapp

WORKDIR /usr/src/myapp

# compila o codigo
# gcc -o: Write the build output to an output file.
RUN gcc -o myapp main.c

CMD ["./myapp"]
