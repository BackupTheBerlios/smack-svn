bin_PROGRAMS = smack
smack_SOURCES = gui.c gui-drum.c phat-fan-slider-pix.c
smack_LDFLAGS = $(GTK_LIBS) $(PHAT_LIBS) $(LOSC_LIBS)
smack_CFLAGS = $(GTK_CFLAGS) $(PHAT_CFLAGS) $(LOSC_CFLAGS)
plugin_LTLIBRARIES = adenv_lvl.la adenv.la dahdsr_fexp.la dahdsr_hexp.la
smack_DEPENDENCIES = adenv_lvl.la adenv.la dahdsr_fexp.la dahdsr_hexp.la
plugindir = @prefix@/lib/ladspa
adenv_la_LDFLAGS = -module -avoid-version -Wc,-nostartfiles
adenv_la_SOURCES = adenv.c
adenv_lvl_la_LDFLAGS = -module -avoid-version -Wc,-nostartfiles
adenv_lvl_la_SOURCES = adenv_lvl.c
dahdsr_fexp_la_LDFLAGS = -module -avoid-version -Wc,-nostartfiles
dahdsr_fexp_la_SOURCES = dahdsr_fexp.c
dahdsr_hexp_la_LDFLAGS = -module -avoid-version -Wc,-nostartfiles
dahdsr_hexp_la_SOURCES = dahdsr_hexp.c
DESTDIR = $(INSTALL_ROOT)
DISTFN = $(distdir)

