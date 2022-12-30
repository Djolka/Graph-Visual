FROM ubuntu:latest

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y 
RUN apt-get install qtcreator -y
RUN apt-get install build-essential -y 
RUN apt install qtbase5-dev qt5-qmake -y

COPY . /usr/src/GraphVisual
WORKDIR /usr/src/GraphVisual

RUN mkdir build
WORKDIR /usr/src/GraphVisual/build
RUN qmake ..
RUN make