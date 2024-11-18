# Specify the folder for object files
OBJDIR = obj
CXX = g++                    # C++ compiler
CXXFLAGS = -std=c++11 -Wall -Wextra -O2  # Compilation flags
OBJS = $(OBJDIR)/main.o $(OBJDIR)/bond.o

# Target to create the output
output: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o main

# Rule to compile main.cpp and place the object file in OBJDIR
$(OBJDIR)/main.o: main.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(OBJDIR)/main.o

# Rule to compile bond.cpp and place the object file in OBJDIR
$(OBJDIR)/bond.o: bond.cpp bond.h
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c bond.cpp -o $(OBJDIR)/bond.o

# Clean up object files and the main executable
clean:
	rm -rf $(OBJDIR) main *.zip

zip: output
	zip homework3.zip main.cpp bond.cpp bond.h main readme.md

.PHONY: output clean  # Declaring phony targets