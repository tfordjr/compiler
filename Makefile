GCC = g++
CFLAGS = -g -std=c++11
SRCS= main.cpp parser.cpp testTree.cpp

make:
	$(GCC) $(CFLAGS) -o comp $(SRCS)

clean: 
	rm -f comp
	rm -f *.asm