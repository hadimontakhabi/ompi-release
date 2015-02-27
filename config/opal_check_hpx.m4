# -*- shell-script -*-
#
# Copyright (c) 2004-2005 The Trustees of Indiana University and Indiana
#                         University Research and Technology
#                         Corporation.  All rights reserved.
# Copyright (c) 2004-2005 The University of Tennessee and The University
#                         of Tennessee Research Foundation.  All rights
#                         reserved.
# Copyright (c) 2004-2005 High Performance Computing Center Stuttgart, 
#                         University of Stuttgart.  All rights reserved.
# Copyright (c) 2004-2006 The Regents of the University of California.
#                         All rights reserved.
# Copyright (c) 2009      Cisco Systems, Inc.  All rights reserved.
# Copyright (c) 2008-2014 University of Houston. All rights reserved.
# $COPYRIGHT$
# 
# Additional copyrights may follow
# 
# $HEADER$
#

# OPAL_CHECK_HPX(prefix, [action-if-found], [action-if-not-found])
# --------------------------------------------------------
# check if HPX support can be found.  sets prefix_{CPPFLAGS, 
# LDFLAGS, LIBS} as needed and runs action-if-found if there is
# support, otherwise executes action-if-not-found
AC_DEFUN([OPAL_CHECK_HPX],[

    check_hpx_CXXFLAGS="-w -std=c++11 -DNDEBUG -DHPX_DISABLE_ASSERTS -D_GNU_SOURCE -DHPX_APPLICATION_EXPORTS -DHPX_ENABLE_ASSERT_HANDLER"
    check_hpx_CPPFLAGS="-w -std=c++11 -DNDEBUG -DHPX_DISABLE_ASSERTS -D_GNU_SOURCE -DHPX_APPLICATION_EXPORTS -DHPX_ENABLE_ASSERT_HANDLER"
    check_hpx_LDFLAGS=
    check_hpx_LIBS="-lhpx -lhpx_init -lhpx_serialization -lboost_date_time -lboost_filesystem -lboost_program_options -lboost_regex -lboost_serialization -lboost_system -lboost_thread -lboost_atomic -lboost_chrono -lprofiler -ltcmalloc -liostreams"

    check_hpx_save_LIBS="$LIBS" 
    check_hpx_save_LDFLAGS="$LDFLAGS"
    check_hpx_save_CPPFLAGS="$CPPFLAGS"
    check_hpx_save_CXXFLAGS="$CXXFLAGS"

    check_hpx_configuration="none"
    opal_check_hpx_happy="yes"


    # Get some configuration information
    AC_ARG_WITH([boost],
        [AC_HELP_STRING([--with-boost(=DIR)],
             [Build HPX support, optionally adding DIR/include, DIR/lib, and DIR/lib64 to the search path for headers and libraries])])
    OMPI_CHECK_WITHDIR([boost], [$with_boost], [include/boost/any.hpp])


    AC_ARG_WITH([hpx],
        [AC_HELP_STRING([--with-hpx(=DIR)],
             [Needed to build HPX support, optionally adding DIR/include, DIR/lib, and DIR/lib64 to the search path for headers and libraries])])
    OMPI_CHECK_WITHDIR([hpx], [$with_hpx], [include/hpx/hpx.hpp])


    temp_with_hpx="$with_hpx"
    AS_IF([test -z "$with_hpx"],
          [with_hpx="/usr"])
    
    # Add correct -I and -L flags
    AS_IF([test -d "$with_hpx/include"],
        [check_hpx_CPPFLAGS="$check_hpx_CPPFLAGS -I$with_hpx/include -I$with_hpx/include/hpx/external -I$with_boost/include"
			check_hpx_CXXFLAGS="$check_hpx_CXXFLAGS -I$with_hpx/include -I$with_hpx/include/hpx/external -I$with_boost/include"
            $1_CPPFLAGS="$check_hpx_CPPFLAGS"
			$1_CXXFLAGS="$check_hpx_CXXFLAGS"
            CPPFLAGS="$CPPFLAGS $check_hpx_CPPFLAGS"
			CXXFLAGS="$CXXFLAGS $check_hpx_CXXFLAGS"],
	[opal_check_hpx_happy="no"])
    
    AS_IF([test "$opal_check_hpx_happy" = "yes"],
	[AS_IF([test -d "$with_hpx/lib/hpx"],
		[check_hpx_LDFLAGS="$check_hpx_LDFLAGS -L$with_hpx/lib/hpx -L$with_hpx/lib -L$with_boost/lib"
		    $1_LDFLAGS="$check_hpx_LDFLAGS"
		    LDFLAGS="$LDFLAGS $check_hpx_LDFLAGS"
			],
		[opal_check_hpx_happy="no"]) 
    ],[])
	    
    # Try to find all the hpx libraries
    AS_IF([test "$opal_check_hpx_happy" = "yes"],
	[ 
		$1_LIBS="$check_hpx_LIBS"
		LIBS="$check_hpx_LIBS $LIBS"

		# check for hpx
		AC_LANG(C++)
		AC_CHECK_HEADERS([hpx/hpx.hpp],
		    [AC_MSG_CHECKING([if possible to link HPX])
			AC_LINK_IFELSE(
			    [AC_LANG_PROGRAM(
				    [[#include <hpx/hpx.hpp>]],
				    [[hpx::find_all_localities();]])],
			    [AC_MSG_RESULT([yes])
				opal_check_hpx_happy="yes"],
			    [AC_MSG_RESULT([no])
				opal_check_hpx_happy="no"])],
		    [opal_check_hpx_happy="no"])
    ])

    LDFLAGS="$check_hpx_save_LDFLAGS"
    CPPFLAGS="$check_hpx_save_CPPFLAGS"
    CXXFLAGS="$check_hpx_save_CXXFLAGS"
    LIBS="$check_hpx_save_LIBS"
    AS_IF([test "$opal_check_hpx_happy" = "yes"],
          [$2],
          [AS_IF([test ! -z "$with_hpx" -a "$with_hpx" != "no"],
                  [echo HPX support not found])
              $3])

    with_hpx="$temp_with_hpx"
])

