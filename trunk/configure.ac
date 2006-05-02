# configure.in for smack
AC_INIT([smack],[0.3],[loki@berlios.de])
#AC_CONFIG_SRCDIR([gui.c])

AM_INIT_AUTOMAKE

# Check for ladspa.h
AC_CHECK_HEADER(ladspa.h, , AC_MSG_ERROR([Smack requires LADSPA - you do not seem to have ladspa.h]))

PIXDIR_UNQUOTED="\$(pkgdatadir)/pixmaps/" # for pixmap/Makefile.am

# Write it!
AC_CONFIG_FILES([Makefile pixmaps/Makefile om/Makefile om/smack808/Makefile om/smack909/Makefile om/smackfm/Makefile om/supersmack/Makefile om/smacknoisy/Makefile om/smackmonkey/Makefile])
AC_OUTPUT
