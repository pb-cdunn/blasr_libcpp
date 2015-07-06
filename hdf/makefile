export
# Same as .EXPORT_ALL_VARIABLES

all clean: mkdefines
	${MAKE} -f build.mk $@

mkdefines:
	#./conf-nightly.py defines.mk
	cp normal.defines.mk defines.mk
