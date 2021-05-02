.PHONY: all examples clean

all: examples

examples: basic-buffer basic-string iterative

clean:
	rm -f basic-buffer basic-string iterative

basic-buffer: md5.h md5.cpp ./examples/basic-buffer.cpp
	g++ -o basic-buffer -I $(shell pwd) md5.cpp ./examples/basic-buffer.cpp

basic-string: md5.h md5.cpp ./examples/basic-buffer.cpp
	g++ -o basic-string -I $(shell pwd) md5.cpp ./examples/basic-string.cpp

iterative: md5.h md5.cpp ./examples/iterative.cpp
	g++ -o iterative -I $(shell pwd) md5.cpp ./examples/iterative.cpp
