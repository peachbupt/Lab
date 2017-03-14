FLAGS = -g $(shell pkg-config --cflags glib-2.0 gmodule-export-2.0)
LIBS  = $(shell pkg-config --libs glib-2.0 gmodule-export-2.0)

all:
	g++ $(FLAGS) demo1.cpp -o demo1_test $(LIBS)
clean:
	rm *test

