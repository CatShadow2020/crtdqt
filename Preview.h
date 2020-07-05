#pragma "$Id$"
#if !defined(_PREVIEW_H_INCLUDED_)
#define _PREVIEW_H_INCLUDED_

#include "platform.h"
#undef max
#undef min
#include "RTDisplay.h"
#include <qwidget.h>
#include <qpixmap.h>
#include <QList> 
#include <QEvent>
// #include "qcustomevent.h"

/////////////////////////////////////////////////////////////////////////////
// CPreview window

class CPreview : public QWidget
{
    Q_OBJECT

public:
    CPreview(CRTDisplay *pDisplay, QWidget * parent );
	virtual ~CPreview();

public:
	void DrawPreviewBitmap();
	void Stop();

private:
	void DrawWaveform(QPainter &DC);
	QMutex ScreenBitmapCriticalSection;
	void paintEvent(QPaintEvent *);
	void resizeEvent(QResizeEvent *);



public:
	QPixmap Bitmap;
	int MaxX, MaxY;
	CRTDisplay *pDisplay;
	int x1,x2,y1,y2,xw1, xw2, yw1, yw2;

    const static QEvent::Type DrawPreview		=	    static_cast<QEvent::Type>(QEvent::User+1);

public:
protected:
	bool bDrawBitmap;
	void mouseMoveEvent ( QMouseEvent * e );
	void mousePressEvent ( QMouseEvent *e );  

public:
signals:
    void setTimeInfo(QString);

public slots:
    virtual void drawPreviewSlot();


};


#endif // _PREVIEW_H_INCLUDED_
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
