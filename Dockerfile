
FROM gcc

WORKDIR /usr/hoffMan

COPY ./hoffman_encode.cpp ./

RUN gcc hoffman_encode.cpp -o hoffman_encode -lstdc++

CMD ["./hoffman_encode" ]
