#pragma "$Id$"

#include <qstring.h> 
#include <stdlib.h>
#include <qsettings.h> 
#include "platform.h"
#include "nrtsinfo.h"

bool g_bForceRedraw = FALSE;
bool g_bForceRedrawWaveforms = FALSE;
BOOL bContinue=FALSE;
QString server="fsuhub";
int nNrtsPort=39136;
int nDisplayedTime=60;
int nBufferedTime=3600;
int nRefreshTime=1;
int nDelay=12;
CNRTSINFO		NrtsInfo;

const QString WINDOWS_REGISTRY = "/nrtsutil/CRTD";
const QString APP_KEY_C = "/config/";
bool bShiftButtonPressed=FALSE;


QString qParamFileName="crtdqt.ch";

int nFontSize = 10;


void LoadGlobalParam()
{
    QSettings settings(QSettings::IniFormat,
                       QSettings::UserScope,
                       "IDA",
                       "CRTD");

#ifdef WIN32
//	settings.insertSearchPath( QSettings::Windows, WINDOWS_REGISTRY);
#else
//    settings.insertSearchPath( QSettings::Unix, "./" );
#endif
    qDebug("LoadGlobalParam0");
    server		= settings.value("SERVER", "idahub.ucsd.edu").toString();
    nNrtsPort	= settings.value("PORT",39136).toInt();
    nDisplayedTime	= settings.value("DISPLAYEDTIME",60).toInt();
    nBufferedTime	= settings.value("BUFFEREDTIME",3600).toInt();
    nRefreshTime	= settings.value("REFRESHTIME",1).toInt();
    nDelay	= settings.value("DELAY",12).toInt();
    qDebug("LoadGlobalParam1");

/*	GetPrivateProfileString("-CONFIG-","SERVER","",cBuff,sizeof(cBuff),pIniFile);
	if(*cBuff) server=cBuff;
	GetPrivateProfileString("-CONFIG-","PORT","",cBuff,sizeof(cBuff), pIniFile);
	if(*cBuff) nNrtsPort=atoi(cBuff);

	GetPrivateProfileString("-CONFIG-","DISPLAYEDTIME","",cBuff,sizeof(cBuff), pIniFile);
	if(*cBuff) nDisplayedTime=atoi(cBuff);

	GetPrivateProfileString("-CONFIG-","BUFFEREDTIME","",cBuff,sizeof(cBuff), pIniFile);
	if(*cBuff) nBufferedTime=atoi(cBuff);

	GetPrivateProfileString("-CONFIG-","REFRESHTIME","",cBuff,sizeof(cBuff), pIniFile);
	if(*cBuff) nRefreshTime=atoi(cBuff);

	GetPrivateProfileString("-CONFIG-","DELAY","",cBuff,sizeof(cBuff), pIniFile);
	if(*cBuff) nDelay=atoi(cBuff);*/

}
void SaveGlobalParam()
{
    QSettings settings(QSettings::IniFormat,
                       QSettings::UserScope,
                       "IDA",
                       "CRTD");

    settings.setValue("SERVER", server);
    settings.setValue("PORT",nNrtsPort);
    settings.setValue("DISPLAYEDTIME",nDisplayedTime);
    settings.setValue("BUFFEREDTIME",nBufferedTime);
    settings.setValue("REFRESHTIME",nRefreshTime);
    settings.setValue("DELAY",nDelay);
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
