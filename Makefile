GCC = g++
CFLAGS = -std=c++11

make:
	$(GCC) $(CFLAGS) -o P1 main.cpp

clean: 
	rm -f P1
