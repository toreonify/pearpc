#AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = ppc
AM_CPPFLAGS =
SUBDIRS = common configuration cpu
ppc_LDFLAGS	= @PPC_LDFLAGS@
ppc_LDADD = configuration/libconfiguration.a common/libcommon.a cpu/@CPU_DIR@/libcpu.a
ppc_SOURCES = main.cpp pearpc.cpp