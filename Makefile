CXX = g++
CXXFLAGS = -Wall -Wextra -Werror
TARGET = main
SOURCES = main.cpp draw.cpp
TESTS = validation.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) validation.o

fclean: clean
	rm -f $(TARGET) validation

re: fclean all

test: validation
	./validation

validation: validation.o
	$(CXX) $(CXXFLAGS) validation.o   -o validation

.PHONY: all clean fclean re test