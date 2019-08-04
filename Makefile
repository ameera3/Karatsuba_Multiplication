# Change the CXX variable assignment at your own risk.
CXX ?= g++ 
CXXFLAGS=-std=c++11 -Wall -O2
LDFLAGS=-g

all: karatsuba 

karatsuba: karatsuba.cpp 

clean:
	rm -f karatsuba *.o core* *~

