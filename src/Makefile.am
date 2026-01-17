## Process this file with automake to produce Makefile.in

deskewdir = $(GIMP_LIBDIR)/plug-ins/deskew
deskew_PROGRAMS = deskew

deskew_SOURCES =                                \
	plugin-intl.h                           \
	interface.c                             \
	interface.h                             \
	main.c                                  \
	main.h                                  \
	render.c                                \
	render.h                                \
	formats/gimpfact.cc                     \
	formats/gimpfact.h                      \
	raster/bwfactory.h                      \
	raster/bwimage.cc                       \
	raster/bwimage.h                        \
	raster/deskewer.cc                      \
	raster/deskewer.h                       \
	util/bitutil.cc                         \
	util/bitutil.h                          \
	util/cntptr.h                           \
	deskew.cc                               \
	deskew.h

AM_CPPFLAGS = \
	-DLOCALEDIR=\""$(LOCALEDIR)"\"		\
	-DDATADIR=\""$(DATADIR)"\" \
	-I$(top_srcdir)		\
	@GIMP_CFLAGS@		\
	-I$(includedir)

LDADD = $(GIMP_LIBS)
#LDADD = $(GIMP_LIBS) -lnetpbm

