# Compilatorul folosit
CXX = g++

# Flag-uri: C++17, Optimizare maximă (-O3), Avertismente cod (-Wall)
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra

# Numele executabilului
TARGET = motor_cautare

# Găsește toate fișierele sursă (.cpp)
SRCS = src/main.cpp src/Logger.cpp src/Document.cpp src/Index.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regula pentru fișierele obiect
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) motor_cautare.log