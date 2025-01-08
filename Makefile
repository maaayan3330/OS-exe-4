# שם הקובץ הבינארי שיווצר
EXEC = ex4.out

# קומפיילר
CC = g++

# פלאגים לקומפילציה
CFLAGS = -std=c++17 -Wall -pthread

# כל קבצי המקור וה-Header בפרויקט
SRC = main.cpp Configuration.cpp BoundedBuffer.cpp Producer.cpp Dispatcher.cpp CoEditor.cpp ScreenManager.cpp
HEADERS = Configuration.h BoundedBuffer.h Producer.h Dispatcher.h CoEditor.h ScreenManager.h

# חוקים ל-Makefile

all: $(EXEC)

$(EXEC): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

# ניקוי הקבצים שנוצרים בקומפילציה
clean:
	rm -f $(EXEC)

# הרצה של התוכנית עם קובץ הקונפיגורציה
run: $(EXEC)
	./$(EXEC) config.txt
