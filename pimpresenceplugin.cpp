/*
   pimpresenceplugin.cpp

   Kopete PIM Presence plugin

   Copyright (c) 2002,2003 by Will Stephenson <will@stevello.free-online.co.uk>

   Kopete    (c) 2002,2003 by the Kopete developers  <kopete-devel@kde.org>

 *************************************************************************
 *                                                                    	*
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation; either version 2 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 *************************************************************************
 */

#include "config.h"

#include <qdatetime.h>

#include <libkcal/calendarresources.h>
#include <libkcal/event.h>

#include <kstandarddirs.h>
#include <kdebug.h>
#include <kconfig.h>
#include <kgenericfactory.h>

#include <kopeteaccountmanager.h>
#include <kopeteonlinestatusmanager.h>
#include "kopetepluginmanager.h"
#include "kopeteprotocol.h"
#include "kopeteaccountmanager.h"
#include "kopeteaccount.h"

#include "pimpresenceplugin.h"

typedef KGenericFactory<PIMPresencePlugin> PIMPresencePluginFactory;
K_EXPORT_COMPONENT_FACTORY( kopete_pimpresence, PIMPresencePluginFactory( "kopete_pimpresence" )  )

PIMPresencePlugin::PIMPresencePlugin( QObject *parent, const char *name, const QStringList& /*args*/ )
: Kopete::Plugin( PIMPresencePluginFactory::instance(), parent, name )
{
	KConfig c( locate( "config", "korganizerrc" ) );
	c.setGroup( "Time & Date" );
	QString tz = c.readEntry( "TimeZoneId" );
	kdDebug(5890) << "TimeZone: " << tz << endl;

	m_giveReason = true;
	m_includePrivate = false;
	m_reason = "initial_reason";

	m_calendar = new KCal::CalendarResources( tz );
	m_calendar->readConfig();
	m_calendar->load();
	
	connect( &m_checkTimer, SIGNAL( timeout() ), SLOT( slotCheckCalendar() ) );
	connect(this, SIGNAL(settingsChanged()), this, SLOT( loadSettings() ) );
	loadSettings();
	slotCheckCalendar();
	m_checkTimer.start( 5 * 1000 );
}

PIMPresencePlugin::~PIMPresencePlugin()
{
}

void PIMPresencePlugin::loadSettings()
{
/*	KConfig *kconfig = KGlobal::config();
	kconfig->setGroup( "PIM Presence Plugin" );
	
	frequency = kconfig->readNumEntry("UploadFrequency" , 15);
	
	url = kconfig->readPathEntry("uploadURL");
	useDefaultStyleSheet = kconfig->readBoolEntry("formatDefault", true);
	justXml = kconfig->readBoolEntry("formatXML", false);
	userStyleSheet = kconfig->readEntry("formatStylesheetURL");

	useImName = kconfig->readBoolEntry("showName", true);
	userName = kconfig->readEntry("showThisName");
	showAddresses = kconfig->readBoolEntry("includeIMAddress", false);*/
}

void PIMPresencePlugin::slotCheckCalendar()
{
	// TODO: only go away if we are Available?
	QPtrListIterator<Kopete::Account> it = Kopete::AccountManager::self()->accounts();
	bool anyConnected = false;
	for ( ; it.current(); ++it )
		anyConnected |= it.current()->isConnected();

	if ( !anyConnected )
	{
		kdDebug() << "no account connected, not changing status" << endl;
		return;
	}

	KCal::Event::List events = m_calendar->events( QDateTime::currentDateTime() );
	kdDebug() << "there are: " << events.count() << " events occurring today." << endl;
	bool busy = false;
	QString awayReason;
	int count = 0;
	if ( events.count() )
	{
		if ( m_giveReason )
		{
			KCal::Event::List::Iterator it = events.begin();
			for ( ; it != events.end(); ++it )
			{
				// check if the event is currently happening
				if ( !eventFallsWithin( *it, QDateTime::currentDateTime() ) )
					continue;
				++count;
				// we are busy if any event is busy
				if ( (*it)->transparency() == KCal::Event::Opaque )
					busy |= true;
				if ( (*it)->secrecy() != KCal::Incidence::SecrecyPublic && !m_includePrivate )
					continue;
				if ( !awayReason.isEmpty() )
					awayReason += ", ";
				awayReason += (*it)->summary();
			}
		}
	}
	kdDebug() << "there are: " << count << " events occurring right now." << endl;
	if ( awayReason != m_reason )
	{
		m_reason = awayReason;
		if ( busy )
		{
			kdDebug() << "setting away with reason \"" << awayReason << "\"" << endl;
			Kopete::AccountManager::self()->setAwayAll( awayReason );
/*			Kopete::AccountManager::self()->setOnlineStatus( 
					Kopete::OnlineStatusManager::Away, awayReason, 0 );*/
		}
		else
		{
			kdDebug() << "Available now with reason \"" << awayReason << "\"" << endl;
			Kopete::AccountManager::self()->setAvailableAll();
/*			Kopete::AccountManager::self()->setOnlineStatus(
					Kopete::OnlineStatusManager::Online, awayReason, 0 );*/
		}
	}
}

bool PIMPresencePlugin::eventFallsWithin( const KCal::Event *ev, const QDateTime &qdt )
{
	return ( ev->dtStart() <= qdt && ev->dtEnd() >= qdt );
}

// vim: set noet ts=4 sts=4 sw=4:
#include "pimpresenceplugin.moc"
