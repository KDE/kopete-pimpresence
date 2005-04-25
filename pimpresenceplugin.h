/*
    pimpresenceplugin.h

    Kopete PIM Presence plugin

    Copyright (c) 2005 by Will Stephenson <will@stevello.free-online.co.uk>

    Kopete    (c) 2002,2003,2004,2005 by the Kopete developers  <kopete-devel@kde.org>

    *************************************************************************
    *                                                                    	*
    * This program is free software; you can redistribute it and/or modify  *
    * it under the terms of the GNU General Public License as published by  *
    * the Free Software Foundation; either version 2 of the License, or     *
    * (at your option) any later version.                                   *
    *                                                                       *
    *************************************************************************
*/

#ifndef PIMPRESENCEPLUGIN_H
#define PIMPRESENCEPLUGIN_H

namespace KCal {
class CalendarResources;
}

#include <qtimer.h>

class PIMPresencePlugin : public Kopete::Plugin
{
	Q_OBJECT

private:
public:
	PIMPresencePlugin( QObject *parent, const char *name, const QStringList &args );
	virtual ~PIMPresencePlugin();

protected slots:
	void loadSettings();
	void slotCheckCalendar();
protected:
	bool eventFallsWithin( const KCal::Event *, const QDateTime & );
	KCal::CalendarResources * m_calendar;
	QTimer m_checkTimer;
	bool m_giveReason;
	bool m_includePrivate;
	QString m_reason;
};

#endif

// vim: set noet ts=4 sts=4 sw=4:
