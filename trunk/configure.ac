# configure.in for smack
AC_INIT([smack],[0.0.1],[loki@berlios.de])
AC_CONFIG_SRCDIR([gui.c])

AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE

# Checks for compilers
AC_PROG_CXX

AC_ENABLE_STATIC(no)
AC_ENABLE_SHARED(yes)
AC_LIBTOOL_DLOPEN
AC_PROG_LIBTOOL
# Check for standard lib stuff
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h unistd.h])
AC_CHECK_FUNCS([strdup strndup])

# Check random other stuff
AC_C_CONST
AC_C_INLINE
AC_FUNC_MALLOC
AC_HEADER_STDBOOL
AC_TYPE_SIGNAL
AC_TYPE_SIZE_T

# Check for ladspa.h
AC_CHECK_HEADER(ladspa.h, , AC_MSG_ERROR([Smack requires LADSPA - you do not seem to have ladspa.h]))

# Check for liblo
PKG_CHECK_MODULES(LOSC, liblo >= 0.16)
AC_SUBST(LOSC_LIBS)
AC_SUBST(LOSC_CFLAGS)

PKG_CHECK_MODULES(GTK, gtk+-2.0)
AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)
PKG_CHECK_MODULES(PHAT, phat)
AC_SUBST(PHAT_CFLAGS)
AC_SUBST(PHAT_LIBS)
AC_SUBST(LIBTOOL)



CXXFLAGS="-O0 -g -ansi -pedantic -Wall -DNDEBUG"

# Write it!
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
