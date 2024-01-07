#include "workthread.h"

#include <QObject>
#include <QEvent>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfoList>
#include <QSettings>
#include <QDebug>

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "util2.h"
#include "util2qt.h"
#include "gfxutil.h"

#include <math.h>

//---------------------------------------------------------------------------------------------


Worker::Worker(QObject *parent) : QObject(parent)
{
    m_stop = false;
}

void Worker::stop()
{
    m_stop = true;
}

int Worker::xprintf(const char *fmt,  ...)
{
    char buffer[2048];
    va_list argptr;
    int cnt;

    va_start(argptr, fmt);
    cnt = vsprintf(buffer, fmt, argptr);
    va_end(argptr);

    xprint(buffer);

    return cnt;
}

//---------------------------------------------------------------------------------------------


DirScanWorker::DirScanWorker(QString dirName, QObject *parent) : Worker(parent)
{
    m_dirName = dirName;
}

void DirScanWorker::process()
{
    DirItem   ditem;
    int       nr, n,l, pers;
    int       cgg, junk, swap;

    QDir dir(m_dirName);
    dlist.clear();

    QFileInfoList list = dir.entryInfoList();

    l = list.size();

    dlist.clear();

    for(nr=n=0; n < l; n++)
    {
        QFileInfo fileInfo = list.at(n);

        if(!fileInfo.isDir()       ) continue;
        if(fileInfo.fileName()==".") continue;

        ditem.ftype = 0;
        ditem.fname = fileInfo.fileName();

        dlist.append(ditem); nr++;
        pers = (int)((100.*nr)/l);
        xpers(pers, "Scanning directory...");
    }

    for(n=0; n < l; n++)
    {
        QFileInfo fileInfo = list.at(n);

        if(fileInfo.isDir()) continue;

        pers = (int)((100.*nr)/l);
        xpers(pers, "Scanning directory...");

        QByteArray qfn = fileInfo.filePath().toLocal8Bit();
        const char* fname = qfn.data();
        //int   type;

        if(m_stop) break;

        if(is_cst_f(fname))
        {
            //continue;
            ditem.ftype = 10;
            ditem.fname = fileInfo.fileName();
            ditem.type  = 3;
            ditem.ffid  = 0;
            dlist.append(ditem); nr++;
        }
        else if(is_segy_f(fname,swap,cgg,junk)==1)
        {
            ditem.ftype = 10;
            ditem.fname = fileInfo.fileName();
            ditem.type  = 1;
            ditem.ffid  = 0;
            dlist.append(ditem); nr++;
        }
        else if(is_su_f(fname,swap))
        {
            //continue;
            ditem.ftype = 10;
            ditem.fname = fileInfo.fileName();
            ditem.type  = 2;
            ditem.ffid  = 0;
            dlist.append(ditem); nr++;
        }
    }

    if(m_stop)
    {
        dlist.clear();
    }
    else
    {
        emit edir(dlist);
    }

    emit efin("");
    emit finished(); //!!!!
}

//---------------------------------------------------------------------------------------------

DelayScanWorker::DelayScanWorker(SeisFile* sf, QObject *parent) : Worker(parent)
{
    m_sf = sf;
}

void DelayScanWorker::process()
{
    qint64 nt = m_sf->Nt();
    qint64 n;

    int dly;
    int dly_min;
    int dly_max;

    int pers, pp=-1;

    for(n=0;n<nt;n++)
    {
        if(m_stop) break;

        pers=(n)*100./nt;

        if(pp!=pers)
        {
            xpers(pers,"Scanning delay time");
            pp=pers;
        }

        dly = m_sf->Rh(n,"DELRECT");

        if(n==0)
        {
            dly_min=dly;
            dly_max=dly;
        }
        else
        {
            if(dly_min>dly) dly_min=dly;
            if(dly_max<dly) dly_max=dly;
        }
    }

    if(!m_stop)  emit edelay(dly_min,dly_max);

    QString mess;

    emit efin(mess);
    emit finished(); //!!!!
}

//---------------------------------------------------------------------------------------------

TraceFindWorker::TraceFindWorker
    (SeisFile* sf, long long cidx, QString sidx, double sval, QString dir, QString sign,
     QObject *parent) : Worker(parent)
{
    m_sf = sf;
    m_sidx = sidx;
    m_sval = sval;
    m_dir  = dir;
    m_sign = sign;
    m_cidx = cidx; if(m_cidx<0) m_cidx=0;
}

void TraceFindWorker::process()
{
    bool      find = false;
    long long n;

    if(m_sf->Active())
    {
        int thidx = m_sf->ThIdx(m_sidx);

        double cval = m_sf->Th(m_cidx, thidx);
        double sv;

        if     (m_sign=="=") sv=m_sval;
        else if(m_sign=="+") sv=cval+m_sval;
        else if(m_sign=="-") sv=cval-m_sval;
        else                 sv=m_sval;

        long long l = m_sf->Nt();
        int       pers, pp=-1;

        if(m_dir==">")
        {
            for(n=m_cidx;n<l;n++)
            {
                if(m_stop) break;

                if(m_sf->Rh(n,thidx)==sv)
                {
                    find = true;
                    break;
                }

                pers = (100.*n)/l;
                if(pp!=pers)
                {
                    xpers(pers,"Searching...");
                    pp=pers;
                }
            }
        }
        else if(m_dir=="<")
        {
            for(n=m_cidx;n>=0;n--)
            {
                if(m_stop) break;

                if(m_sf->Rh(n,thidx)==sv)
                {
                    find = true;
                    break;
                }

                pers = (100.*n)/l;
                if(pp!=pers)
                {
                    xpers(pers,"Searching...");
                    pp=pers;
                }
            }
        }
        else if(m_dir=="=")
        {
            int tmid;
            int tfst=0;
            int tlst = l-1;

            double vf;
            double vl;
            double vm;

            vf = m_sf->Rh(tfst,thidx);
            vl = m_sf->Rh(tlst,thidx);

            for(;;)
            {
                tmid=(tfst+tlst)/2;

                vm = m_sf->Rh(tmid,thidx);

                if(sv==vm)
                {
                    n = tmid; find=true;
                    break;
                }

                if(tfst>=tlst) break;
                if(m_stop)     break;

                if(vl>vf)
                {
                    if(sv>vm) tfst=tmid+1;
                    else      tlst=tmid-1;
                }
                else
                {
                    if(sv<vm) tfst=tmid+1;
                    else      tlst=tmid-1;
                }

                pers=(tmid)*100./l;

                if(pp!=pers)
                {
                    xpers(pers,"Searching...");
                    pp=pers;
                }
            }
        }
    }

//  int    cnt;

    QString mess;

    if(find) emit efind(n);
    else     mess="Trace Not Found";

    emit efin(mess);
    emit finished(); //!!!!
}
//---------------------------------------------------------------------------------------------

ChangeThExprWorker::ChangeThExprWorker(SeisFile* sf,
        QMap<QString,SeisTrExpr> elist, QString undofn, int mode,
        QObject *parent) : Worker(parent)
{
        m_sf     = sf;
        m_elist  = elist;
        m_undofn = undofn;
        m_mode   = mode;
}

ChangeThExprWorker::~ChangeThExprWorker()
{
}




//---------------------------------------------------------------------------------------------

QString ChangeThExprWorker::undo()
{
    QString mess;
    long long n;

    long long l = m_sf->Nt();
    int       i;
    int       cnt;

    int uf = open_q(m_undofn,O_RDONLY | O_BINARY);

    QList<QString> hlist =  m_elist.keys();
    int nh = hlist.count();

    if(uf<0 || nh<1)
    {
        return "Undo error";
    }

    long long fsz = getfilesize64(uf);

    int       pers, pp=-1;

    int wsz = nh*sizeof(double);

    long long lu = fsz/wsz;

    double*        backv  = new double[nh];

    QMap<QString,double> vlist;


    for(n=0;n<lu;n++)
    {
        /*
        if(m_stop)
        {
            mess="Terminated";
            break;
        }
        */

        cnt=read(uf,backv,wsz);

        if(cnt!=wsz) break;

        for(i=0;i<nh;i++)
        {
            vlist[hlist[i]]=backv[i];
        }

        m_sf->Wvlist(n, &vlist);

        pers=(n)*100./lu;

        if(pp!=pers)
        {
            xpers(pers,"Undoing...");
            pp=pers;
        }
    }

    close(uf);

    delete [] backv;

    unlink_q(m_undofn);

    return "Undone";
}


QString ChangeThExprWorker::update()
{
    QString mess;
    long long n;

    long long l = m_sf->Nt();
    int       i;

    int uf = open_q(m_undofn,O_CREAT | O_TRUNC | O_RDWR | O_BINARY);

    int       pers, pp=-1;

    QList<QString> hlist =  m_elist.keys();

    int nh = hlist.count();

    double*        backv  = new double[nh];

    for(n=0;n<l;n++)
    {
        if(m_stop)
        {
            mess="Terminated";
            break;
        }
        m_sf->Welist(n, &m_elist);

        for(i=0;i<nh;i++)
        {
            backv[i]=m_elist[hlist[i]].V;
        }

        write(uf,backv,sizeof(double)*nh);

        pers=(n)*100./l;

        if(pp!=pers)
        {
            xpers(pers,"Updating...");
            pp=pers;
        }
    }

    close(uf);

    delete [] backv;

    if(m_stop) mess=undo();

    return mess;
}

void ChangeThExprWorker::process()
{
    QString mess;

    if(m_sf->Active())
    {
        if(m_mode==0) mess = update();
        else          mess = undo  ();
    }

    m_sf->Reset();

    emit efin(mess);
    emit finished(); //!!!!
}

//---------------------------------------------------------------------------------------------

SaveAsWorker::SaveAsWorker(SeisFile* sf, QString outfn,
                      QString selh,
                      int     trmin,
                      int     trmax,
                      int     trstp,
                      int     tmmin,
                      int     tmmax,
                      int     frmt, bool rev,
                      QObject *parent) : Worker(parent)
{
    m_sf    = sf;
    m_outfn = outfn;
    m_selh  = selh;
    m_tmmin = tmmin;
    m_tmmax = tmmax;
    m_trmin = trmin;
    m_trmax = trmax;
    m_trstp = trstp;
    m_frmt  = frmt;
    m_rev   = rev;

    m_selhi = sf->ThIdx(m_selh);
}

void SaveAsWorker::process()
{
    QString mess;
    char buf [3200];
    char ebuf[3200];
    int  n, i, j;
    int  cnt;

    QByteArray qtxt;
    QString txthed;

    BinHed binhed;

    txthed = m_sf->TxtHed();

    qtxt = txthed.toLocal8Bit();
    char* s = qtxt.data();


 //   if(m_sf->Active())
 //   {
//    }

    int outf=open_q(m_outfn,O_CREAT|O_TRUNC|O_WRONLY|O_BINARY,0664);

    if(outf<0)
    {
        mess="Cannot create output file: " + m_outfn;
        goto END;
    }

    memset(buf,' ',3200);

    for(i=j=n=0;n<strlen(s);n++)
    {
        char c = s[n];
        if(c=='\n')
        {
            i++; j=0; continue;
        }
        else
        {
            if(j<80 && i<40)
            {
                buf[i*80+j]=c; j++;
            }
        }
    }

    asebdn(ebuf,buf,3200);

    cnt = write(outf,ebuf,3200);

    binhed.set(1,m_frmt,m_sf->binHed());

    cnt = write(outf,binhed.buf(),400);

    if(m_selhi==0) CopyTrcByIdx(outf);
    else           CopyTrcByHdr(outf);

    close(outf);

END:
    emit efin(mess);
    emit finished(); //!!!!
}

void SaveAsWorker::CopyTrcByIdx(int outf)
{
    long long tidx;
    long long tcount = m_sf->Nt();
    int   cnt;
    byte* trbuf;
    int       pp   = -1;
    int       pers;

    int inc = m_trstp; if(inc<1) inc=1;

    if(m_trstp<1)

    for(tidx=m_trmin;tidx<m_trmax;tidx+=inc)
    {
        long long  ti=tidx;
        if(m_rev)  ti = tcount-tidx-1;

        trbuf = m_sf->MakeTrace(cnt, ti, 1, m_frmt,m_tmmin,m_tmmax);
        cnt = write(outf,trbuf,cnt);
        pers = (100.*tidx)/tcount;
        if(pp!=pers)
        {
            xpers(pers,"Saving...");
            pp=pers;
        }

        delete [] trbuf;
    }
}

void SaveAsWorker::CopyTrcByHdr(int outf)
{
    long long tidx;
    long long tcount = m_sf->Nt();
    int   cnt;
    byte* trbuf;
    int       pp   = -1;
    int       pers;

    for(tidx=0;tidx<tcount;tidx++)
    {
        long long  ti=tidx;
        if(m_rev)  ti = tcount-tidx-1;

        int h = m_sf->Rh(ti, m_selhi);

        if(h <m_trmin || h > m_trmax)
        {
            continue;
        }

        if(m_trstp>1 && h%m_trstp) continue;

        trbuf = m_sf->MakeTrace(cnt, ti, 1, m_frmt,m_tmmin, m_tmmax);
        cnt = write(outf,trbuf,cnt);
        pers = (100.*tidx)/tcount;
        if(pp!=pers)
        {
            xpers(pers,"Saving...");
            pp=pers;
        }

        delete [] trbuf;
    }
}
