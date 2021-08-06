all:
	mkdir -p bin ; make server ; make client

server:
	mkdir -p bin ; g++ -o bin/server-executable server-main.cpp gen-cpp/Example.* -lthrift

client:
	mkdir -p bin ; g++ -o bin/client-executable client-main.cpp gen-cpp/Example.* -lthrift
