#pragma "$Id$"
// DrawWaveformThread.cpp: implementation of the DrawWaveformThread class.
//
//////////////////////////////////////////////////////////////////////
#include <qapplication.h> 
#include "DrawWaveformThread.h"
#include "CRTDglob.h"
#include "Preview.h"
// #include "qcustomevent.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DrawWaveformThread::DrawWaveformThread():QThread()
{
}

DrawWaveformThread::~DrawWaveformThread()
{
}

void DrawWaveformThread::Init(MainFrame *p)
{
	pMF = p;

    connect(this, SIGNAL(drawPreviewSignal()), pMF->pPreview, SLOT(drawPreviewSlot()) );
    connect(this, SIGNAL(drawWaveformsSignal()), pMF->pDisplay, SLOT(drawWaveformsSlot()) );
}

void DrawWaveformThread::run()
{
	int nTimerCount=nRefreshTime;

	CRTDisplay *pRTDisplay = pMF->pDisplay;
	CPreview *pPreview      = pMF->pPreview;

	while(bContinue)
    {
        for(int i=0; i<10; ++i)
        {
            QThread::msleep(100);

            if(g_bForceRedraw)
            {
                emit drawPreviewSignal();
                g_bForceRedraw = false;
            }

            if(g_bForceRedrawWaveforms)
            {
                emit drawWaveformsSignal();
                g_bForceRedrawWaveforms = false;
            }
        }


		if(nTimerCount++==nRefreshTime)
        {
            emit drawWaveformsSignal();
            emit drawPreviewSignal();
			nTimerCount=0;
        }

    }

	return;
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
