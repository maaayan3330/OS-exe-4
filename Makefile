# שם הקובץ הסופי
TARGET = test

# קבצי המקור
SRC = main.cpp \
      BoundedBuffer.cpp \
      CountingSemaphore.cpp \
      Producer.cpp \
      Dispatcher.cpp

# קבצי הכותרות
HEADERS = BoundedBuffer.h \
          CountingSemaphore.h \
          Producer.h \
          Dispatcher.h

# הקומפיילר והפלגים
CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread

# יעד ברירת המחדל
all: $(TARGET)

# יצירת הקובץ הבינארי
$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# ניקוי קבצים שנוצרו
clean:
	rm -f $(TARGET)
