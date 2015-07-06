all:

include ../rules.mk
include defines.mk

EXE := test-runner

all: $(EXE)
	
gtest: $(EXE)
	./$< --gtest_output=xml:./xml/all.xml

LIBS := alignment/libblasr_gtest.a \
		hdf/libpbihdf_gtest.a \
		pbdata/libpbdata_gtest.a

$(EXE): $(LIBS)
	$(CXX) $(CXXOPTS) $(CXXFLAGS) $(GTEST_SRC) -Wl,$(LD_WHOLE_ARCHIVE) $^ -Wl,$(LD_NO_WHOLE_ARCHIVE) -o $@ -I$(GTEST_ROOT) $(LIBDIRS) $(LDFLAGS)

$(LIBS):
	${MAKE} -C $(dir $@) PBINCROOT=${PBINCROOT}/.. $(notdir $@)

clean:
	@${MAKE} -C alignment clean
	@${MAKE} -C hdf clean
	@${MAKE} -C pbdata clean
	@${RM} -fr $(EXE) xml
