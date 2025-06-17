CXX = g++
CXXFLAGS = -std=c++17 -O2 -Iinclude

SRC_DIR = src
INCLUDE_DIR = include
HNSW_DIR = include/hnswlib/hnswlib

SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/app_config.cpp \
       $(SRC_DIR)/csv_reader.cpp \
       $(SRC_DIR)/hnsw_indexer.cpp

OBJS = $(SRCS:.cpp=.o)
TARGET = hnsw_test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)
