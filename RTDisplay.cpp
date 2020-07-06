#pragma "$Id$"
// RTDisplay.cpp: implementation of the CRTDisplay class.
//
//////////////////////////////////////////////////////////////////////
#include <qapplication.h>
#include <qvariant.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <QMenu>
#include <qtoolbar.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qpainter.h>

#include "RTDisplay.h"
#include "nrtsinfo.h"
#include "CRTDglob.h"
#include "util.h"
#include "MainFrame.h"


THREAD_FUNC GettingDataThread(void* lpV);

#ifndef max
#define max(x,y)((x<y)?y:x)
#endif
#ifndef min
#define min(x,y)((x>y)?y:x)
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRTDisplay::CRTDisplay(QWidget * parent):QWidget(parent)
{

    QRect rc;
    GetTextRectangle("WgWgWgWgWgWg",rc);
    TimeBarYsize=rc.height()*2+8;
    WindowInfoXsize=rc.width();


    //	int t=rc.top();
    //	int b=rc.bottom();
    //	tmmarks.setAutoDelete(TRUE);
    nActiveScreen = -1;
    bDrawBitmap = FALSE;
    m_autoscale = TRUE;
    setMouseTracking(TRUE);

    MainFrame *pParent=(MainFrame *)parent;
    connect(this, SIGNAL(setTimeInfo(QString)), pParent, SLOT(SetTextToStatusbarSlot(QString)) );
    connect(this, SIGNAL(drawPreviewSignal()),  pParent, SLOT(drawPreviewSlot()) );


    installEventFilter(this);
}

CRTDisplay::~CRTDisplay()
{
    ClearWaveformInfo();
}
void CRTDisplay::ClearWaveformInfo()
{
    while(WaveformInfo.count()>0)
    {
        CMWindow *wfi=WaveformInfo.first();
        WaveformInfo.removeFirst();
        delete wfi;
    }
}

void CRTDisplay::AddWindow(QString Sta, QString Chan, QString LCODE, double dSpS)
{
    CMWindow *wfi = new CMWindow;
    wfi->StaName  = Sta;
    wfi->ChanName = Chan;
    wfi->LCODE    = LCODE;
    wfi->dSpS     = dSpS;
    WaveformInfo.append(wfi);
}
void CRTDisplay::RemoveWindow(QString Sta, QString Chan, QString LCODE)
{
    CMWindow *wfi;
    QList<CMWindow * >::Iterator j =  WaveformInfo.begin();
    while(j!=WaveformInfo.end())
    {
        wfi = *j;
        if( (Sta.compare(wfi->StaName)==0) && (Chan.compare(wfi->ChanName)==0) && (LCODE.compare(wfi->LCODE)==0))
        {
            j = WaveformInfo.erase(j);
            delete wfi;
            return;
        }
        else
            ++j;
    }

}


void CRTDisplay::Run()
{
    QMap< QString, CNRTSSTAINFO * >::Iterator i;
    QMap< QString, CNRTSCHANINFO * >::Iterator j;
    CNRTSSTAINFO	*si = NULL;
    CNRTSCHANINFO	*ci = NULL;
    QString			sSta,sChan,sLoc;

    //    MainFrame *pParent=(MainFrame *)parentWidget();

    // Make windows control list

    ClearWaveformInfo();
    nLastMarkRightPos=0;
    for(i=NrtsInfo.StaInfo.begin(); i!=NrtsInfo.StaInfo.end(); ++i)
    {
        si = *i;
        sSta=si->Sta;
        for(j=si->ChanInfo.begin(); j!=si->ChanInfo.end(); ++j)
        {
            ci=*j;
            if(ci->bSelected)
            {
                sChan=ci->Chan;
                sLoc=ci->LCODE;
                double dSpS=ci->dSpS;
                AddWindow(sSta, sChan, sLoc, dSpS);
            }
        }
    }

    nActiveScreen=0;
    CalculateWindowsSize();
    bContinue=TRUE;

}
void CRTDisplay::Stop()
{
    ScreenBitmapCriticalSection.lock();
    Critical.lock();

    ClearWaveformInfo();
    bDrawBitmap = FALSE;
    Critical.unlock();
    ScreenBitmapCriticalSection.unlock();
    ClearDisplay();
    repaint();
}

void CRTDisplay::CalculateWindowsSize()
{
    int i;
    CMWindow *wfi;
    QList<CMWindow * >::Iterator ii;
    int nWin = WaveformInfo.count();
    if(nWin==0)
    {
        return;
    }
    MaxX=width();
    MaxY= height();
    int yHeight=(MaxY-TimeBarYsize)/nWin;
    i=0;
    for( ii=WaveformInfo.begin(); ii!=WaveformInfo.end(); ++ii, ++i)
    {
        wfi = *ii;
        wfi->xw1=2;
        wfi->xw2=MaxX-1;
        wfi->yw1=yHeight*i+TimeBarYsize;
        wfi->yw2=(yHeight*(i+1)+TimeBarYsize)-1;

        wfi->x1=wfi->xw1+WindowInfoXsize+2;
        wfi->x2=wfi->xw2-1;

        wfi->y1=wfi->yw1+1;
        wfi->y2=wfi->yw2-1;
    }

}

void  CRTDisplay::resizeEvent( QResizeEvent *q )
{
    g_bForceRedraw=TRUE;
}


void CRTDisplay::OnTimer() 
{
    SetTime();
    RemoveOldData();
    DrawWaveforms();
}

void CRTDisplay::DrawWaveforms()
{
    QPen DarkPen(QColor(0,0,0));
    QBrush BlueBrush(QColor(0,0,128));


    QBrush WhiteBrush(QColor(255,255,255));
    QBrush GrayBrush(QColor(192,192,192));

    QPen WhitePen(QColor(255,255,255));
    QPen BluePen(QColor(0,0,255));
    QPen YellowPen(QColor(255,255,0));

    QPen WhitePen2(QColor(255,255,255),2);
    QPen GrayPen2 (QColor(128,128,128),2);

    if(height()<30 && width()<30) return;

    QMutexLocker ml(&Critical);

    if(m_autoscale)
        for(int i=0; i<WaveformInfo.size(); ++i)
        {
            ApplyAutoscale(i, 0);
        }

    CalculateWindowsSize();
    QRect rc(0,0,MaxX, MaxY);
    QPixmap Bitmap1(MaxX, MaxY);
    QPainter DC(&Bitmap1);
    DC.setBackgroundMode(Qt::TransparentMode);

    DC.fillRect(rc, BlueBrush);

    DC.setPen(DarkPen);
    DC.drawLine(0,0, 0,MaxY);

    DrawTimePanel(&DC);

    for(unsigned int i=0; i<WaveformInfo.count(); ++i)
    {
        DrawWindow(i, &DC);
    }


    ScreenBitmapCriticalSection.lock();
    Bitmap = Bitmap1;
    bDrawBitmap = TRUE;
    ScreenBitmapCriticalSection.unlock();

    repaint();
}

void CRTDisplay::SetTime()
{
    double dnewtime;
    time_t tim;

    tim = time(NULL);
    dnewtime = tim;

    dnewtime-=nDelay;
    Critical.lock();

    if(t2>=tB2)
    {
        t2=dnewtime;
        t1=t2-nDisplayedTime;
    }
    else
    {
        if(tB1>=t1)
        {
            t1=dnewtime-nBufferedTime;
            t2=nDisplayedTime+t1;
        }
    }
    tB2=dnewtime;
    tB1=tB2-nBufferedTime;
    Critical.unlock();

}
void CRTDisplay::DrawFocused(QPainter *pDC)
{
    if(nActiveScreen==-1) return;
    if(WaveformInfo.count()==0) return;
    CMWindow *wfi = WaveformInfo.at(nActiveScreen);
    float xw1=wfi->xw1+4;
    float xw2=wfi->xw1+WindowInfoXsize-4;
    float yw1=wfi->yw1+4;
    float yw2=wfi->yw2-4;


    QPen WhitePen(QColor(255,255,255));
    QPen GrayPen(QColor(128,128,128));


    pDC->setPen(GrayPen);
    pDC->drawLine(xw1,MaxY-yw2, xw2, MaxY-yw2);
    pDC->drawLine(xw1,MaxY-yw2, xw1, MaxY-yw1);

    pDC->setPen(WhitePen);
    pDC->drawLine(xw2,MaxY-yw1, xw2,MaxY-yw2);
    pDC->drawLine(xw2+1,MaxY-yw1, xw2+1,MaxY-yw2);
    pDC->drawLine(xw2, MaxY-yw1, xw1, MaxY-yw1);
    pDC->drawLine(xw2,MaxY-yw1+1, xw1, MaxY-yw1+1);
}

void CRTDisplay::mousePressEvent ( QMouseEvent *e )  
{

    QMutexLocker ml(&Critical);
    QList<CMWindow * >::Iterator ii;
    CMWindow *wfi;
    //	int x=e->x();
    int y=MaxY-e->y();
    int i=0;

    if (e->button() != Qt::LeftButton)
    {
        return;
    }


    //
    // Change Focus
    //
    for( ii = WaveformInfo.begin(); ii!=WaveformInfo.end(); ++ii,++i)
    {
        wfi = *ii;
        //		int xw1=wfi->xw1;
        //		int xw2=wfi->xw2;
        int yw1=wfi->yw1;
        int yw2=wfi->yw2;

        if( y<=yw2 && y>=yw1)
        {
            nActiveScreen=i;
            repaint();

            //   Update Preview Window

            g_bForceRedraw = true;
            return;
        }

    }


    /*	CWnd::OnLButtonUp(nFlags, point);*/
}
void CRTDisplay::GetTextRectangle(const char *lpText, QRect &rc)
{

    const QFont f=font();

    QFontMetrics qfm(f);
    rc.setRect(0,0,0,0);
    rc = qfm.boundingRect(lpText);

}
//************************************************************
//
// Removes data blocks out of buffered time interval
//
//
void CRTDisplay::RemoveOldData()
{
    QList<CMWindow * >::Iterator i;
    QList<CDataBlock * >::Iterator j;
    CDataBlock *xfd;
    CMWindow *wfi;
    Critical.lock();
    for( i = WaveformInfo.begin(); i!=WaveformInfo.end(); ++i)
    {
        wfi = *i;
        for( j = wfi->xferData.begin(); j!=wfi->xferData.end();)
        {
            xfd = *j;
            //			double t1packet=xfd->beg;
            double t2packet=xfd->end;

            if(t2packet<tB1)
            {
                j = wfi->xferData.erase(j);
                delete xfd;
                continue;
            }
            else
                ++j;
        }
    }
    Critical.unlock();
}
void CRTDisplay::DrawTimePanel(QPainter *pDC)
{
    QPen WhitePen(QColor(255,255,255));
    QPen DarkPen(QColor(0,0,0));
    QPen RedPen(QColor(255,0,0));

    int xw1=WindowInfoXsize+3;
    int xw2=MaxX-1;
    int yw1=1;
    int yw2=TimeBarYsize-1;
    int x, x_old;

    int delta=(t2-t1)/10;
    if(delta==0) delta=1;

    DrawTimeBounds(pDC);

    tmmarks.clear();

    pDC->setPen(WhitePen);


    pDC->drawLine( xw1,MaxY-yw2, xw2,MaxY-yw2 );

    pDC->drawLine(xw1,MaxY-yw2, xw1,MaxY-yw1);

    pDC->setPen(DarkPen);

    pDC->drawLine(xw2,MaxY-yw1, xw2,MaxY-yw2);

    pDC->drawLine(xw2,MaxY-yw1, xw1,MaxY-yw1);

    x_old=-1;

    int imode;

    x=(int)((xw2-xw1)/(t2-t1));

    if(x<3)
    {
        x=(int)(60*(xw2-xw1)/(t2-t1));
        if(x==0)
        {
            imode=2;
        }
        else
        {
            imode=1;
        }
    }
    else
    {
        imode=0;
    }
    nLastMarkRightPos=-100;
    for(long tt=(long)t1; tt<t2; ++tt)
    {
        x=(int)((tt-t1)*(xw2-xw1)/(t2-t1)+xw1);

        if(((int)tt)%delta==0)
        {
            x_old=x;

            DrawTimeMark(x, tt, pDC);
        }


    }


}


void CRTDisplay::DrawTimeMark(int x, double tt, QPainter *pDC)
{
    QPen WhitePen(QColor(255,255,255));
    QPen DarkPen(QColor(0,0,0));

    int yw1=1;
    int yw2=TimeBarYsize-1;

    char cBuff1[64], cBuff2[64];


    pDC->setPen(WhitePen);

    strcpy(cBuff1, util_dttostr(tt, 15));
    QRect rcc1,rcc2;
    GetTextRectangle(cBuff1,rcc1);
    int wdt=rcc1.width()/2+1;
    int hgt=rcc1.height();

    rcc1.setTopLeft(QPoint(x-wdt, (MaxY-(yw1+hgt))));
    rcc1.setBottomRight(QPoint(x+wdt, (MaxY-(yw1))));


    strcpy(cBuff2, util_dttostr(tt, 14));
    GetTextRectangle(cBuff2,rcc2);
    wdt=rcc2.width()/2+1;
    hgt=rcc2.height();
    rcc2.setTopLeft(QPoint(x-wdt, (MaxY-(yw1+hgt+hgt))));
    rcc2.setBottomRight(QPoint(x+wdt, (MaxY-(yw1+hgt))));




    int xminPos=min(rcc2.left(),rcc1.left());
    if( nLastMarkRightPos<xminPos && WindowInfoXsize<xminPos)
    {
        pDC->drawText(rcc1, Qt::AlignLeft, cBuff1);
        pDC->drawText(rcc2, Qt::AlignLeft, cBuff2);
        nLastMarkRightPos=max(rcc1.right(),rcc2.right());
        //		nLastMarkRightPos=rcc1.right();
        tmmarks.append(x);
        pDC->setPen(WhitePen);
        pDC->drawLine(x,MaxY-yw2, x,MaxY-(yw2-4));
        pDC->setPen(DarkPen);
        pDC->drawLine(x+1,MaxY-yw2, x+1,MaxY-(yw2-4));
    }
}

void CRTDisplay::DrawTimeBounds(QPainter *pDC)
{
    //	int yw1=1;
    int yw2=TimeBarYsize-1;
    char cBuff1[64];

    QPen WhitePen(QColor(255,255,255));


    pDC->setPen(WhitePen);

    strcpy(cBuff1, util_dttostr(t1,14));
    QRect rcc1;
    //    QRect rcc2;
    GetTextRectangle(cBuff1,rcc1);
    rcc1.moveTop(MaxY-yw2);

    /*	int n1=(MaxY-rcc1.bottom);
    int n2=(MaxY-rcc1.top);
    rcc1.top=n1;
    rcc1.bottom=n2;



    lstrcpy(cBuff2, dttostr(t2,15));
    GetTextRectangle(cBuff2,rcc2);
    nWtd=rcc2.right-rcc2.left;
    hgt=(rcc2.bottom-rcc2.top);
    rcc2.left+=1;
    rcc2.right+=1;
    rcc2.bottom+=yw1;
    rcc2.top+=yw1;

    n1=(MaxY-rcc2.bottom);
    n2=(MaxY-rcc2.top);
    rcc2.top=n1;
    rcc2.bottom=n2;*/

    //	pDC->DrawText(cBuff1,&rcc1,DT_LEFT|DT_SINGLELINE|DT_BOTTOM);
    pDC->drawText(rcc1, Qt::AlignLeft, cBuff1);
    //	pDC->DrawText(cBuff2,&rcc2,DT_LEFT|DT_SINGLELINE|DT_BOTTOM);

    //	nLastMarkRightPos=max(rcc1.right,rcc2.right);
    nLastMarkRightPos=rcc1.right();
}

void CRTDisplay::autoScaleSlot(int nType)
{
    if(WaveformInfo.size()==0) return;

    ScreenBitmapCriticalSection.lock();
    Critical.lock();

    int sState=QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ShiftModifier);
    QPixmap Bitmap1=Bitmap;
    Critical.unlock();

    QPainter DC(&Bitmap1);

    if(sState==0)
    {
        ApplyAutoscale(nActiveScreen, nType);
        DrawWindow(nActiveScreen, &DC);
    }
    else
    {
        for(unsigned int i=0; i<WaveformInfo.count(); ++i)
        {
            ApplyAutoscale(i, nType);
            DrawWindow(i, &DC);
        }
    }
    Critical.lock();
    Bitmap=Bitmap1;
    Critical.unlock();
    ScreenBitmapCriticalSection.unlock();

    if(sState==0)
    {
        //		CMWindow *wfi = WaveformInfo.at(nActiveScreen);
        //		int xw1=wfi->xw1;
        //		int xw2=wfi->xw2;
        //		int yw1=wfi->yw1;
        //		int yw2=wfi->yw2;
        //		QRect rc(QPoint(xw1,MaxY-yw2),QPoint(xw2,MaxY-yw1));

        repaint(); //InvalidateRect(rc, FALSE);
    }
    else
    {
        repaint();
    }

}
void CRTDisplay::ApplyAutoscale(int nWindow, int nType)
{
    if(WaveformInfo.size()==0) return;


    QList<CDataBlock * >::Iterator i;
    CDataBlock *xfd;
    BOOL bfirstcount=TRUE;
    CMWindow *wfi = WaveformInfo.at(nWindow);


    long amax=wfi->amax;
    long amin=wfi->amin;


    for(i = wfi->xferData.begin(); i!= wfi->xferData.end(); ++i)
    {
        xfd = *i;
        double t1packet=xfd->beg;
        //		double t2packet=xfd->end;
        int nsamp=xfd->nsamp;
        for(int k=0; k<nsamp; ++k)
        {
            long a=xfd->data[k];
            double tt=t1packet+xfd->sint*k;

            if(nType==0)
            {
                if(tt<t1) continue;
                if(tt>t2) break;
            }
            if(!bfirstcount)
            {
                if(a>amax) amax=a;
                if(a<amin) amin=a;
            }
            else
            {
                bfirstcount=FALSE;
                amax=a+1;
                amin=a-1;
            }

        }
    }
    if(amax==amin)
    {
        amax++;
        amin--;
    }

    WaveformInfo.at(nWindow)->amax=amax;
    WaveformInfo.at(nWindow)->amin=amin;
}

void CRTDisplay::DrawWindow(int nWindow, QPainter *pDC)
{
    if(WaveformInfo.size()==0) return;
    QString qText;
    QBrush WhiteBrush(QColor(255,255,255));
    QBrush GrayBrush(QColor(192,192,192));
    QBrush BlueBrush(QColor(0,0,128));

    QPen WhitePen(QColor(255,255,255));
    QPen DarkPen(QColor(0,0,0));
    QPen BluePen(QColor(0,0,255));
    QPen YellowPen(QColor(255,255,0));

    CMWindow *wfi = WaveformInfo.at(nWindow);

    int xw1=wfi->xw1;
    int xw2=wfi->xw2;
    int yw1=wfi->yw1;
    int yw2=wfi->yw2;

    int x1=wfi->x1;
    int x2=wfi->x2;
    int y1=wfi->y1;
    int y2=wfi->y2;

    if(wfi->xferData.size()<5 )
    {
        ApplyAutoscale(nWindow,1);
    }


    long amin=wfi->amin;
    long amax=wfi->amax;


    QRect rc(QPoint(xw1-1, MaxY-yw2-1), QPoint(xw2+1, MaxY-yw1+1));
    pDC->fillRect(rc, BlueBrush);

    //	pDC->SelectObject(&DarkPen);


    //*************************************************************
    //      Draw Ampl (Y) Axis
    //

    QRect rc1(QPoint(xw1, MaxY-yw2), QPoint(xw1+WindowInfoXsize-1, MaxY-yw1));
    pDC->fillRect(rc1, GrayBrush);


    pDC->setPen(DarkPen);
    //	pDC->SetTextColor(QColor(0,0,0));

    pDC->drawLine(xw1+WindowInfoXsize-8,MaxY-(yw1+8), (xw1+WindowInfoXsize-8),MaxY-(yw2-8));

    pDC->drawLine(xw1+WindowInfoXsize-8,MaxY-(yw1+8), (xw1+WindowInfoXsize-8+4),MaxY-(yw1+8));

    pDC->drawLine(xw1+WindowInfoXsize-8,MaxY-(yw2-8), (xw1+WindowInfoXsize-8+4),MaxY-(yw2-8));

    pDC->setPen(WhitePen);

    {
        QPoint qp;
        //	QRect rcText;
        QRect rcTextAmax, rcTextAmin;
        char cTextAmin[64], cTextAmax[64];
        static const int _distanceFromMinMaxLabelToUpperOrBottomEdge = 9;


        sprintf(cTextAmax,"%d",amax);
        GetTextRectangle(cTextAmax, rcTextAmax);

        qp=QPoint(xw1+WindowInfoXsize-rcTextAmax.width()-10,MaxY-yw2+_distanceFromMinMaxLabelToUpperOrBottomEdge);
        rcTextAmax.moveTopLeft(qp);


        sprintf(cTextAmin,"%d",amin);
        GetTextRectangle(cTextAmin, rcTextAmin);

        qp=QPoint(xw1+WindowInfoXsize-rcTextAmin.width()-10,MaxY-yw1-_distanceFromMinMaxLabelToUpperOrBottomEdge);
        rcTextAmin.moveBottomLeft(qp);


        if(rcTextAmax.bottom()<rcTextAmin.top()+1)
        {
            pDC->drawText(rcTextAmax,Qt::AlignRight, cTextAmax);
            pDC->drawText(rcTextAmin, Qt::AlignRight, cTextAmin);
        }




        QRect rcc3(QPoint(xw1+5,(MaxY-yw2)),QPoint(xw1+WindowInfoXsize-8-2, (MaxY-yw1)));
        qText = wfi->StaName +"."+ wfi->ChanName+"."+ wfi->LCODE;

        pDC->drawText(rcc3,Qt::AlignVCenter,qText);

    }

    //**************************************************************

    double ttt=-1.;

    pDC->setPen(YellowPen);
    CDataBlock *xfd;
    QList<CDataBlock * >::Iterator i;
    int x_prev=0, y_prev=0;
    for( i=wfi->xferData.begin(); i!=wfi->xferData.end(); ++i )
    {
        xfd = *i;
        double t1packet=xfd->beg;
        //		double t2packet=xfd->end;
        int nsamp=xfd->nsamp;


        for(int k=0; k<nsamp; ++k)
        {
            long a=xfd->data[k];
            double tt=t1packet+(xfd->sint)*k;
            int x,y;

            if(tt<t1) continue;
            if(tt>t2) break;

            x=(int)((tt-t1)*(x2-x1)/(t2-t1)+x1);

            if(a>amax) a=amax;
            if(a<amin) a=amin;

            y=(a-amin)*(y2-y1)/(amax-amin)+y1;
            y=MaxY-y;
            if(tt-ttt>1.1*xfd->sint)
            {
                //                pDC->moveTo(x,y);
                x_prev = x;
                y_prev = y;
            }
            else
            {
                pDC->drawLine(x_prev, y_prev, x, y);
                x_prev = x;
                y_prev = y;
            }
            ttt=tt;
        }
    }

    DrawGaps(nWindow,pDC);

}
void CRTDisplay::DrawGaps(int nWindow, QPainter *pDC)
{
    QBrush LightBlueBrush(QColor(0,0,192));

    const QPen   &oldPen=pDC->pen();
    const QBrush &oldBrush=pDC->brush();

    //    int xw1=WaveformInfo[nWindow]->xw1;
    //    int xw2=WaveformInfo[nWindow]->xw2;
    //    int yw1=WaveformInfo[nWindow]->yw1;
    //    int yw2=WaveformInfo[nWindow]->yw2;

    int x1=WaveformInfo[nWindow]->x1;
    int x2=WaveformInfo[nWindow]->x2;
    int y1=WaveformInfo[nWindow]->y1;
    int y2=WaveformInfo[nWindow]->y2;


    int nXferBlocks=WaveformInfo[nWindow]->xferData.size();
    //    double ttt=-1.;
    double sint;

    sint = -1;

    double tend=t1;
    for(int j=0; j<nXferBlocks; ++j)
    {
        CDataBlock *xfd=WaveformInfo[nWindow]->xferData[j];
        double t1packet=WaveformInfo[nWindow]->xferData[j]->beg;
        double t2packet=WaveformInfo[nWindow]->xferData[j]->end;
        int nsamp=WaveformInfo[nWindow]->xferData[j]->nsamp;
        if(tend>t2packet) continue;
        if(tend>t1packet)
        {
            tend=t2packet;
            continue;
        }

        if((fabs(tend-t1packet)>xfd->sint) && (tend!=-1))
        {
            int xx1=(int)((tend-t1)*(x2-x1)/(t2-t1)+x1);
            int xx2=(int)((t1packet-t1)*(x2-x1)/(t2-t1)+x1);
            QRect rc(xx1,(MaxY-y2)+1,xx2-xx1,(y2-y1)-1);
            //              QRect rc(xx1,(y1)+2,xx2,(y2)-1);
            pDC->fillRect(rc, LightBlueBrush);
        }
        tend=t1packet+nsamp*xfd->sint;
        sint = xfd->sint;
    }
    if(fabs(tend-t2)>sint && sint>-1)
    {
        int xx1=(int)((tend-t1)*(x2-x1)/(t2-t1)+x1);
        int xx2=x2;
        QRect rc(xx1,(MaxY-y2)+1,xx2-xx1,(y2-y1)-1);
        //        QRect rc(xx1,(y1)+2,xx2,(y2)-1);
        pDC->fillRect(rc, LightBlueBrush);
    }

    pDC->setPen(oldPen);
    pDC->setBrush(oldBrush);
}

void CRTDisplay::expandVertSlot()
{
    ScreenBitmapCriticalSection.lock();
    Critical.lock();


    short sState = QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ShiftModifier);


    QPainter DC(&Bitmap);
    //*******************************************************

    if(sState==0)
    {
        ApplyExpand(nActiveScreen);
        DrawWindow(nActiveScreen, &DC);
    }
    else
    {
        for(unsigned int i=0; i<WaveformInfo.count(); ++i)
        {
            ApplyExpand(i);
            DrawWindow(i, &DC);
        }
    }
    //	DrawWindow(nActiveScreen, &DC);
    //*******************************************************
    Critical.unlock();
    ScreenBitmapCriticalSection.unlock();


    if(sState==0)
    {
        CMWindow *wfi = WaveformInfo.at(nActiveScreen);
        int xw1=wfi->xw1;
        int xw2=wfi->xw2;
        int yw1=wfi->yw1;
        int yw2=wfi->yw2;

        QRect rc(QPoint(xw1,MaxY-yw2),QPoint(xw2,MaxY-yw1));

        repaint(); //InvalidateRect(rc, FALSE);
    }
    else
    {
        repaint();
    }

}

void CRTDisplay::ApplyExpand(int nWindow)
{
    CMWindow *wfi = WaveformInfo.at(nWindow);

    long amax=wfi->amax;
    long amin=wfi->amin;

    long amid, adelta;

    amid=(amax+amin)/2;
    adelta=(amax-amin)/2;

    adelta/=2;

    amax=amid+adelta;
    amin=amid-adelta;

    if(amax==amin)
    {
        amax++;
        amin--;
    }

    wfi->amax=amax;
    wfi->amin=amin;
}

void CRTDisplay::contractVertSlot()
{
    ScreenBitmapCriticalSection.lock();
    Critical.lock();


    short sState=QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ShiftModifier);

    QPainter DC(&Bitmap);
    //*******************************************************

    if(sState==0)
    {
        ApplyContract(nActiveScreen);
        DrawWindow(nActiveScreen, &DC);
    }
    else
    {
        for(unsigned int i=0; i<WaveformInfo.count(); ++i)
        {
            ApplyContract(i);
            DrawWindow(i, &DC);
        }
    }
    //	DrawWindow(nActiveScreen, &DC);
    //*******************************************************
    Critical.unlock();
    ScreenBitmapCriticalSection.unlock();


    if(sState==0)
    {
        CMWindow *wfi = WaveformInfo.at(nActiveScreen);
        int xw1=wfi->xw1;
        int xw2=wfi->xw2;
        int yw1=wfi->yw1;
        int yw2=wfi->yw2;

        QRect rc(QPoint(xw1,MaxY-yw2),QPoint(xw2,MaxY-yw1));

        repaint(); //InvalidateRect(rc, FALSE);
    }
    else
    {
        repaint();
    }

}

void CRTDisplay::ApplyContract(int nWindow)
{
    //	BOOL bfirstcount=TRUE;

    long amax=WaveformInfo.at(nWindow)->amax;
    long amin=WaveformInfo.at(nWindow)->amin;

    long amid, adelta;

    amid=(amax+amin)/2;
    adelta=(amax-amin)/2;

    adelta*=2;

    if(adelta==0) adelta=1;

    amax=amid+adelta;
    amin=amid-adelta;


    WaveformInfo.at(nWindow)->amax=amax;
    WaveformInfo.at(nWindow)->amin=amin;

}
void CRTDisplay::shiftUpDownSlot(int nDirection)
{
    CMWindow *wfi = WaveformInfo.at(nActiveScreen);

    ScreenBitmapCriticalSection.lock();
    Critical.lock();

    QPainter DC(&Bitmap);

    int xw1=wfi->xw1;
    int xw2=wfi->xw2;
    int yw1=wfi->yw1;
    int yw2=wfi->yw2;

    QRect rc( QPoint(xw1,MaxY-yw2),QPoint(xw2,MaxY-yw1));



    long amax=wfi->amax;
    long amin=wfi->amin;

    long amid, adelta, adelta1;

    amid=(amax+amin)/2;
    adelta=(amax-amin)/2;
    adelta1=adelta/5;

    if(adelta1==0) adelta1=1;
    if(nDirection>0)
    {
        amid=amid+adelta1;
    }
    else
    {
        amid=amid-adelta1;
    }

    amax=amid+adelta;
    amin=amid-adelta;


    wfi->amax=amax;
    wfi->amin=amin;

    DrawWindow(nActiveScreen, &DC);

    Critical.unlock();
    ScreenBitmapCriticalSection.unlock();

    repaint();
}

void CRTDisplay::ClearDisplay()
{

    repaint();
}



/*void CRTDisplay::OnMouseMove(UINT nFlags, CPoint point) */
void CRTDisplay::mouseMoveEvent ( QMouseEvent * e ) 
{
    if(!bContinue) return;

    int x=e->x();
    int y=MaxY-e->y();


    int nWindow=nWindowFromPoint(x,y);

    if(nWindow!=-1)
    {
        char cBuff[128];
        long amax=WaveformInfo.at(nWindow)->amax;
        long amin=WaveformInfo.at(nWindow)->amin;
        int x1=WaveformInfo.at(nWindow)->x1;
        int x2=WaveformInfo.at(nWindow)->x2;
        int y1=WaveformInfo.at(nWindow)->y1;
        int y2=WaveformInfo.at(nWindow)->y2;


        double ttt=(x-x1)*(t2-t1)/(x2-x1)+t1;
        long aaa=(long)((double)(y-y1)*(amax-amin)/(y2-y1)+amin+0.5);

        sprintf(cBuff,"A:%d T:%s",(long)aaa, util_dttostr(ttt, 1));

        emit setTimeInfo(QString(cBuff));
    }

}
int CRTDisplay::nWindowFromPoint(int x, int y)
{
    CMWindow *wfi;
    int nWindow=0;
    int x1, x2, y1, y2;
    QList<CMWindow * >::Iterator i;

    for(i = WaveformInfo.begin(); i!=WaveformInfo.end(); ++i)
    {
        wfi = *i;
        x1=wfi->x1;
        x2=wfi->x2;
        y1=wfi->y1;
        y2=wfi->y2;
        if( (y<=y2) && (y>=y1) && (x>=x1) && (x<=x2)) return nWindow;
        ++nWindow;
    }
    return -1;
}
void CRTDisplay::paintEvent(QPaintEvent *)
{
    QMutexLocker ml(&ScreenBitmapCriticalSection);

    if(bDrawBitmap)
    {
        QPainter paint( this );
        paint.drawPixmap(0,0, Bitmap);
        DrawFocused(&paint);
        QPen dotPen(QColor(0,0,0),1, Qt::DotLine);

        paint.setPen(dotPen);
        for(unsigned int i=0; i<tmmarks.count(); ++i)
        {
            int x=tmmarks.at(i);
            paint.drawLine( x, MaxY-TimeBarYsize, x,1);
        }
    }

}
bool CRTDisplay::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case Update:
        OnTimer();
        return true;
    case Draw:
        DrawWaveforms();
        return true;
    default:
        return false;
    }

}

void CRTDisplay::setAutoScaleFlag(bool b)
{
    m_autoscale = b;
}

void CRTDisplay::drawWaveformsSlot()
{
    OnTimer();
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
