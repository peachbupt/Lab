1. install libsigc++
	sudo apt-get install libsigc++
2. compile
	g++ demo1.cpp -o demo1 `pkg-config --cflags --libs sigc++-2.0` -lpthread
3. run
	./demo1

