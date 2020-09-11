FROM debian:latest

RUN apt-get update
RUN apt-get install -y autoconf automake gcc make

WORKDIR /bugs

COPY include include/
COPY src src/