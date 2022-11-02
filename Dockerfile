FROM ubuntu:latest
RUN apt-get update -y
RUN apt-get install -y libavcodec-dev libavformat-dev libswscale-dev
WORKDIR /app
COPY . /app
CMD ./vpaSTRM

