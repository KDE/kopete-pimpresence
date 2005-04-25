/***************************************************************************
                          pimpresencepreferences.h
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

#ifndef PIMPRSENCEPREFERECES_H
#define PIMPRSENCEPREFERECES_H

#include "kcmodule.h"

class PIMPresencePrefsUI;
class KAutoConfig;

/**
 * Preference widget for the Now Listening plugin, copied from the Cryptography plugin
 * @author Olivier Goffart
 */
class PIMPresencePreferences : public KCModule  {
   Q_OBJECT

public:
	PIMPresencePreferences(QWidget *parent = 0, const char *name = 0, const QStringList &args = QStringList());

	virtual void save();
	virtual void defaults();

private:
	PIMPresencePrefsUI *preferencesDialog;
	KAutoConfig *kautoconfig;

private slots: // Public slots
	void widgetModified();

};

#endif

// vim: set noet ts=4 sts=4 sw=4:
