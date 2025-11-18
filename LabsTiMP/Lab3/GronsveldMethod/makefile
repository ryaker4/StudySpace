# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
LDFLAGS = -lUnitTest++

# Имена файлов
SOURCES = main.cpp modAlphaCipher.cpp
HEADERS = modAlphaCipher.h
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = test_modAlpha_cipher

# Правило по умолчанию
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Компиляция объектных файлов
main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

modAlphaCipher.o: route_cipher.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c modAlphaCipher.cpp -o modAlphaCipher.o

# Запуск тестов
test: $(TARGET)
	./$(TARGET)

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET)

# Пересборка
rebuild: clean all

# Объявление фиктивных целей
.PHONY: all test clean rebuild
