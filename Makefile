all:
	g++ -c -std=c++11 src/*.cpp -I /usr/include/sigc++-2.0/ -I /usr/lib64/sigc++-2.0/include/ -I/usr/include/SDL/

	 g++ -o SF *.o -l SDL -l SDL_image -l sigc-2.0 -l SDL_ttf
	./SF

