CXX:=g++

PROGRAM_NAME:=fibheap

SOURCES:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp,%.o,$(SOURCES))
DEPS:=$(patsubst %.cpp,%.d,$(SOURCES))

all: $(PROGRAM_NAME)

run: $(PROGRAM_NAME)
	 ./$(PROGRAM_NAME)

$(PROGRAM_NAME): $(OBJS)
	$(CXX) $(OBJS) -o $@

.cpp.o:
	$(CXX) -c $< -o $@
	
clean:
	rm -rf .deps
	rm -f $(OBJS) *.o
	rm -f $(PROGRAM_NAME)

.SUFFIXES: .cpp .h .d .o

deps:
	rm -f .deps/*.d
	$(CXX) -MD -E $(SOURCES) > /dev/null
	mkdir -p .deps
	mv $(DEPS) .deps

-include .deps/*.d

