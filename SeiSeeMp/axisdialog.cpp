#include "axisdialog.h"
#include "ui_axisdialog.h"
#include "sgyfile.h"
#include "hdrdef.h"

#include <QDebug>

AxisDialog::AxisDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AxisDialog)
{
    ui->setupUi(this);

    selHdrGrid.setRowCount(0);
    selHdrGrid.setColCount(1);
    selHdrGrid.verticalHeader()  ->setVisible(false);
    selHdrGrid.horizontalHeader()->setVisible(false);

    QVBoxLayout* selGridLayout = new QVBoxLayout;
    selGridLayout->setMargin (1);
    selGridLayout->setSpacing(1);
    selGridLayout->addWidget(&selHdrGrid);
    ui->selHdrsBox->setLayout(selGridLayout);

    aviHdrGrid.setRowCount(0);
    aviHdrGrid.setColCount(2);
    aviHdrGrid.verticalHeader()  ->setVisible(false);
    aviHdrGrid.horizontalHeader()->setVisible(false);

    aviHdrGrid.setColWidth(0,80);

    QVBoxLayout* aviGridLayout = new QVBoxLayout;
    aviGridLayout->setMargin (1);
    aviGridLayout->setSpacing(1);
    aviGridLayout->addWidget(&aviHdrGrid);
    ui->aviHdrsBox->setLayout(aviGridLayout);
}

AxisDialog::~AxisDialog()
{
    delete ui;
}

void AxisDialog::on_closeButton_pressed()
{
    close();
}


void AxisDialog::FillAviGrid()
{
    int n,i;
    int l = hdrDefList->count();

    for(n=i=0;n<l;n++)
    {
       QString name = hdrDefList->item(n)->name;

       if(hdrList.contains(name)) continue;
       i++;
    }

    aviHdrGrid.setRowCount(i);

    for(n=i=0;n<l;n++)
    {
       QString desc = hdrDefList->item(n)->desc;
       QString name = hdrDefList->item(n)->name;

       if(hdrList.contains(name)) continue;

       aviHdrGrid.setCell(i,0,name);
       aviHdrGrid.setCell(i,1,desc);

       i++;
    }
}

void AxisDialog::FillForm()
{
    changed = false;

    hdrList = ckList->List();

    hdrDefList=TraceHdrsSet.List();

    FillAviGrid();

    int     n;

    int l = hdrList.count(); selHdrGrid.setRowCount(l);

    for(n=0;n<l;n++)
    {
        selHdrGrid.setCell(n,0,hdrList[n]);
    }

    ui->dTCbx->setEditText(QString::number(dT));

    ui->ckTimLines->setChecked(tL);
}

void AxisDialog::show()
{
    FillForm();
    QDialog::show();
}

void AxisDialog::on_applyButton_pressed()
{
    if(!changed) return;

    int n;

    hdrList.clear();
    for(n=0;n<selHdrGrid.RowCount();n++)
    {
        hdrList.append(selHdrGrid.Cell(n,0));
    }
    ckList->setList(hdrList);
    emit changedEvent();
}

void AxisDialog::on_okButton_pressed()
{
    on_applyButton_pressed();
    close();
}

void AxisDialog::on_addBtn_pressed()
{
    int row = aviHdrGrid.curRow();

    if(row>=0)
    {
        QString name = aviHdrGrid.Cell(row,0);

        int nr = selHdrGrid.RowCount();
        selHdrGrid.setRowCount(nr+1);
        selHdrGrid.setCell(nr,0,name);
        aviHdrGrid.delRow(row);
        hdrList.append(name);
        changed=true;
    }
}

void AxisDialog::on_delBtn_clicked()
{
    int row = selHdrGrid.curRow();

    if(row>=0)
    {
        QString name = selHdrGrid.Cell(row,0);
        hdrList.removeAll(name);
        selHdrGrid.delRow(row);
        FillAviGrid();
        changed=true;
    }
}

void AxisDialog::on_dellAllBtn_clicked()
{
    if(hdrList.count()<1) return;

    hdrList.clear();
    selHdrGrid.setRowCount(0);
    FillAviGrid();
    changed=true;
}

void AxisDialog::on_upBtn_clicked()
{
    int row = selHdrGrid.curRow();

    if(row<1) return;

    QString v1 = selHdrGrid.Cell(row-1,0);
    QString v2 = selHdrGrid.Cell(row  ,0);
    selHdrGrid.setCell(row-1,0,v2);
    selHdrGrid.setCell(row  ,0,v1);

    selHdrGrid.setCurCell(row-1);
    changed=true;
}

void AxisDialog::on_downBtn_clicked()
{
    int row = selHdrGrid.curRow();

    if(row>selHdrGrid.RowCount()-2) return;

    QString v1 = selHdrGrid.Cell(row  , 0);
    QString v2 = selHdrGrid.Cell(row+1, 0);
    selHdrGrid.setCell(row  ,0,v2);
    selHdrGrid.setCell(row+1,0,v1);

    selHdrGrid.setCurCell(row+1);
    changed=true;
}

void AxisDialog::on_dTCbx_editTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

    QString txt = ui->dTCbx->currentText();
    bool ok;

    int dt = txt.toInt(&ok);
    if(!ok) return;

    if(dT!=dt)
    {
        dT=dt; changed=true;
    }
}

void AxisDialog::on_ckTimLines_toggled(bool checked)
{
    tL = checked; changed=true;
}
