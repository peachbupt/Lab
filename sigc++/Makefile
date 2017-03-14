FLAGS = $(shell pkg-config --cflags sigc++-2.0)
LIBS = $(shell pkg-config --libs sigc++-2.0)
all:
	g++ $(FLAGS) demo1.cpp -o demo1_test $(LIBS)-pthread
	g++ $(FLAGS) demo2.cpp -o demo2_test $(LIBS)
clean:
	rm -f *test
