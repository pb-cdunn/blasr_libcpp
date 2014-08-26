include ../common.mk

INCDIRS    = -I../ \
			 -I$(PBINCROOT)/pbdata

LIBDIRS    = -L$(PBINCROOT)/pbdata

LDFLAGS   := -lpbdata -lpthread -lz -ldl

SOURCES    = $(wildcard *.cpp) \
		     $(wildcard utils/*.cpp) \
		     $(wildcard metagenome/*.cpp) \
		     $(wildcard saf/*.cpp)
OBJECTS    = $(SOURCES:.cpp=.o)
EXECS      = $(SOURCES:.cpp=)


all: $(EXECS)


$(EXECS): % : %.o
	$(CXX) $(CCOPTS) $(CCFLAGS) $< $(GTEST_MAINA) -static -o $@ $(LIBDIRS) $(LDFLAGS)

.cpp.o:
	$(CXX) $(CCOPTS) $(CCFLAGS) -c $< -o $@ $(INCDIRS) $(GTESTINCDIRS) 

gtest: $(EXECS)
	@(for exe in $(EXECS); do echo "Running $$exe"; ./$$exe --gtest_output=xml:../xml/$$exe.xml; done;)

clean:
	@(find . -type f -name \*.o -delete)
	@(find . -type f -name \*.d -delete)
	@(for exe in $(EXECS); do rm -f $$exe; rm -f ../xml/$$exe.xml; done;)

