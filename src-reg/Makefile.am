bin_PROGRAMS = checkregularity

checkregularity_SOURCES = checkregularity.cc

LDADD           = ../lib-src-reg/libCHECKREG.a \
                  ../lib-src/libTOPCOM.a \
                  ../wrap-gmp-gcc4/libwrapgmp-gcc4.a \
                  ../external/lib/libcddgmp.a \
                  ../external/lib/libgmp.a

INCLUDES        = -I../lib-src
INCLUDES       += -I../lib-src-reg
INCLUDES       += -I../wrap-gmp-gcc4
INCLUDES       += -I../external/include
INCLUDES       += -I$(includedir)


AM_CPPFLAGS     = -DVERBOSE -DGMPRATIONAL -ftemplate-depth-30

AM_CXXFLAGS     = -O2
