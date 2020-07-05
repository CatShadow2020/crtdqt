#pragma "$Id$"
// GettingDataThread.h: interface for the GettingDataThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_GETTINGDATATHREAD_H_)
#define _GETTINGDATATHREAD_H_

#include <qthread.h>
#include "MainFrame.h"
#include "DrawWaveformThread.h"
#include "IsiInterruptThread.h"


class GettingDataThread : public QThread  
{
public:
	GettingDataThread();
	virtual ~GettingDataThread();
	void Init(MainFrame *p);
	virtual void run();
	MainFrame *pMF;

private:
	IsiInterruptThread    IsiInterruptT;
	DrawWaveformThread    DrawT;

private:
	void StopDatavisualization();

};

#endif // !defined(_GETTINGDATATHREAD_H_)
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