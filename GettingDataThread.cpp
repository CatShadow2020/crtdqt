#pragma "$Id$"
// GettingDataThread.cpp: implementation of the GettingDataThread class.
//
//////////////////////////////////////////////////////////////////////
#include <qapplication.h>
#include "GettingDataThread.h"
#include "CRTDglob.h"
#include "isi.h"
#include "util.h"
#include "MainFrame.h"



GettingDataThread::GettingDataThread()
	{
	}

GettingDataThread::~GettingDataThread()
	{
	}

void GettingDataThread::Init(MainFrame *p)
	{
	pMF = p;
	}


void GettingDataThread::run()
	{
	MainFrame *pParent=pMF;
	CRTDisplay *pDisplay=pMF->pDisplay;

	ISI *isi=NULL;
	
	int status;
	ISI_GENERIC_TS *ts;
	ISI_DATA_REQUEST *dreq;
	double beg = ISI_NEWEST;
	double end = ISI_KEEPUP;
	int compress  = ISI_COMP_IDA;
	int format    = ISI_FORMAT_GENERIC;
    char streamBuff[10000];

	char *StreamSpec;
	QString streams;

	ISI_PARAM par;

	double dstime;

	CMWindow *pWaveI;


	IsiInterruptT.Init(&isi);
	DrawT.Init(pParent);
	DrawT.start(QThread::NormalPriority);
	IsiInterruptT.start(QThread::NormalPriority);

	dstime = time(NULL);
	

	beg=dstime - nBufferedTime;

	utilNetworkInit();
	isiInitDefaultPar(&par);
	par.port = nNrtsPort;

    QList<CMWindow * >::Iterator i;
    for ( i=pDisplay->WaveformInfo.begin(); i!=pDisplay->WaveformInfo.end(); ++i)
    {
        pWaveI = *i;
		QString channelName="+";
		channelName+=pWaveI->StaName+"."+pWaveI->ChanName+"."+pWaveI->LCODE;
		streams+=channelName;
    }
    strcpy(streamBuff, (char *)streams.toLocal8Bit().data());

	while(bContinue)
		{

        if ((dreq = isiAllocSimpleDataRequest(beg, end, streamBuff)) == NULL)
			{
			continue;
			}
		isiSetDatreqFormat(dreq, format);
		isiSetDatreqCompress(dreq, compress);

		if(!bContinue) break;

        if ((isi = isiInitiateDataRequest((char *)server.toLocal8Bit().data(), &par, dreq)) == NULL)
			{
			continue;
			}

		isiFreeDataRequest(dreq);

		if(!bContinue) break;

		while ( bContinue) 
			{

			ts = isiReadGenericTS(isi, &status);

			if(status == ISI_ERROR) continue;
			if(status == ISI_BREAK) break;
			if(status == ISI_DONE) break;

			char *sta, *chan, *loc;
			double sint;

			sint = isiSrateToSint(&ts->hdr.srate);

			sta  = ts->hdr.name.sta;
			chan = ts->hdr.name.chn;
			loc  = ts->hdr.name.loc;

			int nsamp = ts->hdr.nsamp;
            INT32 *data = (INT32 *)ts->data;

     //       utilSwapINT32((UINT32 *) ts->data, nsamp);


		pDisplay->Critical.lock();

        for ( i=pDisplay->WaveformInfo.begin(); i!=pDisplay->WaveformInfo.end(); ++i)
        {
            pWaveI = *i;
			if( (pWaveI->StaName.compare(sta)==0) &&
				(pWaveI->ChanName.compare(chan)==0) &&
				(pWaveI->LCODE.compare(loc))==0)
				{

				CDataBlock *xfd=new CDataBlock;
				if(xfd!=NULL)
					{
                    xfd->PutData(nsamp, (INT32 *)data);

					strcpy(xfd->sname,sta);
					xfd->lat   = 0.;
					xfd->lon   = 0.;
					xfd->elev  = 0.;
					xfd->depth = 0.;

					strcpy(xfd->cname, chan);
					xfd->sint  = sint;
					xfd->beg   = ts->hdr.tofs.value;
					xfd->tear  = 0;
					xfd->nsamp = nsamp;
					xfd->end   = ts->hdr.tols.value;

					pWaveI->Add(xfd);
					break;
					}
				}
        }
		pDisplay->Critical.unlock();

		}
	}
//	isiDestroyGenericTS(ts);
	

	DrawT.wait();
	IsiInterruptT.wait();
	StopDatavisualization();

	}

void GettingDataThread::StopDatavisualization()
	{
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