CPP=g++
ld=$(CPP)
CPPFLAGS=-std=c++11
LDFLAGS=

keys = demo
objs = slugify-cpp.o

all:$(keys) $(objs)

demo:demo.cpp $(objs)
	$(CPP) $(CPPFLAGS) $(LDFLAGS) -o $@ $< $(objs)
slugify-cpp.o:slugify-cpp.cpp
	$(CPP) $(CPPFLAGS) $(LDFLAGS) -c $< 
	
clean:
	rm $(keys)
	rm $(objs)


	 
	
 	
