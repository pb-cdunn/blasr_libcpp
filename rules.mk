ARFLAGS         := rc
CXX_SHAREDFLAGS := -fPIC
#LD_SHAREDFLAGS  := -dynamiclib -fPIC
CPPFLAGS        += $(patsubst %,-I%,${INCLUDES})
CFLAGS          += -fno-common
LDFLAGS         += ${EXTRA_LDFLAGS}


%.a:
	${AR} $(ARFLAGS) $@ $^

%.so:
	${CXX} -shared ${LDFLAGS} -o $@ -Wl,-soname,$@ $^ ${LDLIBS}

%.dylib:
	${CXX} -dynamiclib ${LDFLAGS} -o $@ -Wl,-install_name,$@ $^ ${LDLIBS}

%.o: %.cpp
	$(CXX) $(CXXOPTS) $(CXXFLAGS) $(LEGACY) $(CPPFLAGS) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o) $(@:%.o=%.d)" -c $< -o $@

%.shared.o: %.cpp
	$(CXX) $(CXXOPTS) $(CXXFLAGS) $(LEGACY) $(CPPFLAGS) $(CXX_SHAREDFLAGS) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o) $(@:%.o=%.d)" -c $< -o $@
