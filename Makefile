PROJECT = Pacman

CC = g++

CFLAGS = -Wall -std=c++11

LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

ODIR = obj

SDIR = src

# Include the tinyxml2 directory
TINYXML2_DIR = $(SDIR)/tinyxml2

# Add tinyxml2.cpp to the list of source files
SOURCE_FILES := $(wildcard $(SDIR)/*.cpp) $(TINYXML2_DIR)/tinyxml2.cpp

# Update the OBJECTS rule to handle the subdirectory for tinyxml2
OBJECTS = $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(filter-out $(TINYXML2_DIR)/tinyxml2.cpp, $(SOURCE_FILES))) $(patsubst $(TINYXML2_DIR)/%.cpp, $(ODIR)/%.o, $(wildcard $(TINYXML2_DIR)/*.cpp))

all: $(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CC) -o $(PROJECT) $(OBJECTS) $(LIBS)

# General rule for compiling .cpp files in the src directory
$(ODIR)/%.o: $(SDIR)/%.cpp
	@if [ ! -d $(ODIR) ]; then \
		mkdir $(ODIR); \
	fi
	$(CC) -c -o $@ $< $(CFLAGS)

# Specific rule for compiling tinyxml2.cpp
$(ODIR)/%.o: $(TINYXML2_DIR)/%.cpp
	@if [ ! -d $(ODIR) ]; then \
		mkdir $(ODIR); \
	fi
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf $(ODIR)/*.o $(PROJECT)

