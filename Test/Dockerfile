FROM ubuntu:latest

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y 
RUN apt-get install qtcreator -y
RUN apt-get install build-essential -y 
RUN apt install qtbase5-dev qt5-qmake -y

COPY ../GraphVisual /usr/src/GraphVisual

COPY . /usr/src/Test
WORKDIR /usr/src/Test

RUN mkdir build
WORKDIR /usr/src/Test/build
RUN qmake ..
RUN make