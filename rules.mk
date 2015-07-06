ARFLAGS := rc

%.a:
	${AR} $(ARFLAGS) $@ $^

%.so:
	${CXX} ${LD_SHAREDFLAGS} -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXOPTS) $(CXXFLAGS) $(LEGACY) $(INCLUDES) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o) $(@:%.o=%.d)" -c $< -o $@

%.shared.o: %.cpp
	$(CXX_pp) $(CXX_SHAREDFLAGS) $(CXXOPTS) $(CXXFLAGS) $(LEGACY) $(INCLUDES) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o) $(@:%.o=%.d)" -c $< -o $@
