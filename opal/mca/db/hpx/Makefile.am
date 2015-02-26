#
# Copyright (c) 2012      Los Alamos National Security, Inc. All rights reserved.
# $COPYRIGHT$
# 
# Additional copyrights may follow
# 
# $HEADER$
#

sources = \
        db_hpx.h \
        db_hpx_component.c \
        db_hpx.c \
	db_hpx_db.h \
	db_hpx_db.cpp

# Make the output library in this directory, and name it either
# mca_<type>_<name>.la (for DSO builds) or libmca_<type>_<name>.la
# (for static builds).

if MCA_BUILD_opal_db_hpx_DSO
component_noinst =
component_install = mca_db_hpx.la
else
component_noinst = libmca_db_hpx.la
component_install =
endif

mcacomponentdir = $(ompilibdir)
mcacomponent_LTLIBRARIES = $(component_install)
mca_db_hpx_la_SOURCES = $(sources)
mca_db_hpx_la_CPPFLAGS = $(db_hpx_CPPFLAGS)
mca_db_hpx_la_CXXFLAGS = $(db_hpx_CXXFLAGS)
mca_db_hpx_la_LDFLAGS = -module -avoid-version $(db_hpx_LDFLAGS)
mca_db_hpx_la_LIBADD = $(db_hpx_LIBS) 

noinst_LTLIBRARIES = $(component_noinst)
libmca_db_hpx_la_SOURCES =$(sources)
libmca_db_hpx_la_CPPFLAGS = $(db_hpx_CPPFLAGS)
libmca_db_hpx_la_CXXFLAGS = $(db_hpx_CXXFLAGS)
libmca_db_hpx_la_LDFLAGS = -module -avoid-version $(db_hpx_LDFLAGS)
libmca_db_hpx_la_LIBADD = $(db_hpx_LIBS)
