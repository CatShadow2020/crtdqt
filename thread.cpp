#pragma "$Id$"
#include <qapplication.h>
#include "StopAcquisitionThread.h"
#include "RTDisplay.h"
#include "platform.h"
#include "CRTDglob.h"
#include "isi.h"
#include "util.h"
#include "MainFrame.h"
#include "GettingDataThread.h"



static StopAcquisitionThread StopT;
static GettingDataThread GettingDataT;

void StopDatavisualization(MainFrame *pM);



void StopAcquisition(MainFrame *p)
{
	StopT.Init(p);
	StopT.start(QThread::NormalPriority);
}

void StartAcquisition(MainFrame *p)
{
	GettingDataT.Init(p);
	GettingDataT.start(QThread::NormalPriority);
}
void WaitForStop()
{
	GettingDataT.wait();
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