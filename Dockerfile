# Docker version 27.2.0
FROM gcc:14.2.0 AS build-stage

WORKDIR /app

COPY src/ src/

RUN g++ -Wall -fexceptions -O2  -c src/main.cpp -o ./main.o

RUN g++ -o ./create_index ./main.o -s -static-libstdc++ -static-libgcc -static

################################################################################

FROM scratch

WORKDIR /app

COPY input/ input/

COPY --from=build-stage /app/create_index .

CMD [ "./create_index" ]
