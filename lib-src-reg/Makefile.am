lib_LIBRARIES = libCHECKREG.a

libCHECKREG_a_SOURCES = \
SPXinterface.cc \
LPinterface.cc \
RegularityCheck.cc

include_HEADERS = \
SPXinterface.hh \
RegularityCheck.hh \
LPinterface.hh

INCLUDES        = -I../lib-src 
INCLUDES       += -I../wrap-gmp-gmpxx
INCLUDES       += -I../external/include
INCLUDES       += -I$(includedir)

AM_CPPFLAGS     = -DVERBOSE -DGMPRATIONAL -ftemplate-depth-30

AM_CXXFLAGS     = -O2
