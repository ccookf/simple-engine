CC = g++
LDFLAGS = -lsfml-system-d -lsfml-window-d -lsfml-graphics-d -lsfml-audio-d
CFLAGS = -std=c++11 -DDEBUG -g
SFML = C:/SFML-2.4.2/include
SOURCES = main.cpp $(wildcard src/*.cpp)
HEADERS = $(wildcard include/*.h)
OBJECTS = $(SOURCES:.cpp=.o)
INCLUDE = include
EXECUTABLE = main.exe

all: $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
 
.cpp.o: $(HEADERS)
	$(CC) -c $(CFLAGS) -I$(INCLUDE) -I$(SFML) $< -o $@

.PHONY: clean
clean:
	cmd /C  del $(EXECUTABLE) & del /S *.o & exit