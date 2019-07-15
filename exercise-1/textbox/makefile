ifeq ($(OS), Windows_NT)
	CXX = g++
else
	CXX = /usr/bin/i686-w64-mingw32-g++
endif

OBJS = textbox.o main.o

all: $(OBJS)
	$(CXX) $(OBJS) -o main.exe -static