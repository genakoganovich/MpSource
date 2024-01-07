#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#ifdef _MSC_VER
    #pragma warning( push )
    #pragma warning( disable : 4100 4244 4267 4305) // implicit conversion, possible loss of data
#else
    #pragma GCC diagnostic ignored "-Wsign-compare"
    #pragma GCC diagnostic ignored "-Wunused-parameter"
#endif


#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDir>

#include "seisfile.h"
#include "sgyfile.h"

//---------------------------------------------------------------------------------------------

class DirItem
{
public:
    QString    fname;
    int        ftype;  // 0 - dir, 1 - Sgd, 2 - ltod, 3 - file in ltod
    int        ffid;
    int        type;   // Sgd type
    qint64     lpos;   // position in ltod
    qint64     llen;   // file length in ltod
};

//---------------------------------------------------------------------------------------------


class Worker : public QObject
{
    Q_OBJECT

public:

    explicit Worker(QObject *parent = 0);

protected:

    bool           m_stop;

    virtual void xprint(QString str)
    {
        emit eprint(str);
    }

    virtual void xprogr(int pers, QString str="")
    {
        emit eprogr(pers, str);
    }

    virtual void xpers(int pers, QString str="")
    {
        QString progr=QString::number(pers)+"%";
        emit eprogr(pers, str);
    }

    virtual int xprintf(const char *fmt,  ...);

public slots:
    virtual void process()
    {
        emit efin("");
        emit finished();
    }

    void stop();

signals:
    void finished();
    void eprint(QString str);
    void eprogr (int pers, QString str);
    void efin   (QString rc);
    void elckt  (QString tape, QString info, bool lock);
};
//---------------------------------------------------------------------------------------------


typedef QList<DirItem> DirList;

class DirScanWorker : public Worker
{
    Q_OBJECT

public:

    explicit DirScanWorker(QString dirName, QObject *parent = 0);

protected:

    QString    m_dirName;
    int        m_type;       // 1 - dir, 2 - ltod, 3 - tape

    DirList    dlist;


public slots:
    virtual void process();

signals:
    void edir(DirList dist);
};
//---------------------------------------------------------------------------------------------


class TraceFindWorker : public Worker
{
    Q_OBJECT

public:

    explicit TraceFindWorker(
            SeisFile* sf, long long cidx,
            QString sidx, double sval,
            QString dir, QString sign,
            QObject *parent=0);

protected:

    SeisFile*  m_sf;
    QString    m_sidx;
    double     m_sval;
    QString    m_dir;  // direction
    QString    m_sign;
    long long  m_cidx;


public slots:
    virtual void process();

signals:
    void efind(int tridx);
};
//---------------------------------------------------------------------------------------------

class DelayScanWorker: public Worker
{
    Q_OBJECT

public:

    explicit DelayScanWorker(SeisFile* sf, QObject *parent=0);

protected:

    SeisFile*  m_sf;

public slots:
    virtual void process();

signals:
     void edelay(int dlymin, int dlymax);
};
//---------------------------------------------------------------------------------------------

class ChangeThExprWorker : public Worker
{
    Q_OBJECT

public:

    explicit ChangeThExprWorker(SeisFile* sf,
                                QMap<QString,SeisTrExpr> elist,
                                QString undofn, int mode,
                                QObject *parent=0);

    ~ChangeThExprWorker();

protected:

    SeisFile*                 m_sf;
    QMap<QString,SeisTrExpr>  m_elist;

    QString                   m_undofn;
    int                       m_mode; // 0 - update, 1 - undo

    QString update();
    QString undo  ();

public slots:
    virtual void process();

};
//---------------------------------------------------------------------------------------------


class SaveAsWorker : public Worker
{
    Q_OBJECT

public:

    explicit SaveAsWorker(SeisFile* sf,
                          QString outfn,
                          QString selh,
                          int     trmin,
                          int     trmax,
                          int     trstp,
                          int     tmmin,
                          int     tmmax,
                          int     frmt,
                          bool    rev,
                          QObject *parent=0);
protected:

    SeisFile*                 m_sf;
    QString                   m_outfn;

    QString                   m_selh;
    int                       m_selhi;
    int                       m_trmin;
    int                       m_trmax;
    int                       m_trstp;
    int                       m_tmmin;
    int                       m_tmmax;
    int                       m_frmt;
    bool                      m_rev;

    QString save();

    void CopyTrcByIdx(int outf);
    void CopyTrcByHdr(int outf);

public slots:
    virtual void process();

};
//---------------------------------------------------------------------------------------------




#endif // WORKTHREAD_H
