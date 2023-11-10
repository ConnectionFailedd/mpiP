FROM ubuntu

RUN apt update
RUN apt install libunwind-dev binutils openmpi-bin libopenmpi-dev -y
RUN apt install python2 python3 -y
RUN apt install build-essential -y
RUN groupadd -g 1000 ubuntu && useradd -u 1000 -g 1000 -s /bin/bash -m ubuntu