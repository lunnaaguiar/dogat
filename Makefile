SRC = $(wildcard src/*.c)
CFLAGS = -O1 -Wall -std=c99 -I include -I .

ifeq ($(OS),Windows_NT)
	OUT = Dogat.exe
	CFLAGS += -I C:/raylib/include
	LDFLAGS = -L C:/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm
else
	OUT = Dogat
	LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

all:
	gcc $(SRC) -o $(OUT) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f Dogat Dogat.exe