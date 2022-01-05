AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS	= ppc

AM_CPPFLAGS =

SUBDIRS = configuration

ppc_LDFLAGS	= @PPC_LDFLAGS@

ppc_LDADD = configuration/libconfiguration.a

ppc_SOURCES	= main.cc info.h pearpc.cc pearpc.h

