#ifndef AXISDIALOG_H
#define AXISDIALOG_H

#include <QDialog>
#include "mystringtable.h"
#include "hdrdef.h"

namespace Ui {
class AxisDialog;
}

class AxisDialog : public QDialog
{
    Q_OBJECT

private:

    MyStringTable     selHdrGrid;
    MyStringTable     aviHdrGrid;

    QStringList hdrList;

    bool              changed;

public:
    explicit AxisDialog(QWidget *parent = 0);
    ~AxisDialog();

   TrHdrDefList*  hdrDefList;
   CkListSet*  ckList;
   int         dT;
   bool        tL;

    void show();

private slots:
    void on_closeButton_pressed();

    void on_addBtn_pressed();

    void on_applyButton_pressed();

    void on_okButton_pressed();

    void on_delBtn_clicked();

    void on_dellAllBtn_clicked();

    void on_upBtn_clicked();

    void on_downBtn_clicked();

    void on_dTCbx_editTextChanged(const QString &arg1);

    void on_ckTimLines_toggled(bool checked);

private:
    Ui::AxisDialog *ui;

    void FillAviGrid();
    void FillForm();

signals:
    void changedEvent();
};

#endif // AXISDIALOG_H
