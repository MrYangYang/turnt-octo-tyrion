bin_PROGRAMS = tests
tests_SOURCES = test_dispensary.c \
				test_medicine.c \
				test_history.c \
				main.c
AM_CFLAGS=$(DEPS_CFLAGS) $(CHKDEPS_CFLAGS)
tests_LDADD=$(DEPS_LIBS) $(CHKDEPS_LIBS) ../src/libdsp.a

