#ifndef SET_ALL_PARAMETERS_H
#define SET_ALL_PARAMETERS_H

#include "nrtsinfo.h"
#undef max
#undef min
#include <QTableWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QDialog>

class Set_All_Parameters : public QDialog
{
    Q_OBJECT

public:
    Set_All_Parameters( QWidget* parent = 0);
    ~Set_All_Parameters();
	void SaveParameters();
	void LoadStaList();
	void LoadChanList(QString &sSta);
	void SetChanDrawState(const QString &sSta, const QString &sChan, const QString &LCODE, BOOL bSelected);
	void SetStationCheck();


	CNRTSINFO NrtsInfoX;

    QPushButton* buttonHelp;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QTabWidget* tabWidget;
    QWidget* Channels;
    QTableWidget* IDC_CHAN;
    QLabel* Port_number_2;
    QLabel* ISI_Server_2;
    QPushButton* IDC_LOADLIST;
    QTableWidget* IDC_STA;
    QLineEdit* IDC_NRTSSERVER;
    QLineEdit* IDC_PORT;
    QWidget* Display_parameters;
    QFrame* frame3;
    QLabel* Displayed_window_size;
    QLineEdit* IDC_REFRESHTIME;
    QLineEdit* IDC_DELAY;
    QLabel* Buffered_window_size;
    QLineEdit* IDC_BUFFEREDTIME;
    QLineEdit* IDC_DISPLAYTIME;
    QLabel* Refresh_time;
    QLabel* Delay__sec;

private:
	BOOL bHasSelectedChan(QString sSta);
	BOOL bHasSelectedChan(CNRTSSTAINFO *si);

protected:

    void InitStaTable();

    QHBoxLayout* Layout1;
    QSpacerItem* Horizontal_Spacing2;
    QGridLayout* layout14;
	QString ActiveSta;

protected slots:
    virtual void languageChange();
    virtual void OnOk();
	void OnLoadList();
    void OnClickStaListTableItem(QTableWidgetItem *i);
    void OnClickChanListTableItem(QTableWidgetItem *);

};

#endif // SET_ALL_PARAMETERS_H

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
