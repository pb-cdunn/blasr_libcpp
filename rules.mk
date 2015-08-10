ARFLAGS         := rc
CXX_SHAREDFLAGS := -fPIC
#LD_SHAREDFLAGS  := -dynamiclib -fPIC
CPPFLAGS        += $(patsubst %,-I%,${INCLUDES})


%.a:
	${AR} $(ARFLAGS) $@ $^

%.so:
	${CXX} -shared -fPIC ${LDFLAGS} -o $@ -Wl,-soname,$@ $^

%.dylib:
	${CXX} -dynamiclib ${LDFLAGS} -o $@ -Wl,-install_name,$@ $^

%.o: %.cpp
	$(CXX) $(CXXOPTS) $(CXXFLAGS) $(LEGACY) $(CPPFLAGS) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o) $(@:%.o=%.d)" -c $< -o $@

%.shared.o: %.cpp
	$(CXX) $(CXXOPTS) $(CXXFLAGS) $(LEGACY) $(CPPFLAGS) $(CXX_SHAREDFLAGS) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o) $(@:%.o=%.d)" -c $< -o $@
