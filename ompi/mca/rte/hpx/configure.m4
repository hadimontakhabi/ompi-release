# -*- shell-script -*-
#
# Copyright (c) 2012      Los Alamos National Security, LLC.  All rights reserved.
# Copyright (c) 2013      Sandia National Laboratories. All rights reserved.
#
# $COPYRIGHT$
# 
# Additional copyrights may follow
# 
# $HEADER$
#

# Highest priority, as it's the default
AC_DEFUN([MCA_ompi_rte_hpx_PRIORITY], [100])

# Force this component to compile in static-only mode
AC_DEFUN([MCA_ompi_rte_hpx_COMPILE_MODE], [
    AC_MSG_CHECKING([for MCA component $2:$3 compile mode])
    $4="static"
    AC_MSG_RESULT([$$4])
])

# If component was selected, $1 will be 1 and we should set the base header
AC_DEFUN([MCA_ompi_rte_hpx_POST_CONFIG],[
    AS_IF([test "$1" = "1"], [ompi_rte_base_include="hpx/rte_hpx.h"])
    AC_DEFINE_UNQUOTED([OMPI_RTE_HPX], [$1],
        [Defined to 1 if the OMPI runtime component is HPX])
    AM_CONDITIONAL([OMPI_RTE_HPX], [test $1 = 1])
])

# MCA_rte_hpx_CONFIG([action-if-can-compile], 
#                     [action-if-cant-compile])
# ------------------------------------------------
AC_DEFUN([MCA_ompi_rte_hpx_CONFIG],[
    AC_CONFIG_FILES([ompi/mca/rte/hpx/Makefile])

    OMPI_CHECK_HPX([rte_hpx], [rte_hpx_good=1], [rte_hpx_good=0])
         
    # Evaluate succeed / fail
    AS_IF([test "$rte_hpx_good" = 1],
          [$1],
          [$2])

    # set build flags to use in makefile
    AC_SUBST([rte_hpx_CPPFLAGS])
    AC_SUBST([rte_hpx_CXXFLAGS])
    AC_SUBST([rte_hpx_LDFLAGS])
    AC_SUBST([rte_hpx_LIBS])
])
