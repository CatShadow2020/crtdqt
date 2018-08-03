#pragma "$Id$"
#include <QMenu>
#include <qpixmap.h>
#include <qapplication.h>
#include <qmainwindow.h> 
#include <qmenubar.h>
#include <qlineedit.h> 
#include <qsettings.h>
#include "MainFrame.h"
#include "CRTDglob.h"


QString WINDOWS_REGISTRY = "/nrtsutil/CRTD/display/";
const QString APP_KEY_C = "/display/";

bool bPrintUsage=false;
void PrintUsage();
void ParseCmd(int argc,char *argv[]);

void LoadConfig()
	{
	double dSpS;
	BOOL bSelected;
	QStringList stalist, chanlist, lcodelist;
	QSettings settings;

	CNRTSSTAINFO *si;

	QString qs;



#ifdef WIN32
//	settings.insertSearchPath( QSettings::Windows, WINDOWS_REGISTRY);
#else
	//settings.insertSearchPath( QSettings::Unix, "./" );
#endif
/*
	settings.beginGroup(WINDOWS_REGISTRY);
	stalist = settings.subkeyList(0);

	QStringList::Iterator it = stalist.begin();
    for( ;it != stalist.end(); ++it) 
		{
        si=new 	CNRTSSTAINFO((*it).toLocal8Bit().data());
        qs = APP_KEY_C+*it;
		settings.beginGroup(*it);
		chanlist = settings.subkeyList(0);
		QStringList::Iterator chanit = chanlist.begin();
		while( chanit != chanlist.end() ) 
			{
			QString qChan = (*chanit).ascii();
			settings.beginGroup(*chanit);
			lcodelist = settings.subkeyList(0);
			QStringList::Iterator lcodeit = lcodelist.begin();
			while( lcodeit != lcodelist.end() ) 
				{
				settings.beginGroup(*lcodeit);
				lcodelist = settings.subkeyList(0);

				dSpS = settings.readDoubleEntry(qs,1);
				bSelected = settings.readBoolEntry(qs,0);
				si->AddChan(*chanit, *lcodeit, dSpS, bSelected);
				++lcodeit;
				settings.endGroup();
				}
			++chanit;
			settings.endGroup();
			}
		settings.endGroup();
		}
	settings.endGroup();
*/
	}



int main(int argc,char *argv[])
	{
    qDebug("MAIN !!!");
	QApplication a( argc, argv );


	ParseCmd(argc,argv);
	if(bPrintUsage) 
		{
		PrintUsage();
		return 0;
		}
	nFontSize = 12;

	QFont f("times", nFontSize);
    a.setFont ( f );

//	LoadConfig();
	LoadGlobalParam();
    qDebug("before NrtsInfo.LoadConfigFromFile()");
	NrtsInfo.LoadConfigFromFile();

    MainFrame mw( 0);
    mw.show();
	a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
 //   a.setCentralWidget( &mw );

	a.exec();

	return 0;
	}

void ParseCmd(int argc,char *argv[])
	{
	QString qSc;
    qDebug("ParseCmd");
	for(int i=0; i<argc; ++i)
		{
		QString s=argv[i];
        s = s.toUpper();

        if(qstrncmp(s.toLocal8Bit().data(), "-FONTSIZE=",10) ==0)
			{
			s=s.remove(0,10);
			nFontSize = s.toLong();
			if(nFontSize<6||nFontSize>15) nFontSize=10;
			continue;
			}

        if(qstrncmp(s.toLocal8Bit().data(),"CHLIST=",7) ==0)
			{
			qParamFileName = s.remove(0,7); 
			continue;
			}

        if(qstrncmp(s.toLocal8Bit().data(),"-H",2) ==0)
			{
			bPrintUsage = true;
			return;
			}


		}
	}
void PrintUsage()
	{
	QMessageBox::information(NULL, "CRTDQT(ISI)",
"\nUsage: crtdqt [-help] [-chlist=<file name>] [-fontsize=<6..15>]"
"\nwhere	-help display this help message"
"\n	-chlist=file name to save/restore downloaded from NRTS server channel list"
"\n	-fonsize=desired font size. Integer value between 6 and 15. ",QMessageBox::Information
	);
	}
/*-----------------------------------------------------------------------+
 |                                                                       |
 | Copyright (C) 2016 Regents of the University of California            |
 |                                                                       |
 | This software is provided 'as-is', without any express or implied     |
 | warranty.  In no event will the authors be held liable for any        |
 | damages arising from the use of this software.                        |
 |                                                                       |
 | Permission is granted to anyone to use this software for any purpose, |
 | including commercial applications, and to alter it and redistribute   |
 | it freely, subject to the following restrictions:                     |
 |                                                                       |
 | 1. The origin of this software must not be misrepresented; you must   |
 |    not claim that you wrote the original software. If you use this    |
 |    software in a product, an acknowledgment in the product            |
 |    documentation of the contribution by Project IDA, UCSD would be    |
 |    appreciated but is not required.                                   |
 | 2. Altered source versions must be plainly marked as such, and must   |
 |    not be misrepresented as being the original software.              |
 | 3. This notice may not be removed or altered from any source          |
 |    distribution.                                                      |
 |                                                                       |
 +-----------------------------------------------------------------------*/
/* Revision History
 *
 * $Log$
 */
