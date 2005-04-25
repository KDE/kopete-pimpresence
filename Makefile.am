METASOURCES = AUTO

AM_CPPFLAGS = $(KOPETE_INCLUDES) $(all_includes) $(LIBXML_CFLAGS) $(LIBXSLT_CFLAGS)

kde_module_LTLIBRARIES = kopete_pimpresence.la kcm_kopete_pimpresence.la

kopete_pimpresence_la_SOURCES     = pimpresenceplugin.cpp

kopete_pimpresence_la_LDFLAGS     = -module  -no-undefined $(KDE_PLUGIN)
kopete_pimpresence_la_LIBADD = ../../libkopete/libkopete.la -lkcal

kcm_kopete_pimpresence_la_SOURCES = pimpresencepreferences.cpp pimpresenceprefs.ui
kcm_kopete_pimpresence_la_LDFLAGS = -module -no-undefined $(KDE_PLUGIN) $(all_libraries)
kcm_kopete_pimpresence_la_LIBADD  = ../../libkopete/libkopete.la  $(LIB_KUTILS)

service_DATA = kopete_pimpresence.desktop
servicedir = $(kde_servicesdir)

kcm_DATA = kopete_pimpresence_config.desktop
kcmdir = $(kde_servicesdir)/kconfiguredialog

