src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

CXX = g++
CPPFLAGS = -Wall -std=c++11
LDFLAGS = -lncurses -lm

t:	$(obj)
	$(CXX) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) t