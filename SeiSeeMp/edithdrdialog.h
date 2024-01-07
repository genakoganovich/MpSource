#ifndef EDITHDRDIALOG_H
#define EDITHDRDIALOG_H

#include <QDialog>

#include "sgyfile.h"
#include "hdrdef.h"
#include "mystringtable.h"

namespace Ui {
class EditHdrDialog;
}

class EditHdrDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditHdrDialog(QWidget *parent = 0);
    ~EditHdrDialog();

    MyStringTable     hdrGrid;
    MyStringTable     insGrid;
    bool              changed;
    bool              busy;
    int               curtype;

    void show();

private:
    Ui::EditHdrDialog *ui;

    void setChanged(bool v);
    void enableEdit(bool enable);

    void FillHdrGrid();
    void FillInsGrid();

    int findrow(QString name);

    void onUserInput();

private slots:

    void hdrTabEvent(int row, int mode);

    void on_btnClose_clicked();
    void on_cbSet_currentIndexChanged(int index);
    void on_btnAddItem_clicked();
    void on_cbSet_editTextChanged(const QString &arg1);
    void on_btnReset_clicked();
    void on_btnUpdate_clicked();
    void on_edName_textChanged(const QString &arg1);
    void on_edDesc_textChanged(const QString &arg1);
    void on_edPos_textChanged(const QString &arg1);
    void on_btnDelItem_clicked();
    void on_btnDiscard_clicked();
    void on_btnApply_clicked();

    void on_txtExpr_textChanged();

    void on_tabMode_currentChanged(int index);

    void on_insBtn_clicked();

signals:
    void changedEvent();
};

#endif // EDITHDRDIALOG_H
