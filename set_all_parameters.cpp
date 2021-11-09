#undef max
#undef min
#include "set_all_parameters.h"


#include <qpushbutton.h>
#include <qwidget.h>
#include <QTableWidget>
#include <QHeaderView>
#include <qlabel.h>
#include <qlineedit.h>
#include <qframe.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qmessagebox.h> 
#include "CRTDglob.h"
/*
 *  Constructs a Set_All_Parameters as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
Set_All_Parameters::Set_All_Parameters( QWidget* parent ) : QDialog( parent )
{
    QHeaderView *header;
    QGridLayout *grdLayout = new QGridLayout();

    setWindowTitle( "Set_All_Parameters" );
    setSizeGripEnabled( FALSE);
    setLayout(grdLayout);

    NrtsInfoX=NrtsInfo;

    QWidget* privateLayoutWidget = new QWidget(  );
    //   privateLayoutWidget->setGeometry( QRect( 10, 340, 530, 28 ) );
    Layout1 = new QHBoxLayout( privateLayoutWidget );

    buttonHelp = new QPushButton( privateLayoutWidget );
    buttonHelp->setAutoDefault( TRUE );
    Layout1->addWidget( buttonHelp );
    Horizontal_Spacing2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( Horizontal_Spacing2 );

    buttonOk = new QPushButton( privateLayoutWidget );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );

    buttonCancel = new QPushButton( );
    buttonCancel->setAutoDefault( TRUE );
    Layout1->addWidget( buttonCancel );

    grdLayout->addWidget(privateLayoutWidget,1, 0);

    tabWidget = new QTabWidget(  );

    grdLayout->addWidget(tabWidget,0, 0);

    Channels = new QWidget( tabWidget );

    QVBoxLayout * vboxLayout0 = new QVBoxLayout(  );
    QBoxLayout  * Layout1 = new QHBoxLayout(  );
    QBoxLayout  * Layout2 = new QHBoxLayout(  );
    QGridLayout * GridLayout0 = new QGridLayout();

    Channels->setLayout(vboxLayout0);

    vboxLayout0->addLayout(Layout1);
    vboxLayout0->addLayout(Layout2);

    IDC_CHAN = new QTableWidget( Channels );

    //    IDC_CHAN->setGeometry( QRect( 150, 10, 360, 180 ) );
    IDC_CHAN->setRowCount( 0 );
    IDC_CHAN->setColumnCount( 3 );
    IDC_CHAN->setSelectionBehavior(QAbstractItemView::SelectRows);
    IDC_CHAN->verticalHeader()->setVisible(false);
    //	IDC_CHAN->setLeftMargin(0);
    IDC_CHAN->setEditTriggers(QAbstractItemView::NoEditTriggers);
    header = IDC_CHAN->horizontalHeader();

    QStringList  labels;
    labels << "Channel" << "Lcode" << "SpS";
    IDC_CHAN->setHorizontalHeaderLabels(labels);

    InitStaTable();

    Layout1->addWidget(IDC_STA);
    Layout1->addWidget(IDC_CHAN);

    Port_number_2 = new QLabel( Channels );
    Port_number_2->setGeometry( QRect( 17, 256, 57, 20 ) );

    ISI_Server_2 = new QLabel( Channels );
    ISI_Server_2->setGeometry( QRect( 17, 230, 57, 20 ) );

    IDC_LOADLIST = new QPushButton( Channels );
    IDC_LOADLIST->setGeometry( QRect( 280, 230, 230, 30 ) );

    IDC_NRTSSERVER = new QLineEdit( Channels );
    IDC_NRTSSERVER->setGeometry( QRect( 80, 230, 165, 20 ) );

    IDC_PORT = new QLineEdit( Channels );
    IDC_PORT->setGeometry( QRect( 80, 256, 165, 20 ) );

    Layout2->addLayout(GridLayout0);
    GridLayout0->addWidget(Port_number_2 , 0, 0);GridLayout0->addWidget(IDC_PORT, 0, 1);
    GridLayout0->addWidget(ISI_Server_2  , 1, 0);GridLayout0->addWidget(IDC_NRTSSERVER  , 1, 1);

    Layout2->addWidget(IDC_LOADLIST);

    tabWidget->insertTab( 0, Channels, QString::fromLatin1("") );

    Display_parameters = new QWidget( tabWidget );

    layout14 = new QGridLayout( Display_parameters);

    Displayed_window_size = new QLabel( Display_parameters );
    Displayed_window_size->setFrameShape( QLabel::NoFrame );

    layout14->addWidget( Displayed_window_size, 0, 0 );

    IDC_REFRESHTIME = new QLineEdit( Display_parameters );

    layout14->addWidget( IDC_REFRESHTIME, 2, 1 );

    IDC_DELAY = new QLineEdit( Display_parameters );

    layout14->addWidget( IDC_DELAY, 3, 1 );

    Buffered_window_size = new QLabel( Display_parameters );
    Buffered_window_size->setFrameShape( QLabel::NoFrame );

    layout14->addWidget( Buffered_window_size, 1, 0 );

    IDC_BUFFEREDTIME = new QLineEdit( Display_parameters );

    layout14->addWidget( IDC_BUFFEREDTIME, 1, 1 );

    IDC_DISPLAYTIME = new QLineEdit( Display_parameters );

    layout14->addWidget( IDC_DISPLAYTIME, 0, 1 );

    Refresh_time = new QLabel( Display_parameters );

    layout14->addWidget( Refresh_time, 2, 0 );

    Delay__sec = new QLabel( Display_parameters );

    layout14->addWidget( Delay__sec, 3, 0 );

    Display_parameters->adjustSize();

    tabWidget->insertTab( 1, Display_parameters, "" );
    languageChange();
    resize( QSize(558, 403).expandedTo(minimumSizeHint()) );
    //    clearWState( WState_Polished );
    setAttribute(Qt::WA_WState_Polished, true );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this,  SLOT(OnOk())  );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( IDC_LOADLIST, SIGNAL( clicked() ), this,  SLOT(OnLoadList())  );
    connect( IDC_CHAN, SIGNAL(  itemClicked (  QTableWidgetItem *) ), this,  SLOT(OnClickChanListTableItem( QTableWidgetItem *))  );


    // tab order
    setTabOrder( buttonHelp, buttonOk );
    setTabOrder( buttonOk, buttonCancel );
    setTabOrder( buttonCancel, tabWidget );
    setTabOrder( tabWidget, IDC_DISPLAYTIME );
    setTabOrder( IDC_DISPLAYTIME, IDC_BUFFEREDTIME );
    setTabOrder( IDC_BUFFEREDTIME, IDC_REFRESHTIME );
    setTabOrder( IDC_REFRESHTIME, IDC_DELAY );
    setTabOrder( IDC_DELAY, IDC_CHAN );
    setTabOrder( IDC_CHAN, IDC_PORT );
    setTabOrder( IDC_PORT, IDC_NRTSSERVER );
    setTabOrder( IDC_NRTSSERVER, IDC_LOADLIST );
    setTabOrder( IDC_LOADLIST, IDC_STA );

    // buddies
    Displayed_window_size->setBuddy( IDC_DISPLAYTIME );
    Buffered_window_size->setBuddy( IDC_BUFFEREDTIME );
    Refresh_time->setBuddy( IDC_REFRESHTIME );
    Delay__sec->setBuddy( IDC_DELAY );

    QString text;
    text = QString("%1").arg(nRefreshTime);
    IDC_REFRESHTIME->setText(text);
    text = QString("%1").arg(nDelay);
    IDC_DELAY->setText(text);
    IDC_NRTSSERVER->setText(server);
    text = QString("%1").arg(nNrtsPort);
    IDC_PORT->setText(text);
    text = QString("%1").arg(nDisplayedTime);
    IDC_DISPLAYTIME->setText(text);
    text = QString("%1").arg(nBufferedTime);
    IDC_BUFFEREDTIME->setText(text);
    layout14->sizeHint();
    LoadStaList();
    ActiveSta = "";
}

/*
 *  Destroys the object and frees any allocated resources
 */
Set_All_Parameters::~Set_All_Parameters()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void Set_All_Parameters::languageChange()
{
    setWindowTitle(tr( "Set All Parameters" ) );
    buttonHelp->setText( tr( "&Help" ) );
    buttonHelp->setShortcut( QKeySequence( tr( "F1" ) ) );
    buttonOk->setText( tr( "&OK" ) );
    //buttonOk->setShortcut( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    //buttonCancel->setShortcut( QKeySequence( QString::null ) );
    tabWidget->setToolTip(  tr( "Display parameters" ) );
    Port_number_2->setText( tr( "Port number" ) );
    ISI_Server_2->setText( tr( "ISI Server" ) );
    IDC_LOADLIST->setText( tr( "Load config from ISI server" ) );
    tabWidget->setTabText( 0, tr( "Channels" ) );
    Displayed_window_size->setText( tr( "Displayed window size (sec.)" ) );
    Buffered_window_size->setText( tr( "Buffered window size (sec.)" ) );
    Refresh_time->setText( tr( "Refresh time(sec.)" ) );
    Delay__sec->setText( tr( "Delay (sec)" ) );
    tabWidget->setTabText( 1, tr( "Display parameters" ) );
}

// SIGNAL OnOk
void Set_All_Parameters::OnOk()
{
    long nTmp;
    bool bOk;
    QString text;

    text = IDC_REFRESHTIME->text();
    nTmp=text.toInt(&bOk);
    if(bOk)
    {
        nRefreshTime = nTmp;
    }
    else
    {
        IDC_REFRESHTIME->setFocus();
        return;
    }

    text = IDC_DELAY->text();
    nTmp=text.toInt(&bOk);
    if(bOk)
    {
        nDelay = nTmp;
    }
    else
    {
        IDC_DELAY->setFocus();
        return;
    }

    text = IDC_PORT->text();
    nTmp=text.toInt(&bOk);
    if(bOk)
    {
        nNrtsPort = nTmp;
    }
    else
    {
        IDC_PORT->setFocus();
        return;
    }

    server = IDC_NRTSSERVER->text();

    IDC_NRTSSERVER->setText(server);

    text = IDC_DISPLAYTIME->text();
    nTmp=text.toInt(&bOk);
    if(bOk)
    {
        nDisplayedTime = nTmp;
    }
    else
    {
        IDC_DISPLAYTIME->setFocus();
        return;
    }

    text = IDC_BUFFEREDTIME->text();
    nTmp=text.toInt(&bOk);
    if(bOk)
    {
        nBufferedTime = nTmp;
    }
    else
    {
        IDC_BUFFEREDTIME->setFocus();
        return;
    }
    qDebug("Calling SaveParameters...");
    SaveParameters();
    accept();
}
void Set_All_Parameters::SaveParameters()
{
    SaveGlobalParam();
    //	NrtsInfoX.SaveConfigToIni();
    qDebug("Calling SaveConfigToFile...");
    NrtsInfoX.SaveConfigToFile();
    ::NrtsInfo = NrtsInfoX;
}
void Set_All_Parameters::LoadStaList()
{
    char cSta[16];
    QMap<QString, CNRTSSTAINFO * >::Iterator i;
    CNRTSSTAINFO *si;
    QPixmap pixFlag;

    IDC_STA->setRowCount(0);

    int nRow = 0;

    for(i=NrtsInfoX.StaInfo.begin(); i!=NrtsInfoX.StaInfo.end(); ++i )
    {
        si = *i;
        strcpy(cSta,si->Sta.toLocal8Bit().data());

        IDC_STA->insertRow(nRow);
        IDC_STA->setItem(nRow,      0, new QTableWidgetItem(cSta));

        if(bHasSelectedChan(si))
        {
            pixFlag.load( ":/images/flag.bmp" );

        }
        else
        {
            pixFlag.load( ":/images/blank.bmp" );
        }
        IDC_STA->item(nRow, 0)->setIcon(pixFlag);
        nRow++;
    }
}

void Set_All_Parameters::OnLoadList()
{

    long nTmp;
    bool bOk;
    QString text;

    text = IDC_PORT->text();
    nTmp=text.toInt(&bOk);
    if(bOk)
    {
        nNrtsPort = nTmp;
    }
    else
    {
        IDC_PORT->setFocus();
        return;
    }

    server = IDC_NRTSSERVER->text();

    if(NrtsInfoX.LoadConfigFromServer()==1)
    {
        LoadStaList();
    }
    else
    {
        QMessageBox mb("ERROR","Load Config from server error",QMessageBox::Critical, QMessageBox::Ok, int(NULL), int(NULL));
        mb.exec();
    }
}
void Set_All_Parameters::OnClickStaListTableItem( QTableWidgetItem *item)
{
    //	int row=0;
    //	int col=0;

    QString Sta=item->text();
    LoadChanList(Sta);
    ActiveSta=Sta;
}
void Set_All_Parameters::OnClickChanListTableItem( QTableWidgetItem *item)
{
    int row = item->row();
    QString Chan  = IDC_CHAN->item(row, 0)->text();
    QString LCODE = IDC_CHAN->item(row, 1)->text();

    if(item->checkState() & Qt::Checked)
    {
        SetChanDrawState(ActiveSta, Chan, LCODE, TRUE);
    }
    else
    {
        SetChanDrawState(ActiveSta, Chan, LCODE, FALSE);
    }
    //	ActiveSta=Sta;
}
void Set_All_Parameters::SetChanDrawState(const QString &sSta, const QString &sChan, const QString &LCODE, BOOL bSelected)
{
    CNRTSSTAINFO *si;
    CNRTSCHANINFO *ci;

    QMap<QString, CNRTSSTAINFO * >::Iterator i;
    QMap<QString, CNRTSCHANINFO * >::Iterator j;


    if(!NrtsInfoX.StaInfo.contains(sSta)) return;

    si = NrtsInfoX.StaInfo.value(sSta);
    QString sKey = sChan + "."+LCODE;
    if( !si->ChanInfo.contains(sKey) ) return;
    ci = si->ChanInfo.value(sKey);
    ci->bSelected=bSelected;
    SetStationCheck();


    /*    for(i=NrtsInfoX.StaInfo.begin(); i!=NrtsInfoX.StaInfo.end(); ++i )
    {
        si = *i;
        if(sSta.compare(si->Sta)==0)
        {
            for(j=si->ChanInfo.begin(); j!=si->ChanInfo.end(); ++j )
            {
                ci = *j;
                if(sChan.compare(ci->Chan)==0)
                {
                    if(LCODE.isEmpty()&&ci->LCODE.isEmpty())
                    {
                        ci->bSelected=bSelected;
                        SetStationCheck();
                        return;
                    }
                    else
                    {
                        if( (LCODE.compare(ci->LCODE)==0) &&
                            (!ci->LCODE.isEmpty()))
                            {
                            ci->bSelected=bSelected;
                            SetStationCheck();
                            return;
                            }
                    }
                }
            }
            return;
        }
    }*/
}

void Set_All_Parameters::LoadChanList(QString &sSta)
{
    //    QTableWidgetItem *item0;

    int nRow = 0;
    CNRTSSTAINFO *si;
    CNRTSCHANINFO *ci;
    QMap<QString, CNRTSSTAINFO * >::Iterator i;
    QMap<QString, CNRTSCHANINFO * >::Iterator j;

    char cChan[16],cSpS[16], cLoc[16];

    IDC_CHAN->setRowCount(0);

    //    for(i=NrtsInfoX.StaInfo.begin(); i!=NrtsInfoX.StaInfo.end(); ++i )
    {
        si = NrtsInfoX.StaInfo.value(sSta);
        //		if(sSta.compare(si->Sta)==0)
        {
            int nChan=si->ChanInfo.count();
            IDC_CHAN->setRowCount( nChan );
            for(j=si->ChanInfo.begin(); j!=si->ChanInfo.end(); ++j )
            {
                ci = *j;
                strcpy(cChan, ci->Chan.toLocal8Bit().data());
                if(ci->dSpS>0)
                {
                    sprintf(cSpS,"%.2f",ci->dSpS);
                }
                else
                {
                    sprintf(cSpS,"-");
                }
                strcpy(cLoc, ci->LCODE.toLocal8Bit().data());




                IDC_CHAN->setItem( nRow,   0, new QTableWidgetItem(cChan) );
                IDC_CHAN->setItem( nRow,   1, new QTableWidgetItem(cLoc) );
                IDC_CHAN->setItem( nRow,   2, new QTableWidgetItem(cSpS) );
                IDC_CHAN->item(nRow,   0)->setFlags( Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);

                if(ci->bSelected) 	IDC_CHAN->item(nRow, 0)->setCheckState(Qt::Checked);
                else                IDC_CHAN->item(nRow, 0)->setCheckState(Qt::Unchecked);

                //                IDC_CHAN->item( nRow, 1 )->setText( cLoc );
                //                IDC_CHAN->item( nRow++, 2)->setText(  cSpS );
                ++nRow;

            }
            return;
        }
    }

}

void Set_All_Parameters::SetStationCheck()
{
    QPixmap pixFlag;
    int row = IDC_STA->currentRow();
    QString Sta=IDC_STA->item(row,0)->text();

    if(bHasSelectedChan(ActiveSta))
    {
        pixFlag.load( ":/images/flag.bmp" );
    }
    else
    {
        pixFlag.load( ":/images/blank.bmp" );
    }

    IDC_STA->item(row,0)->setIcon( pixFlag );
}
BOOL Set_All_Parameters::bHasSelectedChan(QString sSta)
{
    CNRTSSTAINFO *si;
    CNRTSCHANINFO *ci;
    QMap<QString, CNRTSSTAINFO * >::Iterator i;
    QMap<QString, CNRTSCHANINFO * >::Iterator j;

    for(i=NrtsInfoX.StaInfo.begin(); i!=NrtsInfoX.StaInfo.end(); ++i )
    {
        si = *i;
        if(sSta.compare(si->Sta)==0)
        {
            for(j=si->ChanInfo.begin(); j!=si->ChanInfo.end(); ++j)
            {
                ci = *j;
                if(ci->bSelected) return TRUE;
            }
        }
    }
    return FALSE;
}
BOOL Set_All_Parameters::bHasSelectedChan(CNRTSSTAINFO *si)
{
    CNRTSCHANINFO *ci;
    QMap<QString, CNRTSCHANINFO * >::Iterator j;
    for(j=si->ChanInfo.begin(); j!=si->ChanInfo.end(); ++j)
    {
        ci = *j;
        if(ci->bSelected) return TRUE;
    }
    return FALSE;
}
void GetWidgetTextRectangle(QWidget *pw, const char *p, QRect &qrc)
{
    QFontMetrics fm = pw->fontMetrics();
    int textWidthInPixels = fm.boundingRect(p).width();
    int textHeightInPixels = fm.height();
    qrc.setRect(0, 0, textWidthInPixels, textHeightInPixels);
}

void Set_All_Parameters::InitStaTable()
{
    QRect qrc, tblrc;
    IDC_STA = new QTableWidget(Channels);

    IDC_STA->setRowCount( 0 );
    IDC_STA->setColumnCount( 2 );


    QStringList  labels;
    labels << "Station" << "Station";
    IDC_STA->setHorizontalHeaderLabels(labels);
    IDC_STA->setSelectionBehavior(QAbstractItemView::SelectRows);
    IDC_STA->setSelectionMode(QAbstractItemView::SingleSelection);
    IDC_STA->verticalHeader()->hide();
    IDC_STA->setEditTriggers(QAbstractItemView::NoEditTriggers);

    GetWidgetTextRectangle(IDC_STA, "Station", qrc);

    tblrc = IDC_STA->rect();
    IDC_STA->setColumnWidth ( 0, qrc.width()+8);
    //
    IDC_STA->setMaximumWidth( qrc.width()*2);
    IDC_STA->setMinimumWidth( qrc.width()*2);

    tblrc = IDC_STA->rect();
    IDC_STA->setColumnWidth ( 0, tblrc.width()-4);

    //	connect(StaTable, SIGNAL(  currentCellChanged ( int , int , int , int  ) ), this,  SLOT(OnCurrentCellChanged(int, int, int, int))  );
    connect( IDC_STA, SIGNAL(  itemClicked(  QTableWidgetItem *) ), this,  SLOT(OnClickStaListTableItem(  QTableWidgetItem *))  );

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
