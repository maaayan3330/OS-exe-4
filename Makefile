all: ex4.out

ex4.out: main.o BoundedBuffer.o Producer.o Dispatcher.o CoEditor.o ScreenManager.o Configuration.o
	g++ -o ex4.out main.o BoundedBuffer.o Producer.o Dispatcher.o CoEditor.o ScreenManager.o Configuration.o -pthread

main.o: main.cpp
	g++ -c main.cpp

Configuration.o: Configuration.cpp
	g++ -c Configuration.cpp

BoundedBuffer.o: BoundedBuffer.cpp
	g++ -c BoundedBuffer.cpp

Producer.o: Producer.cpp
	g++ -c Producer.cpp

Dispatcher.o: Dispatcher.cpp
	g++ -c Dispatcher.cpp

CoEditor.o: CoEditor.cpp
	g++ -c CoEditor.cpp

ScreenManager.o: ScreenManager.cpp
	g++ -c ScreenManager.cpp

clean:
	rm -f *.o ex4.out
