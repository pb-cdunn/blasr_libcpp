include ../../rules.mk
include ../defines.mk

SOURCES    = $(wildcard *.cpp) \
		     $(wildcard utils/*.cpp) \
		     $(wildcard datastructures/alignment/*.cpp) \
		     $(wildcard files/*.cpp) \
		     $(wildcard format/*.cpp) 

ifneq ($(origin nopbbam), undefined)
	SOURCES := $(filter-out format/SAMHeaderPrinter_gtest.cpp, $(SOURCES))
endif

OBJECTS    = $(SOURCES:.cpp=.o)

EXE := test-runner

all debug profile: $(EXE)

libblasr_gtest.a: $(OBJECTS)
	$(AR) $(ARFLAGS)c $@ $^

$(EXE): $(OBJECTS)
	$(CXX) $(CXXOPTS) $(CXXFLAGS) $^ $(GTEST_SRC) -o $@ -I$(GTEST_ROOT) $(LIBDIRS) $(LDFLAGS)

$(OBJECTS): %.o: %.cpp
	$(CXX) $(CXXOPTS) $(CXXFLAGS) -c $< -o $@ $(INCDIRS)

gtest: $(EXE)
	./$< --gtest_output=xml:../xml/alignment.xml

clean:
	@find . -type f -name \*.o -delete
	@find . -type f -name \*.d -delete
	@rm -f libblasr_gtest.a $(EXE) ../xml/alignment.xml
