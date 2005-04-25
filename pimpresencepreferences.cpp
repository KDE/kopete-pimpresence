/***************************************************************************
                          pimpresencepreferences.cpp
                             -------------------
    begin                : jeu nov 14 2002
    copyright            : (C) 2002 by Olivier Goffart
    email                : ogoffart@tiscalinet.be
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <qlayout.h>

#include <kgenericfactory.h>
#include <kautoconfig.h>
#include <kurlrequester.h>

#include "pimpresenceprefs.h"
#include "pimpresencepreferences.h"

typedef KGenericFactory<PIMPresencePreferences> PIMPresencePreferencesFactory;
K_EXPORT_COMPONENT_FACTORY( kcm_kopete_pimpresence, PIMPresencePreferencesFactory("kcm_kopete_pimpresence"))

PIMPresencePreferences::PIMPresencePreferences(QWidget *parent, const char* /*name*/, const QStringList &args)
							: KCModule(PIMPresencePreferencesFactory::instance(), parent, args)
{
	// Add actuall widget generated from ui file.
	( new QVBoxLayout( this ) )->setAutoAdd( true );
	preferencesDialog = new PIMPresencePrefsUI(this);

	// KAutoConfig stuff
	kautoconfig = new KAutoConfig(KGlobal::config(), this, "kautoconfig");
	connect(kautoconfig, SIGNAL(widgetModified()), SLOT(widgetModified()));
	connect(kautoconfig, SIGNAL(settingsChanged()), SLOT(widgetModified()));
    kautoconfig->addWidget(preferencesDialog, "PIM Presence Plugin");
	kautoconfig->retrieveSettings(true);
}

void PIMPresencePreferences::widgetModified()
{
	emit KCModule::changed(kautoconfig->hasChanged());
}

void PIMPresencePreferences::save()
{
	kautoconfig->saveSettings();
}

void PIMPresencePreferences::defaults ()
{
	kautoconfig->resetSettings();
}

#include "pimpresencepreferences.moc"

// vim: set noet ts=4 sts=4 sw=4:
