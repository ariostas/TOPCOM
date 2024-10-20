##############################################################################
## Makefile for building external packages
## 2003/01/27 jr
##############################################################################
TOPCOMRELDIR = ..
SH           = sh

GMP_DONE     = gmp_done
CDD_DONE     = cdd_done
QSO_DONE     = qso_done

GMP_NAME     = gmp
CDD_NAME     = cddlib
QSO_NAME     = qsopt_ex

GMP_INCLUDES = include/gmp.h
CDD_INCLUDES = include/cdd.h  include/cddmp.h  include/cddtypes.h  include/setoper.h
CDD_INCLUDES = include/qsopt_ex/QSopt_ex.h

GMP_LIBS     = lib/libgmp.a
CDD_LIBS     = lib/libcddgmp.a
QSO_LIBS     = lib/libqsopt_ex.a

GMP_VERSION = 6.2.1
GMP_COMPRESSFORMAT = bz2
GMP_EXTRACTOPTIONS = -xvjf

CDD_VERSION = 0.94j-TOPCOMb
CDD_COMPRESSFORMAT = gz
CDD_EXTRACTOPTIONS = -xzvf

QSO_VERSION = 2.5.10.3
QSO_COMPRESSFORMAT = gz
QSO_EXTRACTOPTIONS = -xzvf

GMP_DIR = $(GMP_NAME)-$(GMP_VERSION)
CDD_DIR = $(CDD_NAME)-$(CDD_VERSION)
QSO_DIR = $(QSO_NAME)-$(QSO_VERSION)

GMP_TAR      = $(GMP_NAME)-$(GMP_VERSION).tar.$(GMP_COMPRESSFORMAT)
CDD_TAR      = $(CDD_NAME)-$(CDD_VERSION).tar.$(CDD_COMPRESSFORMAT)
QSO_TAR      = $(QSO_NAME)-$(QSO_VERSION).tar.$(QSO_COMPRESSFORMAT)

GMP_DIR      = $(GMP_NAME)-$(GMP_VERSION)
CDD_DIR      = $(CDD_NAME)-$(CDD_VERSION)
QSO_DIR      = $(QSO_NAME)-$(QSO_VERSION)

CPPFLAGS    += -I`pwd`/../include
LDFLAGS     += -L`pwd`/../lib

all: gmp cdd qso

gmp: $(GMP_DONE)

cdd: $(CDD_DONE)

qso: $(QSO_DONE)

$(GMP_DONE): $(GMP_DIR)
	@echo ==============================================================================
	@echo making gmp ...
	@echo ==============================================================================
	$(SH) -c 'cd $(GMP_DIR); ./configure CFLAGS="-std=c11 -O3 -g -pthread" CPPFLAGS="$(CPPFLAGS)" LDFLAGS="$(LDFLAGS)" --prefix=`pwd`/.. --libdir=`pwd`/../lib --enable-cxx --with-pic'
	make -C $(GMP_DIR)
	make -C $(GMP_DIR) check
	make -C $(GMP_DIR) install
	@echo ==============================================================================
	@echo installing patched wrapper:
	@echo ==============================================================================
	$(SH) -c 'mkdir -p include; cp gmpxx-patch/gmpxx.h include/'
	@echo ==============================================================================
	@echo ... done making gmp.
	@echo ==============================================================================
	touch $(GMP_DONE)

$(CDD_DONE): $(CDD_DIR)
	@echo ==============================================================================
	@echo making cdd ...
	@echo ==============================================================================
	@echo LDFLAGS is $(LDFLAGS)
	$(SH) -c 'cd $(CDD_DIR); ./configure CC=${CXX} CFLAGS="-std=c++11 -O3 -g -pthread" CPPFLAGS="$(CPPFLAGS)" LDFLAGS="$(LDFLAGS)" --prefix=`pwd`/.. --libdir=`pwd`/../lib '
	make -C $(CDD_DIR)
	make -C $(CDD_DIR) install
	@echo ==============================================================================
	@echo ... done making cdd.
	@echo ==============================================================================
	touch $(CDD_DONE)

$(QSO_DONE): $(QSO_DIR)
	@echo ==============================================================================
	@echo making qsopt_ex ...
	@echo ==============================================================================
	$(SH) -c 'cd $(QSO_DIR); ./configure CFLAGS="-O3 -g -pthread" CPPFLAGS="$(CPPFLAGS)" LDFLAGS="$(LDFLAGS)" --prefix=`pwd`/.. --libdir=`pwd`/../lib '
	$(SH) -c 'cd $(QSO_DIR); make; make install'
	@echo ==============================================================================
	@echo ... done making qsopt_ex.
	@echo ==============================================================================
	touch $(QSO_DONE)

$(GMP_DIR): $(GMP_TAR)
	@echo ==============================================================================
	@echo unpacking gmp ...
	@echo ==============================================================================
	tar $(GMP_EXTRACTOPTIONS) $(GMP_TAR)
	@echo ==============================================================================
	@echo ... done unpacking gmp.
	@echo ==============================================================================

$(CDD_DIR): $(CDD_TAR)
	@echo ==============================================================================
	@echo unpacking cdd ...
	@echo ==============================================================================
	tar $(CDD_EXTRACTOPTIONS) $(CDD_TAR)
	@echo ==============================================================================
	@echo ... done unpacking cdd.
	@echo ==============================================================================

$(QSO_DIR): $(QSO_TAR)
	@echo ==============================================================================
	@echo unpacking qsopt_ex ...
	@echo ==============================================================================
	tar $(QSO_EXTRACTOPTIONS) $(QSO_TAR)
	@echo ==============================================================================
	@echo ... done unpacking qsoptex.
	@echo ==============================================================================

.PHONY: clean clean_installdirs clean_gmp clean_cdd clean_qso

clean: clean_gmp clean_cdd clean_qso

clean_installdirs:
	rm -rf include lib info bin

clean_gmp:
	rm -f $(GMP_DONE)
	rm -rf $(GMP_DIR)
	rm -rf include lib info bin

clean_cdd:
	rm -f $(CDD_DONE)
	rm -rf $(CDD_DIR)

clean_qso:
	rm -f $(QSO_DONE)
	rm -rf $(QSO_DIR)

# eof Makefile jr.
