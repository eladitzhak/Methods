ifeq ($(OS), Windows_NT)
	CXX = g++
else
	CXX = /usr/bin/i686-w64-mingw32-g++
endif

OBJS = main.o Controller.o Panel.o GeneralInterface.o RadioBox.o Label.o Button.o TextBox.o NumericBox.o ComboBox.o CheckList.o Messagebox.o

all: $(OBJS)
	$(CXX) $(OBJS) -o main.exe -static