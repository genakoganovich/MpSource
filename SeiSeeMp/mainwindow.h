#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QWidget>
#include <QMainWindow>
#include <QApplication>
#include <QStack>
#include <QProgressBar>
#include <QLabel>
#include <QDebug>
#include <QThread>
#include <QPlainTextEdit>

#include "gfxview.h"
#include "myscrollarea.h"
#include "gfxsrcseistest.h"
#include "gfxobjseissect.h"
#include "gfxobjtaxis.h"
#include "gfxobjseishdrs.h"
#include "gfxsrcseismemsegd.h"
#include "mystringtable.h"
#include "gfxsctlist.h"
#include "gfxsrcfile.h"
#include "myobjptrlist.h"
#include "gfxobjhsrslab.h"

#include "mystringtable.h"
#include "mxstringtable.h"
#include "myhugetable.h"

#include "procparmdialog.h"
#include "aboutdialog.h"
#include "axisdialog.h"
#include "edithdrdialog.h"
#include "saveasdialog.h"

#include "workthread.h"


#define VERSION "3.0 alpha.37"

/*
class zdata
{
public:
    int    xo, yo;
    double xs, ys;

    zdata(double xxs, double yys, int xxo, int yyo)
    {
        xo=xxo; yo=yyo; xs=xxs; ys=yys;
    }

    zdata() {}
};
*/

namespace Ui {
class MainWindow;
}

class myEventCatcher:public QObject
{
    Q_OBJECT
protected:

    int _tag;

public:

    myEventCatcher(int tag, QObject * parent):QObject(parent) { _tag = tag; }
   ~myEventCatcher() {}

   bool eventFilter(QObject* object,QEvent* event)
   {
      if(event->type() == QEvent::Wheel)
       {
          QWheelEvent* e = dynamic_cast<QWheelEvent *>(event);
          emit whellEvent(_tag,e);
          return true;
       }

       // standard event processing
       return QObject::eventFilter(object, event);
   }

signals:
   void whellEvent(int tag, QWheelEvent* event);

public slots:

};


class myTextEditEventCatcher:public QObject
{
    Q_OBJECT
protected:

    int _tag;

public:

    myTextEditEventCatcher(int tag, QObject * parent):QObject(parent) { _tag = tag; }
   ~myTextEditEventCatcher() {}

   bool eventFilter(QObject* object,QEvent* event)
   {
       if(event->type() == QEvent::KeyPress)
       {
           QKeyEvent* e = static_cast<QKeyEvent *>(event);
           emit keyEvent(_tag, e);
       }

       // standard event processing
       return QObject::eventFilter(object, event);
   }

signals:
   void keyEvent(int tag, QKeyEvent* event);

public slots:

};



class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void execProc(SeisFile* sf, int ns, double si, float* smp);

    void sclZoom (double zx, double zy, int xc, int yc);
    void sclZoomV(double zx, double zy, int xc, int yc);
    void sclZoomH(double zx, double zy, int xc, int yc);

    void winZoom(QRect r);

private slots:

    void binHdrGridChangedEvent();

    void dirGridEvent(int row, int mode);

    void hdrListDtGridEvent      (qint64 row, int mode);
    void hdrListDtGridHeaderEvent(int col);
    void hdrElstDtGridHeaderEvent(int col);

    void hdrListCkEvent(int row, int mode);
    void hdrElstCkEvent(int row, int mode);

    void viewMouseEvent(QMouseEvent* event);

    void procParmEvent();
    void axesDlgEvent();
    void hdreDlgEvent();

    void hdrListDtGridDataEvent(int r, int c, QString& v);
    void hdrElstDtGridDataEvent(int r, int c, QString& v);

    void txtEditKeyEvent(int tag, QKeyEvent* event);
    void txtEditChanged ();

    void edWhellEvent(int tag, QWheelEvent* event);

    virtual void closeEvent(QCloseEvent * event);

    void ResetSrc();

    void on_ckAgc_toggled(bool checked);

    void on_ckFilt_toggled(bool checked);

    void on_ckNorm_toggled(bool checked);

    void on_ckWiggle_toggled(bool checked);

    void on_ckGray_toggled(bool checked);

    void on_ckColor_toggled(bool checked);

    void on_rbNon_toggled(bool checked);

    void on_rbPos_toggled(bool checked);

    void on_rbNeg_toggled(bool checked);

    void on_zoomAllBtn_pressed();

    void on_zoomVallBtn_pressed();

    void on_zoomHallBtn_pressed();

    void on_edTr_editingFinished();

    void on_edTm_editingFinished();

    void on_edGn_editingFinished();

    void on_zoomPreBtn_pressed();

    void on_zoomOutBtn_pressed();

    void on_zoomInBtn_pressed();

    void on_selDirBtn_pressed();

    void on_refreshBtn_pressed();

    void on_procParmBtn_pressed();

    void on_zoomWinBtn_pressed();

    void on_actionOpen_Directory_triggered();

    void on_actionAbout_triggered();

    void on_TrSlider_valueChanged(int p);

    void on_TrSlider_sliderReleased();

    void on_TrSlider_sliderPressed();

    void on_TmSlider_sliderPressed();

    void on_TmSlider_sliderReleased();

    void on_TmSlider_valueChanged(int p);

    void on_GnSlider_sliderPressed();

    void on_GnSlider_sliderReleased();

    void on_GnSlider_valueChanged(int p);

    void on_TxtHdrEdit_cursorPositionChanged();

    void on_axisBtn_pressed();

    void on_actionAxes_Setup_triggered();

    void on_actionParameters_triggered();

    void on_actionHeader_Editor_triggered();

    void on_btnEdHdr_clicked();

    void on_btnTxtRd_clicked();

    void on_actionLoad_Text_Header_from_File_triggered();

    void on_actionLoad_XML_triggered();

    void on_actionExport_Text_Header_to_File_triggered();

    void on_btnTxtRdx_clicked();

    void on_btnTxtRst_clicked();

    void on_btnTxtUpd_clicked();

    void on_ckTrEd_toggled(bool checked);

    void on_btnBinRst_clicked();

    void on_btnBinUpd_clicked();

    void on_InfoTab_currentChanged(int index);

    void on_btnLastTr_clicked();

    void on_btnFirstTr_clicked();

    void on_btnSbin_clicked();

    void on_cbSval_editTextChanged(const QString &arg1);

    void on_cbSidx_currentIndexChanged(const QString &arg1);

    void x_dir  (DirList dlist);
    void x_progr(int pers, QString mess);
    void x_fin  (QString mess);
    void x_fin_e(QString mess);

    void x_find (int tridx);
    void x_find_fin (QString mess);

    void x_delay  (int dmin, int dmax);

//  void x_pers (int pers);

    void on_btnSfwd_clicked();

    void on_btnSbkw_clicked();

    void on_btnSstop_clicked();

    void on_btnUpdTrh_clicked();

    void on_cbEnval_editTextChanged(const QString &arg1);

    void on_btnCkNon_clicked();

    void on_btnCkAll_clicked();

    void on_btnCkNonE_clicked();

    void on_edExpr_textChanged(const QString &arg1);

    void on_btnNexp_clicked();

    void on_btnLexp_clicked();

    void on_btnHexp_clicked();

    void on_btnClrExp_clicked();

    void on_btnUpdE_clicked();

    void on_btnUndE_clicked();

    void on_actionSave_As_triggered();

    void on_btnLastTr_2_clicked();

    void on_btnFirstTr_2_clicked();

    void on_autoGainBtn_clicked();

    void on_rbDirNorm_toggled(bool checked);

    void on_rbDirRev_toggled(bool checked);

    void on_ckTimLines_toggled(bool checked);

    void on_actionOpen_File_triggered();

    void on_ckDly_toggled(bool checked);

private:
    Ui::MainWindow *ui;

//  ReadThread*    WorkThread;

    int    eExpIdx;

    QProgressBar *progressBar;

    QLabel * m_statMess;
    QLabel * m_statTrcn;
    QLabel * m_statTime;
    QLabel * m_statAmp;
    QLabel * m_statFfid;
    QLabel * m_statSp;
    QLabel * m_statusRight;

    ProcParmDialog ProcParmDlg;
    AboutDialog    AboutDlg;
    AxisDialog     AxisDlg;
    EditHdrDialog  EdHdrDlg;
    SaveAsDialog   SaveAsDlg;

    QList<DirItem> dlist;
    QStack<zdata>  zstack;

    QList<QRgb>    rgb;

    QString        find;

    QString        undofn;

    double     _f1, _f2, _f3, _f4;
    double     _agcw;

    double     _dly_min;
    double     _dly_max;

    bool              busy;
    bool              expu_running;

    double            xss, yss, gss; // sliders' values

    QVector<bool>     chsSel;

    GfxView           timeView;
    GfxView           hdrsView;
    GfxView           seisView;
    GfxView           hlabView;

    MyScrollArea*     hdrsScrl;
    MyScrollArea*     timeScrl;
    MyScrollArea*     seisScrl;

    GfxSrcFile        seisSrc;
    GfxObjSeisSect    seisSct;
    GfxObjSeisHdrs    hdrsAxis;
    GfxObjTAxis       timeAxis;
    GfxObjHsrsLab     hdrsLab;

    MyStringTable     dirGrid;

    MyStringTable     binHdrGrid;
    MyStringTable     trcHdrGrid;
    MyStringTable     trcDatGrid;

    MyStringTable     hdrListCkGrid;
    MyHugeTable       hdrListDtGrid;

    MyStringTable     hdrElstCkGrid;
    MyHugeTable       hdrElstDtGrid;

    CkListSet         hdrElstCk;
    CkListSet         hdrListCk;
    CkListSet         hdrAxisCk;

    QString           txtHdrDir;
    QString           txtHdrFile;
    QString           savDir;
    QString           curDir;
    QString           curHdr;
    QString           curFn;  // file number in ltod

    QString           curFileName;

    QMap<QString,SeisTrExpr> exprList;
    QMap<QString,SeisTrExpr> undoList;

    int  xprintf(QPlainTextEdit *edit, const char *fmt,  ...);
    void xprint (QPlainTextEdit *edit, QString str);

    void ClrUndoE();

    void setEnabledAllBtns(QWidget* box, bool enabled);

    int allSectWidth();

    void FillDirGrid(QList<DirItem> list);

    void SelectTrace(int it);

    void ChangeDataDir(QString Dname, QString Find="");
    void ScanLtod     ();

    void SetZoomC (double  xs,  double  ys, int  xc, int  yc);
    void SetZoom  (double  xs,  double  ys, int  xo, int  yo, bool push=true);
    void GetZoom  (double& xs,  double& ys, int& xo, int& yo);

    void Clear();

    void ShowProgress(QString mes, int pers);

    int  InitSeisView();

    int  ScanDelay();

    int  OpenSeisFile(int frm);

    void ArrangeSections();

    void FillBinHdrGrid();
    void FillEdits();
    void FillControls();

    void FillHdrListGrids();
    void FillHdrElstGrids();

    void SetSearchControls(bool on);
    void SaveSval();

    void GetRegInfo ();
    void SaveRegInfo();

//  void NewFileReady(TSegD* newsegd);

    void SetHdrDatList();
    void SetHdrDatElst();

    void SetTrEdCurVal();

    void loadTxtHdr();
    void exportTxtHdr(QString fileName);

    void checkTxtHdrChange();
    int  checkBinHdrChange();

    void FindTrace(QString dir);

signals:
    void stop_dirs();
    void stop_find();
    void stop_expu();
    void stop_dlys();
};

#endif // MAINWINDOW_H
