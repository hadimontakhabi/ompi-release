#
# Copyright (c) 2012      Los Alamos National Security, LLC.
#                         All rights reserved.
# $COPYRIGHT$
# 
# Additional copyrights may follow
# 
# $HEADER$
#

headers = rte_hpx.h \
	rte_hpx_db.h

sources = \
        rte_hpx_component.c \
        rte_hpx_module.c \
	rte_hpx_db.cpp

# Conditionally install the header files
if WANT_INSTALL_HEADERS
ompidir = $(ompiincludedir)/$(subdir)
nobase_ompi_HEADERS = $(headers)
endif

# We only ever build this component statically
noinst_LTLIBRARIES = libmca_rte_hpx.la
libmca_rte_hpx_la_SOURCES = $(sources)
libmca_rte_hpx_la_CXXFLAGS = $(rte_hpx_CXXFLAGS)
libmca_rte_hpx_la_CPPFLAGS = $(rte_hpx_CPPFLAGS)
libmca_rte_hpx_la_LDFLAGS = -module -avoid-version $(rte_hpx_LDFLAGS) 
libmca_rte_hpx_la_LIBADD = $(top_builddir)/orte/libopen-rte.la $(rte_hpx_LIBS)

