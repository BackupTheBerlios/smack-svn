SUBDIRS = om pixmaps

bin_PROGRAMS = smack
smack_SOURCES = gui.c gui.h gui-drum.c gui-drum.h phat-fan-slider-pix.c phat-fan-slider-pix.h cmdline.c cmdline.h
smack_LDFLAGS = $(GTK_LIBS) $(PHAT_LIBS) $(LOSC_LIBS)
smack_CFLAGS = $(GTK_CFLAGS) $(PHAT_CFLAGS) $(LOSC_CFLAGS) -DPKGDATADIR=\"$(pkgdatadir)\"
DESTDIR = $(INSTALL_ROOT)
DISTFN = $(distdir)

