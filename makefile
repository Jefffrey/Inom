CC				:= g++
RM				:= rm
SUITE_EXE 		:= suite
SUITE_CPP_FILES	:= $(wildcard test/*.cpp) $(wildcard test/inom/*.cpp)
SUITE_OBJ_FILES	:= $(SUITE_CPP_FILES:.cpp=.o)
LD_FLAGS		:=
CC_FLAGS		:= -std=c++11 -O2 -ferror-limit=1

suite: $(SUITE_OBJ_FILES)
	$(CC) $(LD_FLAGS) -o $@ $^

remake:
	make clean
	make

run:
	make $(SUITE_EXE)
	./$(SUITE_EXE)

clean:
	rm -f $(SUITE_EXE)
	find . -name "*.o" -type f -delete

test/%.o: test/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $<
