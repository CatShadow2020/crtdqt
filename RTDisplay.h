#pragma "$Id$"

// RTDisplay.h: interface for the CRTDisplay class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_RTDISPLAY_H_INCLUDED_)
#define _RTDISPLAY_H_INCLUDED_

#include "platform.h"
#include <qwidget.h>
#include <qpixmap.h>
#include <QList> 
#include "MWindow.h"
#include <qmutex.h>
// #include <qcustomevent.h>
#include <QMouseEvent>


class CRTDisplay : public QWidget  
{
    Q_OBJECT
public:
    CRTDisplay(QWidget * parent = NULL);
	virtual ~CRTDisplay();


    const static QEvent::Type AutoScale0		=	    static_cast<QEvent::Type>(QEvent::User+1);
    const static QEvent::Type AutoScale1		=	    static_cast<QEvent::Type>(QEvent::User+2);
    const static QEvent::Type AutoScale2		=	    static_cast<QEvent::Type>(QEvent::User+3);

    const static QEvent::Type ExpandVert		=	    static_cast<QEvent::Type>(QEvent::User+4);
    const static QEvent::Type ContractVert	=	    static_cast<QEvent::Type>(QEvent::User+5);
    const static QEvent::Type ShiftUp	    =	    static_cast<QEvent::Type>(QEvent::User+6);
    const static QEvent::Type ShiftDown		=	    static_cast<QEvent::Type>(QEvent::User+7);
    const static QEvent::Type Update         =	    static_cast<QEvent::Type>(QEvent::User+8);
    const static QEvent::Type Draw			=	    static_cast<QEvent::Type>(QEvent::User+9);


public:
	QPixmap Bitmap; // off screen bitmap
    QList<CMWindow *> WaveformInfo; // array of all waveforms
    QList<int> tmmarks; // time marks array

	QMutex Critical;
	QMutex ScreenBitmapCriticalSection;

	int MaxX, MaxY;

	double t1,t2;
	double tB1,tB2;
	int nTimerCount;
	int nActiveScreen;
	int TimeBarYsize;
    BOOL m_autoscale;

// Operations
public:

	void AddWindow(QString Sta, QString Chan, QString LCODE, double dSpS);
	void RemoveWindow(QString Sta, QString Chan, QString LCODE);
	void Run();
	void Stop();
	void DrawWaveforms();
	void OnTimer();
	void RemoveOldData();
    void setAutoScaleFlag(bool b);

	void DrawTimeMark(int x, double tt, QPainter *pDC);
	void DrawTimeBounds(QPainter *pDC);
	int nWindowFromPoint(int x, int y);
	void resizeEvent(QResizeEvent * );
	void paintEvent (QPaintEvent  * );
    bool eventFilter(QObject *obj, QEvent *event);

private:
	int nLastMarkRightPos; 
	bool bDrawBitmap;
	int WindowInfoXsize;

protected:
	void SetTime();
	void CalculateWindowsSize();
	void ClearWaveformInfo();
	void DrawFocused(QPainter  *pDC);
	void GetTextRectangle(const char *lpText, QRect &rc);
	void DrawTimePanel(QPainter *pDC);
	void DrawWindow(int nWindow, QPainter  *pDC);
	void ClearDisplay();
	void ApplyAutoscale(int nWindow, int nType);
	void DrawGaps(int nWindow, QPainter *pDC);
	void ApplyExpand(int nWindow);
	void ApplyContract(int nWindow);
	void mousePressEvent (QMouseEvent *e );
	void mouseMoveEvent ( QMouseEvent *e );
signals:
    void setTimeInfo(QString);
    void drawPreviewSignal(void);
    void autoScaleSignal(int);

public slots:
    void drawWaveformsSlot();
    void autoScaleSlot(int nType);
    void expandVertSlot();
    void contractVertSlot();
    void shiftUpDownSlot(int nDirection);



};

#endif // !defined(_RTDISPLAY_H_INCLUDED_)

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
