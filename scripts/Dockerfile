# very elementary Dockerfile running this project
FROM gcc:latest

COPY . /DockerWorld

WORKDIR /DockerWorld/

RUN gcc -o DockerWorld dockerworld.c

CMD [“./DockerWorld”]

