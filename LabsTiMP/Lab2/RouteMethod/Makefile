# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

# Целевые файлы
TARGET = cipher
SOURCES = main.cpp route_cipher.cpp
HEADERS = route_cipher.h
OBJECTS = $(SOURCES:.cpp=.o)

# Правило по умолчанию
all: $(TARGET)

# Сборка основной программы
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(LDLIBS)

# Компиляция объектных файлов
main.o: main.cpp route_cipher.h
	$(CXX) $(CXXFLAGS) -c main.cpp

route_cipher.o: route_cipher.cpp route_cipher.h
	$(CXX) $(CXXFLAGS) -c route_cipher.cpp

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET)

# Пересборка
rebuild: clean all

# Phony targets (цели, которые не являются файлами)
.PHONY: all clean rebuild
