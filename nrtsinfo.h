//////////////////////////////////////////////////////////////////////
// NRTSINFO.h: interface for the CNRTSINFO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_NRTSINFO_H_INCLUDED_)
#define _NRTSINFO_H_INCLUDED_


#include <QString> 
#include <QList>
#include <QSettings>
#include <QMap>

#include "nrtsstainfo.h"

class CNRTSINFO  
{
public:
	CNRTSINFO();
	CNRTSINFO(CNRTSINFO &Info);
	virtual ~CNRTSINFO();

	void AddStaChan(QString &CSta, QString &CChan, QString &csLCODE,double dSpS, BOOL bSel);
	int LoadConfigFromServer();
	
	void Clear();
	void CopyFrom(CNRTSINFO &Info);
	CNRTSINFO & operator =(CNRTSINFO &Info);
	int GetSelectedChanNumber();
	void SaveConfigToFile();
	void LoadConfigFromFile();
	void SaveConfig();
//	void LoadConfig();



public:
    QMap< QString, CNRTSSTAINFO *> StaInfo;


};

#endif // !defined(_NRTSINFO_H_INCLUDED_)
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
