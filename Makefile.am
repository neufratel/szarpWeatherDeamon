# SZARP Scada
# Pawe� Pa�ucha pawel@praterm.com.pl
#
# $Id: Makefile.am 6824 2009-06-05 13:51:11Z pawel $

SUBDIRS = analiza

# Source directory
SOURCE_DIR=@srcdir@

# Additional files for deleting on 'make maintainer-clean'
MAINTAINERCLEANFILES = Makefile.in

# Compilations flags
AM_CPPFLAGS = @XML_CFLAGS@ @LUA_CFLAGS@ \
           -I$(SOURCE_DIR)/../libSzarp/include		\
           -I$(SOURCE_DIR)/../libSzarp2/include		\
           -I$(SOURCE_DIR)/../include			\
	   $(BOOST_CPPFLAGS)				\
	   $(XMLRPC_EPI_CFLAGS)					\
	  `python-config --cflags`			\
	   -DPREFIX=\"@prefix@\"

LIBSZARP2 = ../libSzarp2/libSzarp2.la
LIBSZARP = ../libSzarp/libSzarp.la
USB = -lusb
LDADD = $(LIBSZARP2) $(LIBSZARP) @EVENT_LIBS@ @PTHREAD_CFLAGS@ @XML_LIBS@  $(BOOST_LDFLAGS) $(BOOST_SYSTEM_LIB) $(BOOST_FILESYSTEM_LIB) $(BOOST_THREAD_LIB) $(BOOST_DATE_TIME_LIB) $(BOOST_REGEX_LIB) $(BOOST_LOCALE_LIB) 

# Aditional libraries for daemons using dlopen
DL = -ldl

# Programs to create

bin_PROGRAMS = \
              alstdmn \
	      wetdmn \
	      aqtdmn \
	      calcdmn \
	      calecdmn \
	      dbdmn \
	      @DDEDMN@ \
	      @DLMSDMN@ \
              dpafdmn \
	      dprdmn \
	      eapnetdmn \
              endmn \
	      execdmn \
              fp2kdmn \
	      ifcl5dmn \
              ipcinfo \
	      k601dmn \
	      kamsdmn \
	      kwmsdmn \
              lbdmn \
	      lecdmn \
	      lecmdmn \
              linedmn \
	      lmldmn \
	      logdmn \
	      mbdmn \
	      borutadmn \
	      mbrtudmn \
	      mbtcpdmn \
	      mbusdmn \
	      melsdmn \
	      muksdmn \
	      npozytondmn \
	      nrsdmn \
              pafdmn \
              pafdmnr \
              parcook \
	      polludmn \
	      pozytondmn \
	      @PSETD@ \
	      ratedmn \
              rsdmn \
	      sampledmn \
	      sbusdmn \
	      setdmn \
	      iecdmn \
	      prodmn \
	      sre2dmn \
	      tcpdmn \
	      tensdmn \
	      testdmn \
	      @UNITEDMN@ \
	      wlkdmn \
              zmddmn \
	      pythondmn

if WANT_SNAP7DMN
bin_PROGRAMS += snap7dmn
endif


EXTRA_PROGRAMS = psetd ddedmn unitedmn dlmsdmn


basedmn_SOURCES = base_daemon.cc base_daemon.h

wetdmn_SOURCES =  wet_daemon.cc USBConnector.h 
wetdmn_LDADD =$(LDADD) $(USB)
dpafdmn_SOURCES = dpafdmn.cc

lbdmn_SOURCES = lbdmn.cc

alstdmn_SOURCES = alstdmn.cc

calecdmn_SOURCES = calecdmn.cc

dbdmn_SOURCES = dbdmn.cc

dprdmn_SOURCES = dprdmn.cc

eapnetdmn_SOURCES = eapnetdmn.cc eapnet-prop-plugin.h
eapnetdmn_LDADD = $(LDADD) $(DL)

endmn_SOURCES = endmn.cc

execdmn_SOURCES = execdmn.cc

fp2kdmn_SOURCES = fp2kdmn.cc

ipcinfo_SOURCES = ipcinfo.cc

kamsdmn_SOURCES = kamsdmn.cc
kamsdmn_LDADD = $(LDADD) $(BOOST_LDFLAGS) $(BOOST_FILESYSTEM_LIB) $(BOOST_THREAD_LIB) $(BOOST_DATE_TIME_LIB) $(DL)

kwmsdmn_SOURCES = kwmsdmn.cc

linedmn_SOURCES = linedmn.cc

lmldmn_SOURCES = lmldmn.cc

logdmn_SOURCES = logdmn.cc $(basedmn_SOURCES)

mbrtudmn_SOURCES = mbrtudmn.cc

k601dmn_SOURCES = k601dmn.cc k601-prop-plugin.h
k601dmn_LDADD = $(LDADD) $(DL)

ifcl5dmn_SOURCES = ifcl5dmn.cc

mbtcpdmn_SOURCES = mbtcpdmn.cc

pafdmn_SOURCES = pafdmn.cc

pafdmnr_SOURCES = pafdmnr.cc

polludmn_SOURCES = polludmn.cc

sre2dmn_SOURCES = sre2dmn.cc
sre2dmn_LDADD = $(LDADD) $(DL)

calcdmn_SOURCES = calcdmn.cc

ratedmn_SOURCES = ratedmn.cc

lecdmn_SOURCES = lecdmn.cc

lecmdmn_SOURCES = lecmdmn.cc

tensdmn_SOURCES = tensdmn.cc

muksdmn_SOURCES = muksdmn.cc

aqtdmn_SOURCES = aqtdmn.cc

pozytondmn_SOURCES = pozytondmn.cc pozyton-prop-plugin.h
pozytondmn_LDADD = $(LDADD) $(DL)

npozytondmn_SOURCES = npozytondmn.cc npozyton-prop-plugin.h
npozytondmn_LDADD = $(LDADD) $(DL)

rsdmn_SOURCES = nrsdmn.cc

nrsdmn_SOURCES = nrsdmn.cc

tcpdmn_SOURCES = tcpdmn.cc

testdmn_SOURCES = testdmn.cc

zmddmn_SOURCES = zmddmn.cc

parcook_SOURCES = parcook.cc funtable.cc funtable.h

psetd_SOURCES = psetd.cc
psetd_LDADD = $(LDAP_LIBS) $(SSL_LIBS) $(LDADD)

mbusdmn_SOURCES = mbusdmn.cc

wlkdmn_SOURCES = wlkdmn.cc
wlkdmn_LDADD = $(LDADD) $(BOOST_LDFLAGS) $(BOOST_DATE_TIME_LIB) $(BOOST_FILESYSTEM_LIB) $(BOOST_REGEX_LIB) $(BOOST_PROGRAM_OPTIONS_LIB)

dlmsdmn_SOURCES = dlmsdmn.cc
dlmsdmn_LDADD = $(LDADD) $(BOOST_LDFLAGS) $(LBER_LIBS)

melsdmn_SOURCES = melsdmn.cc mels-prop-plugin.h
melsdmn_LDADD = $(LDADD) $(BOOST_LDFLAGS) $(DL)

unitedmn_SOURCES = unitedmn.cc
unitedmn_LDADD = $(LDADD) @XML_LIBS@ @PTHREAD_CFLAGS@ $(BOOST_DATE_TIME_LIB) $(BOOST_FILESYSTEM_LIB) $(BOOST_THREAD_LIB)

mbdmn_SOURCES = mbdmn.cc
mbdmn_LDADD = $(LDADD) @EVENT_LIBS@ @XML_LIBS@ @PTHREAD_CFLAGS@ $(BOOST_DATE_TIME_LIB) $(BOOST_FILESYSTEM_LIB) $(BOOST_THREAD_LIB)

borutadmn_SOURCES = borutadmn.cc borutadmn.h boruta_zet.cc boruta_modbus.cc boruta_fp210.cc boruta_wmtp.cc boruta_lumel.cc
borutadmn_LDADD = $(LDADD) @EVENT_LIBS@ @XML_LIBS@ @PTHREAD_CFLAGS@ $(BOOST_DATE_TIME_LIB) $(BOOST_FILESYSTEM_LIB) $(BOOST_THREAD_LIB)

sampledmn_SOURCES = sampledmn.cc $(basedmn_SOURCES)

sbusdmn_SOURCES = sbusdmn.cc

ddedmn_SOURCES = ddedmn.cc
ddedmn_LDADD = $(LDADD) $(BOOST_LDFLAGS) $(XMLRPC_EPI_LIBS) $(CURL_LIBS) -lstdc++

setdmn_SOURCES = setdmn.cc
setdmn_LDADD = $(LDADD) @EVENT_LIBS@ -lstdc++

iecdmn_SOURCES = iecdmn.cc
iecdmn_LDADD = $(LDADD)

prodmn_SOURCES = prodmn.cc
prodmn_LDADD = $(LDADD) @EVENT_LIBS@ @XML_LIBS@ @PTHREAD_CFLAGS@ $(BOOST_DATE_TIME_LIB) $(BOOST_FILESYSTEM_LIB) $(BOOST_THREAD_LIB)

pythondmn_SOURCES = pythondmn.cc
pythondmn_LDADD = $(LDADD) -l$(BOOST_PYTHON_LIB) @PTHREAD_CFLAGS@ $(BOOST_DATE_TIME_LIB) $(BOOST_FILESYSTEM_LIB) $(BOOST_THREAD_LIB) $(BOOST_PYTHON_MODULE) $(PYTHON_LDFLAGS)

snap7dmn_SOURCES = snap7dmn.cc $(basedmn_SOURCES)
snap7dmn_LDADD = $(LDADD) -lsnap7
