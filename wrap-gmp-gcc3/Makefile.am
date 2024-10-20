lib_LIBRARIES = libwrapgmp-gcc3.a

libwrapgmp_gcc3_a_SOURCES = \
Integer.cc \
Rational.cc \
gmp_init.cc

include_HEADERS = \
Integer.h \
Rational.h \
tweaks.h \
gmp_init.h 

INCLUDES        = -I../external/include
INCLUDES       += -I$(includedir)

AM_CPPFLAGS     = -DVERBOSE -ftemplate-depth-20
AM_CXXFLAGS     = -O3
