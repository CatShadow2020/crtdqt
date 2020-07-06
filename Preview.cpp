// Preview.cpp : implementation file
//
#include <qapplication.h>
#include <QMouseEvent>
#include "Preview.h"
#include "CRTDglob.h"
#include <math.h>
#include "MainFrame.h"
#include "util.h"
#include <qpainter.h> 

/////////////////////////////////////////////////////////////////////////////
// CPreview

CPreview::CPreview(CRTDisplay *pDisplay, QWidget * parent = 0)
    :QWidget(parent )
{
    this->pDisplay=pDisplay;
    bDrawBitmap=FALSE;
    setMouseTracking(TRUE);

    MainFrame *pParent=(MainFrame *)parent;
    connect(this, SIGNAL(setTimeInfo(QString)), pParent, SLOT(SetTextToStatusbarSlot(QString)) );

}

CPreview::~CPreview()
{
}

/////////////////////////////////////////////////////////////////////////////
// CPreview message handlers

void CPreview::paintEvent(QPaintEvent *) 
{
    if(bContinue)
    {
        ScreenBitmapCriticalSection.lock();
        if(bDrawBitmap)
        {
            QPainter paint( this );
            paint.drawPixmap(0,0, Bitmap);
        }
        ScreenBitmapCriticalSection.unlock();
    }
}

void CPreview::resizeEvent(QResizeEvent * )
{
    DrawPreviewBitmap();
}

void CPreview::DrawPreviewBitmap()
{
    if(!bContinue) return;


    MaxX=width();
    MaxY=height();
    QPixmap tmpBitmap(MaxX, MaxY);
    QPainter DC(&tmpBitmap);
    QRect rc=rect();

    x1=4;
    x2=MaxX-4;
    y1=4;
    y2=MaxY-4;

    xw1=1;
    xw2=MaxX;
    yw1=0;
    yw2=MaxY;


    QBrush WhiteBrush(QColor(255,255,255));
    QBrush GrayBrush(QColor(192,192,192));
    QBrush BlueBrush(QColor(0,0,255));

    QPen WhitePen(QColor(255,255,255));
    QPen DarkPen(QColor(0,0,0));
    QPen BluePen(QColor(0,0,255));
    QPen YellowPen(QColor(255,255,0));
    QPen WhitePen2(QColor(255,255,255),2);
    QPen GrayPen2(QColor(128,128,128),2);


    //********************************************************************
    DC.setPen(BluePen);
    DC.fillRect(rc, BlueBrush);
    //	DC.SelectObject(CFont::FromHandle((HFONT)GetStockObject(ANSI_VAR_FONT)));


    int xl=(int)((pDisplay->t1 - pDisplay->tB1)*(x2-x1)/(pDisplay->tB2-pDisplay->tB1)+x1+0.5);
    int xr=(int)((pDisplay->t2 - pDisplay->tB1)*(x2-x1)/(pDisplay->tB2-pDisplay->tB1)+x1+0.5);

    DC.setPen(WhitePen2);

    DC.drawLine(xw1,MaxY-yw2, xw2,MaxY-yw2);

    DC.drawLine(xw1,MaxY-yw2, xw1,MaxY-yw1);

    DC.setPen(GrayPen2);

    DC.drawLine(xw2,MaxY-yw1, xw2, MaxY-yw2);

    DC.drawLine(xw2,MaxY-yw1, xw1,MaxY-yw1);

    DrawWaveform(DC);

    DC.setPen(WhitePen2);
    DC.drawLine(xl,MaxY-y1, xr,MaxY-y1);
    DC.drawLine(xr,MaxY-y2,xl,MaxY-y2);
    DC.drawLine(xl,MaxY-y2, xl,MaxY-y1);
    DC.drawLine(xr,MaxY-y2, xr,MaxY-y1);


    //********************************************************************

    ScreenBitmapCriticalSection.lock();
    Bitmap=tmpBitmap;
    bDrawBitmap=TRUE;
    ScreenBitmapCriticalSection.unlock();
    repaint();
}
void CPreview::DrawWaveform(QPainter &DC)
{

    int nActiveScreen=pDisplay->nActiveScreen;
    if(nActiveScreen==-1) return;

    double amin=-3000., amax=3000.;
    double ttt=-1.;
    QPen YellowPen(QColor(255,255,0));
    CDataBlock *xfd;
    CMWindow *wfi;
    DC.setPen(YellowPen);

    pDisplay->Critical.lock();

    wfi = pDisplay->WaveformInfo.at(nActiveScreen);

    // find max and min
    BOOL bfirstcount=TRUE;

    QList<CDataBlock *>::Iterator i;

    for( i = wfi->xferData.begin(); i!=wfi->xferData.end(); ++i)
    {
        xfd = *i;
        double t1packet=xfd->beg;
        //		double t2packet=xfd->end;
        int nsamp=xfd->nsamp;
        for(int k=0; k<nsamp; ++k)
        {
            long a=xfd->data[k];
            double tt=t1packet+xfd->sint*k;

            if(tt<pDisplay->tB1) continue;
            if(tt>pDisplay->tB2) break;
            if(!bfirstcount)
            {
                if(a>amax) amax=a;
                if(a<amin) amin=a;
            }
            else
            {
                bfirstcount=FALSE;
                amax=a;
                amin=a;
            }

        }
    }


    //*************************************
    int x_prev=-1, y_prev=-1;
    for( i = wfi->xferData.begin(); i!=wfi->xferData.end(); ++i)
    {
        xfd = *i;
        double t1packet=xfd->beg;
        //		double t2packet=xfd->end;
        int nsamp=xfd->nsamp;
        for(int k=0; k<nsamp; ++k)
        {
            long a=xfd->data[k];
            double tt=t1packet+xfd->sint*k;
            int x,y;

            if(tt<pDisplay->tB1) continue;
            if(tt>pDisplay->tB2) break;

            x=(int)((tt-pDisplay->tB1)*(x2-x1)/(pDisplay->tB2-pDisplay->tB1)+x1+0.5);
            y=(int)((a-amin)*(y2-y1)/(amax-amin)+y1+0.5);
            y=MaxY-y;
            if(tt-ttt>1.1*xfd->sint)
            {
                x_prev = x;
                y_prev = y;
            }
            else
            {
                DC.drawLine(x_prev, y_prev, x,y);
                x_prev = x;
                y_prev = y;

            }
            ttt=tt;
        }
    }
    pDisplay->Critical.unlock();
}

void CPreview::mousePressEvent ( QMouseEvent *e )  
{
    if(!bContinue) return;
    int x=e->x();
    //	int y=MaxY-e->y();
    //	int i=0;

    if(e->button()!= Qt::LeftButton) return;
    if(pDisplay->nActiveScreen==-1) return;
    pDisplay->Critical.lock();

    //	int nActiveScreen=pDisplay->nActiveScreen;
    double tB1=pDisplay->tB1;
    double tB2=pDisplay->tB2;
    //	double t1=pDisplay->t1;
    //	double t2=pDisplay->t2;
    double half=nDisplayedTime/2.;

    double ttt=(x-x1)*(tB2-tB1)/(x2-x1)+tB1;

    pDisplay->t1=floor(ttt-half);
    pDisplay->t2=pDisplay->t1+nDisplayedTime;

    if(pDisplay->t2>tB2)
    {
        pDisplay->t2=tB2;
        pDisplay->t1=tB2-nDisplayedTime;
    }
    if(pDisplay->t1<tB1)
    {
        pDisplay->t1=tB1;
        pDisplay->t2=tB1+nDisplayedTime;
    }

    pDisplay->Critical.unlock();


    DrawPreviewBitmap();

    g_bForceRedrawWaveforms = true;

}
void CPreview::Stop()
{
    ScreenBitmapCriticalSection.lock();
    bDrawBitmap=FALSE;
    ScreenBitmapCriticalSection.unlock();
    repaint();
}

void CPreview::mouseMoveEvent ( QMouseEvent * e ) 
{
    if(!bContinue) return;

    int x=e->x();
    //	int y=MaxY-e->y();

    if(x>=x1 && x<=x2)
    {
        double ttt=(x-x1)*(pDisplay->tB2-pDisplay->tB1)/(x2-x1)+pDisplay->tB1;
        char cBuff[64];
        strcpy(cBuff, util_dttostr(ttt, 1));

        emit setTimeInfo(QString(cBuff));

    }

}

void CPreview::drawPreviewSlot()
{
    DrawPreviewBitmap();
    repaint();
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
