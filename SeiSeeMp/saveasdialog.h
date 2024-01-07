#ifndef SAVEASDIALOG_H
#define SAVEASDIALOG_H

#include <QDialog>

#include "mystringtable.h"

#include "seisfile.h"
#include "sgyfile.h"

#include "workthread.h"

namespace Ui {
class SaveAsDialog;
}

class SaveAsDialog : public QDialog
{
    Q_OBJECT

public:

    SeisFile*  sf;
    QString*   savDir;

    explicit SaveAsDialog(QWidget *parent = 0);
    ~SaveAsDialog();

    void show();

private slots:

    void hdrListEvent(int row, int mode);

    void on_btnSave_clicked();

    void on_btnClose_clicked();

    void on_ckTrAll_clicked();

    void on_ckTmAll_clicked();

    void on_btnTrMin_clicked();

    void on_btnTrMax_clicked();

    void on_btnTrStp_clicked();

    void on_btnTmMin_clicked();

    void on_btnTmMax_clicked();

    void x_progr(int pers, QString mess);
    void x_fin  (QString mess);

private:

    bool running;

    MyStringTable     hdrListGrid;

    Ui::SaveAsDialog *ui;


    void ShowProgress(QString mes, int pers);

    void FillHdrListGrid();
    void FillLimits();

    int  ReadTxt(QLineEdit* edt, bool& ok);

signals:
    void stop();
};

#endif // SAVEASDIALOG_H
