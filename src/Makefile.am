bin_PROGRAMS=dispensary
noinst_LIBRARIES = libdsp.a
dispensary_SOURCES = callbacks.c \
					 data_io.c \
					 interface.c \
					 main.c \
					 my_type.c

libdsp_a_SOURCES = dispensary.c \
				   medicine.c \
				   history.c 

AM_CFLAGS=$(DEPS_CFLAGS)
dispensary_LDADD=$(DEPS_LIBS) libdsp.a
					 
