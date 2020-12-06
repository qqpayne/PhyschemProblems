CC = g++ $(CFLAGS)
CFLAGS = -O0 -g

rusWords: rusWords.cpp utf8/utf8.h utf8/utf8.cpp
	$(CC) -o rusWords rusWords.cpp utf8/utf8.cpp

clean:
	rm -f rusWords rusWords.exe
