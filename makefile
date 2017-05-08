HEADER = bidirectional_search.h
TARGET = exe

OBJS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
CC = g++
OPTION = -O3

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(OPTION) -lm 

%.o: %.cc $(HEADER)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o