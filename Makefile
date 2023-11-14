GCC = g++
CFLAGS = -g -std=c++11
SRCS= main.cpp parser.cpp testTree.cpp

make:
	$(GCC) $(CFLAGS) -o P2 $(SRCS)

clean: 
	rm -f P2
