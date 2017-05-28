CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

smo: $(OBJ_FILES)
	   mpic++  -fopenmp -o $@ $^

obj/%.o: src/%.cpp
	   mpic++  -fopenmp -c -o $@ $<

clean:
		rm -f obj/*.o smo
