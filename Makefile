# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread

# Executable and object files
EXEC = test
OBJS = main.o BoundedBuffer.o CountingSemaphore.o Producer.o Dispatcher.o Shared.o

# Default target
all: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# Compile main.cpp
main.o: main.cpp BoundedBuffer.h CountingSemaphore.h Producer.h Dispatcher.h Shared.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compile BoundedBuffer.cpp
BoundedBuffer.o: BoundedBuffer.cpp BoundedBuffer.h CountingSemaphore.h Shared.h
	$(CXX) $(CXXFLAGS) -c BoundedBuffer.cpp

# Compile CountingSemaphore.cpp
CountingSemaphore.o: CountingSemaphore.cpp CountingSemaphore.h
	$(CXX) $(CXXFLAGS) -c CountingSemaphore.cpp

# Compile Producer.cpp
Producer.o: Producer.cpp Producer.h BoundedBuffer.h Shared.h
	$(CXX) $(CXXFLAGS) -c Producer.cpp

# Compile Dispatcher.cpp
Dispatcher.o: Dispatcher.cpp Dispatcher.h BoundedBuffer.h Shared.h
	$(CXX) $(CXXFLAGS) -c Dispatcher.cpp

# Compile Shared.cpp
Shared.o: Shared.cpp Shared.h
	$(CXX) $(CXXFLAGS) -c Shared.cpp

# Clean target to remove compiled files
clean:
	rm -f $(EXEC) $(OBJS)

# Run the program
run: $(EXEC)
	./$(EXEC)
