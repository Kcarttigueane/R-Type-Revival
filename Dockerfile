FROM ubuntu:23.10 

RUN apt update && apt install -y libboost-all-dev cmake libsfml-dev protobuf-compiler g++

WORKDIR /app

COPY . .

RUN cd build && rm -rf * && cmake .. && make

CMD ["./build/server/r-type_server"]