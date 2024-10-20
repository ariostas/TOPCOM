bin_PROGRAMS = checkregularity

checkregularity_SOURCES = checkregularity.cc

LDADD           = ../lib-src-reg/libCHECKREG.a \
                  ../lib-src/libTOPCOM.a \
                  ../external/lib/libcddgmp.a \
                  ../external/lib/libgmpxx.a \
                  ../external/lib/libgmp.a

INCLUDES        = -I../lib-src
INCLUDES       += -I../lib-src-reg
INCLUDES       += -I../wrap-gmp-gmpxx
INCLUDES       += -I../external/include
INCLUDES       += -I$(includedir)


AM_CPPFLAGS     = -DVERBOSE -DGMPRATIONAL -ftemplate-depth-30

AM_CXXFLAGS     = -O2
