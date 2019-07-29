ifeq ($(OS), Windows_NT)
	CXX = g++
else
	CXX = /usr/bin/i686-w64-mingw32-g++
endif

OBJS = PanelTest.o ../Panel.o ../Controller.o ../GeneralInterface.o

all: $(OBJS)
	$(CXX) $(OBJS) -o test.exe -static