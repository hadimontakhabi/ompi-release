# -*- shell-script -*-
#
# Copyright (c) 2012-2013 Los Alamos National Security, LLC.
#                         All rights reserved.
# $COPYRIGHT$
# 
# Additional copyrights may follow
# 
# $HEADER$
#
# MCA_db_hpx_CONFIG([action-if-found], [action-if-not-found])
# -----------------------------------------------------------

AC_DEFUN([MCA_opal_db_hpx_CONFIG], [
	AC_CONFIG_FILES([opal/mca/db/hpx/Makefile])
         
	OPAL_CHECK_HPX([db_hpx], [db_hpx_good=1], [db_hpx_good=0])
         
	# Evaluate succeed / fail
	AS_IF([test "$db_hpx_good" = 1],
            [$1],
            [$2])

	# set build flags to use in makefile
	AC_SUBST([db_hpx_CPPFLAGS])
	AC_SUBST([db_hpx_CXXFLAGS])
	AC_SUBST([db_hpx_LDFLAGS])
	AC_SUBST([db_hpx_LIBS])
])
