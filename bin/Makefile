CC = g++
CFLAGS = -Wall -I../include
LDFLAGS = -L../lib -lraylib -lopengl32 -lgdi32 -lwinmm

SRCDIR = ../src
BINDIR = ../bin
INCDIR = ../include

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BINDIR)/%.o)
TARGET = $(BINDIR)/game.exe

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BINDIR)/*.o $(TARGET)
