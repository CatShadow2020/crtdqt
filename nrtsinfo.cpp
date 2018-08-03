#pragma "$Id$"
// NRTSINFO.cpp: implementation of the CNRTSINFO class.
//
//////////////////////////////////////////////////////////////////////

#include "platform.h"
#include "isi.h"
#include "util.h"

#include "nrtsinfo.h"
#include "CRTDglob.h"
#include <memory.h>
#include <qsettings.h>
#include <qfile.h>
#include <qmessagebox.h>
#include <qobject.h>
#include <QTextStream>
#include <QDebug>
#include <QFileInfo>
#include <QDir>


const QString WINDOWS_REGISTRY = "/nrtsutil/CRTD";
const QString APP_KEY_C = "/display/";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNRTSINFO::CNRTSINFO(CNRTSINFO &Info)
	{
	CopyFrom(Info);
	}


CNRTSINFO::CNRTSINFO()
	{
    qDebug("CNRTSINFO::CNRTSINFO()");
	}
void CNRTSINFO::CopyFrom(CNRTSINFO &Info)
	{
	
	CNRTSSTAINFO *si;
	CNRTSCHANINFO *ci;

	Clear();

	int nStations = Info.StaInfo.count();

    QMap<QString, CNRTSSTAINFO * >::Iterator i;
    QMap<QString, CNRTSCHANINFO * >::Iterator j;

    for(i=Info.StaInfo.begin(); i!=Info.StaInfo.end(); ++i )
    {
        si = i.value();
		int nChannels = si->ChanInfo.count();
        for(j=si->ChanInfo.begin(); j!=si->ChanInfo.end(); ++j)
        {
            ci = *j;
			AddStaChan(si->Sta, ci->Chan, ci->LCODE, ci->dSpS, ci->bSelected);
        }
    }

	}
CNRTSINFO & CNRTSINFO::operator =(CNRTSINFO & Info)
	{
	CopyFrom(Info);
	return *this;
	}

void CNRTSINFO::AddStaChan(QString &sSta, QString &sChan, QString &csLCODE,  double dSpS, BOOL bSel=FALSE)
{
	CNRTSSTAINFO *si;
	CNRTSCHANINFO *ci;
    QList<CNRTSSTAINFO * >::Iterator i;
    QList<CNRTSCHANINFO * >::Iterator j;

    if(StaInfo.contains(sSta))
    {
        si = StaInfo.value(sSta);
        QString sKey = sChan + "." + csLCODE;
        if( si->ChanInfo.contains(sKey) ) return;
        si->AddChan(sChan, csLCODE, dSpS, bSel);
        return;
    }
    si=new CNRTSSTAINFO( sSta );
	si->AddChan(sChan, csLCODE, dSpS, bSel);

    StaInfo[sSta] = si;
}
/* 
void CNRTSINFO::LoadConfigFromIni()
	{
	char cSta[16],cChan[16];
	int nStations=GetPrivateProfileInt("-STATIONS-","N",0,pIniFile);
	CNRTSSTAINFO *si;

	LoadConfig();
	return;
	Clear();

	for(int i=0; i<nStations; ++i)
		{
		char cStaIndex[64];
		sprintf(cStaIndex,"STATION%d",i);
		GetPrivateProfileString("-STATIONS-",cStaIndex,"",cSta,sizeof(cSta),pIniFile);

		if(*cSta==0) continue;
		int nChan=GetPrivateProfileInt(cSta,"N",0,pIniFile);
		
		si=new 	CNRTSSTAINFO(cSta);

		for(int j=0; j<nChan; ++j)
			{
			char cChanIndex[64],cSpS[16],csLC[16];
			double dSpS;
			sprintf(cChanIndex,"CH%d",j);
			GetPrivateProfileString(cSta,cChanIndex,"",cChan,sizeof(cChan),pIniFile);

			sprintf(cChanIndex,"CH%d.LCODE",j);
			GetPrivateProfileString(cSta,cChanIndex,"",csLC,sizeof(csLC),pIniFile);

			if(*csLC==0)
				{
				csLC[0]=csLC[1]=' ';
				csLC[2]=0;
				}

			sprintf(cChanIndex,"CH%d.SpS",j);
			GetPrivateProfileString(cSta,cChanIndex,"",cSpS,sizeof(cSpS),pIniFile);

			dSpS=atof(cSpS);
			sprintf(cChanIndex,"CH%d.Selected",j);


			int nsel=GetPrivateProfileInt(cSta,cChanIndex,0,pIniFile);
			BOOL bSelected;
			if(nsel==0)
				{
				bSelected=FALSE;
				}
			else
				{
				bSelected=TRUE;
				}

			si->AddChan(cChan, csLC, dSpS, bSelected);
			}
		StaInfo.append(si);
		}
	}
void CNRTSINFO::SaveConfigToIni()
	{
	CNRTSSTAINFO *si;
	CNRTSCHANINFO *ci;

	int i=0, j;
	char cSta[16],cChan[16],cBuff[128];

	int nStations=StaInfo.count();

	sprintf(cBuff,"%d",nStations);
	WritePrivateProfileString("-STATIONS-","N",cBuff,pIniFile);

	for(si=StaInfo.first(); si; si=StaInfo.next(),++i)
		{
		char cStaIndex[64];
		sprintf(cStaIndex,"STATION%d",i);
		lstrcpy(cSta,si->Sta);
		WritePrivateProfileString("-STATIONS-",cStaIndex,cSta,pIniFile);

		int nChan=si->ChanInfo.count();
		sprintf(cBuff,"%d",nChan);
		WritePrivateProfileString(cSta,"N",cBuff,pIniFile);
		j=0;
		for(ci=si->ChanInfo.first();ci; ci=si->ChanInfo.next(),++j)
			{
			char cChanIndex[64],cSpS[16],*pSelected;
			sprintf(cChanIndex,"CH%d",j);
			lstrcpy(cChan,ci->Chan);
			WritePrivateProfileString(cSta,cChanIndex,cChan,pIniFile);

			sprintf(cChanIndex,"CH%d.SpS",j);
			sprintf(cSpS,"%.4f",ci->dSpS);
			WritePrivateProfileString(cSta,cChanIndex,cSpS,pIniFile);


			sprintf(cChanIndex,"CH%d.LCODE",j);
			WritePrivateProfileString(cSta,cChanIndex,ci->LCODE,pIniFile);


			if(ci->bSelected)
				{
				pSelected="1";
				}
			else
				{
				pSelected="0";
				}
			sprintf(cChanIndex,"CH%d.Selected",j);
			WritePrivateProfileString(cSta,cChanIndex,pSelected,pIniFile);

			}


		}
	SaveConfig();
	}
*/





void CNRTSINFO::LoadConfigFromFile()

	{
	QString qsSta, qsChan, qsLcode;
	char cSta[10], cChan[10], cLcode[10],  cbuff[128];
	float dSpS;
	int bSelected;
	FILE *f;
	int i=0;
	QString qs;
	Clear();
    QString fullPath = QDir::homePath()+"/"+qParamFileName;

    qDebug("void CNRTSINFO::LoadConfigFromFile()");
    f=fopen(fullPath.toLocal8Bit().data(),"r");
	if(f==NULL) return;



	while(fgets(cbuff, sizeof(cbuff)-2, f)!=NULL)
		{
		sscanf(cbuff,"%s %s %s %f %d", cSta, cChan, cLcode, &dSpS, &bSelected);
		qsSta=cSta;
		qsChan=cChan;
		qsLcode=cLcode;
		if(qsLcode.compare("__")==0) qsLcode="  ";
		AddStaChan(qsSta, qsChan, qsLcode, dSpS, bSelected);
		}
	fclose(f);
	}



/*
void CNRTSINFO::LoadConfigFromFile()
	{
	char cSta[10], cChan[10], cLcode[10];
	double dSpS;
	BOOL bSelected;
	QFile f;


	int i=0;
	QString qs;

	Clear();

	f.setName(qParamFileName);


	if(!f.open(IO_ReadOnly))
		{
        QMessageBox::critical(
                NULL,
				"Open failed",
                "Could not open file for writing: "+qParamFileName
                );
            return;
		}
	while(f.readLine(qs, 128)>0)
		{
		QString qsSta, qsChan, qsLcode;
		sscanf(qs.latin1(),"%s %s %s %f %d", cSta, cChan, cLcode, &dSpS, &bSelected);
		qsSta=cSta;
		qsChan=cChan;
		qsLcode=cLcode;
		if(qsLcode.compare("__")==0) qsLcode="  ";
		AddStaChan(qsSta, qsChan, qsLcode, dSpS, bSelected);
		}

	f.close();

	}*/
void CNRTSINFO::SaveConfigToFile()
	{
    QString sFile = QDir::homePath()+"/"+qParamFileName;
    QFile f(sFile);
	CNRTSSTAINFO *si;
	CNRTSCHANINFO *ci;

	QString qs;

    if(!f.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(
                NULL,
				"Open failed",
                "Could not open file for writing: "+qParamFileName
                );
            return;
    }
    QMap< QString, CNRTSSTAINFO  * >::Iterator i;
    QMap< QString, CNRTSCHANINFO * >::Iterator j;
    QTextStream out(&f);



    for(i=StaInfo.begin(); i!=StaInfo.end(); ++i)
		{
        si = i.value();
        for(j=si->ChanInfo.begin(); j!=si->ChanInfo.end(); ++j)
			{
            ci=*j;
			QString lcode;
			if(ci->LCODE.compare("  ")==0)
				lcode="__";
			else
				lcode=ci->LCODE;
            qs.sprintf("%s %s %s %f %d\n", si->Sta.toLocal8Bit().data(), ci->Chan.toLocal8Bit().data(), lcode.toLocal8Bit().data(), ci->dSpS, ci->bSelected);
//            f.writeData(qs.toLocal8Bit().data(), qs.length());
            out << qs;
			}


		}
	f.close();
	}


void CNRTSINFO::SaveConfig()
{
	bool b;
    QSettings settings("crtd.ini", QSettings::IniFormat);

	CNRTSSTAINFO *si;
	CNRTSCHANINFO *ci;


	QString qs;

#ifdef WIN32
//	settings.insertSearchPath( QSettings::Windows, "CRTD" /*WINDOWS_REGISTRY*/);
#else
//	settings.insertSearchPath( QSettings::Unix, "./" );
#endif

    QMap<QString, CNRTSSTAINFO * >::Iterator i;
    QMap<QString, CNRTSCHANINFO * >::Iterator j;

    settings.remove(APP_KEY_C);
    for(i=StaInfo.begin(); i!=StaInfo.end(); ++i)
    {
        si = i.value();
        for(j=si->ChanInfo.begin(); j!=si->ChanInfo.end(); ++j)
        {
            ci=*j;
            qs.sprintf("%s/%s/%s/SPS", si->Sta.toLocal8Bit().data(), ci->Chan.toLocal8Bit().data(), ci->LCODE.toLocal8Bit().data());
            settings.setValue(APP_KEY_C + qs, ci->dSpS);
            qs.sprintf("%s/%s/%s/ON", si->Sta.toLocal8Bit().data(), ci->Chan.toLocal8Bit().data(), ci->LCODE.toLocal8Bit().data());
            settings.setValue(APP_KEY_C + qs, ci->bSelected);
        }


    }

}

void CNRTSINFO::LoadConfig()
	{
	double dSpS;
	BOOL bSelected;
	QStringList stalist, chanlist, lcodelist;
	QSettings settings;
	CNRTSSTAINFO *si;
	QString qs;

	Clear();


#ifdef WIN32
//	settings.insertSearchPath( QSettings::Windows, WINDOWS_REGISTRY);
#else
//	settings.insertSearchPath( QSettings::Unix, "./" );
#endif

/*	stalist = settings.subkeyList(APP_KEY_C);

	QStringList::Iterator it = stalist.begin();
    for( ;it != stalist.end(); ++it) 
		{
		si=new 	CNRTSSTAINFO((*it).ascii());
		qs = APP_KEY_C+*it+"/aru";
		chanlist = settings.subkeyList(qs);
		QStringList::Iterator chanit = chanlist.begin();
		while( chanit != chanlist.end() ) 
			{
			QString qChan = (*chanit).ascii();
			qs = APP_KEY_C+*it+"/"+qChan;
			lcodelist = settings.subkeyList(qs);
			QStringList::Iterator lcodeit = lcodelist.begin();
			while( lcodeit != lcodelist.end() ) 
				{
				qs = APP_KEY_C+*it+"/"+*chanit+"/"+*lcodeit+"/SPS";
				dSpS = settings.readDoubleEntry(qs,1);
				qs = APP_KEY_C+*it+"/"+*chanit+"/"+*lcodeit+"/ON";
				bSelected = settings.readBoolEntry(qs,0);
				si->AddChan(*chanit, *lcodeit, dSpS, bSelected);
				++lcodeit;
				}
			++chanit;
			}
		StaInfo.append(si);
		}
*/
	}

int CNRTSINFO::LoadConfigFromServer()
	{
	int i;
/*	CWaitCursor cw;*/
	Clear();

	ISI_PARAM par;

    utilNetworkInit();
    isiInitDefaultPar(&par);

	

	ISI_CNF_REPORT *report;

	par.port = nNrtsPort;

//    if ((report = isiCnf((char *)(LPCSTR)server, &par)) == NULL) 
    if ((report = isiCnf((char*)server.toLocal8Bit().data(), &par)) == NULL)
		{
		return 0;
		}


    for (i = 0; i < report->nentry; i++)
		{
		float sps;
		QString sta, chan, clcode;
		double sint;

		sta    = report->entry[i].name.sta;
		chan   = report->entry[i].name.chn;
		clcode = report->entry[i].name.loc;

		sint = isiSrateToSint(&report->entry[i].srate);


		if(report->entry[i].srate.factor<0)
			{
			sps  = (double)report->entry[i].srate.multiplier;
			}
		else
			{
			sps  = (double)report->entry[i].srate.multiplier*(double)report->entry[i].srate.factor;
			}
		AddStaChan(sta, chan, clcode, sps);
		}
	isiFreeCnf(report);


/*	for (int ich = 0; ich < (int) channelList.length; ich++)
		{
		char *sta = 0; 
		char *chan = 0;
		sta = strdup(channelList.channel[ich].name);
		if ( (chan = strchr(sta, '.')) == NULL ) 
			{
			free(sta);
			continue;
			}
		*chan++ = '\0';
		AddStaChan(sta, chan, -1.);
		free(sta);
		}
	closesocket (NSocket);
	bContinue = FALSE;*/
	return 1;
	}
void CNRTSINFO::Clear()
{
    QMap <QString, CNRTSSTAINFO *>::Iterator i;
    CNRTSSTAINFO *si=NULL;

    if(StaInfo.empty()) return;

    for(i = StaInfo.begin(); i!=StaInfo.end(); ++i)
    {
        si = i.value();
        if(si==NULL) return;
		delete si;
    }

    StaInfo.clear();
}


CNRTSINFO::~CNRTSINFO()
{
	Clear();
}

int CNRTSINFO::GetSelectedChanNumber()
{
	QString			sSta,sChan;
	CNRTSSTAINFO	*si;
	CNRTSCHANINFO	*ci;

	int nStations=0, nChannels=0, nSelected=0;
    QMap<QString, CNRTSSTAINFO * >::Iterator i;
    QMap<QString, CNRTSCHANINFO * >::Iterator j;

    for(i=StaInfo.begin(); i!=StaInfo.end(); ++i)
    {
        si = *i;
        sSta=si->Sta;
        for(j=si->ChanInfo.begin(); j!=si->ChanInfo.end(); ++j)
        {
            ci=*j;
			if(ci->bSelected)
            {
				++nSelected;
            }
        }
    }
	return nSelected;
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
