#ifndef SGYFILE_H
#define SGYFILE_H

#include "seisfile.h"

class SgyFile : public SeisFile
{
    Q_OBJECT

protected:

    virtual void  Open (string fn);
    virtual void  Close();

    virtual bool   ReadTxtHed();

    virtual bool   ReadBinHed();

    virtual void   ReadTrace(long long ntr);

    virtual float  GetSample(int idx, byte *inptrc);
public:
    explicit SgyFile(QObject *parent = 0);
    virtual ~SgyFile();

    virtual float*  Ts (long long ntr);
    virtual float*  Rs(long long ntr);

    float*          Rs(long long ntr, byte* hed);

    virtual QString typeName() { return "SEG-Y"; }
    virtual int     typIdx()   { return 1;       }

    int ReadRawTrace(byte* &buf, long long ntr, bool header_only=false);
    int WriteRawTrace(byte* buf, long long ntr, bool header_only=false);

    virtual bool UpdateTxtHed   (QString txt);
    virtual bool UpdateBinHed   (QVector<QString> vals);

    virtual bool Active()
    {
        if(_f<0) return false;
        else     return true;
    }

signals:

public slots:

};

class SuFile : public SgyFile
{
    Q_OBJECT

protected:

    virtual void  Open (string fn);
    virtual void  Close();

    virtual float*  Rs(long long ntr);

    virtual bool   ReadBinHed();

    virtual void   ReadTrace(long long ntr);

public:
    explicit SuFile(QObject *parent = 0);
    virtual ~SuFile();

    int ReadRawTrace(byte* &buf, long long ntr, bool header_only=false);
    int WriteRawTrace(byte* buf, long long ntr, bool header_only=false);

    virtual QString typeName() { return "SU";}
    virtual int     typeIdx()  { return    2;}

signals:

public slots:

};


class CstFile : public SgyFile
{
    Q_OBJECT

protected:

    virtual void  Open (string fn);
    virtual void  Close();

    virtual float*  Rs(long long ntr);

    virtual bool   ReadBinHed();

    virtual void   ReadTrace(long long ntr);

public:

    explicit CstFile(QObject *parent = 0);
    virtual ~CstFile();

    virtual QString typeName() { return "CST";}
    virtual int     typeIdx()  { return 3;    }

    int ReadRawTrace(byte* &buf, long long ntr, bool header_only=false);
    int WriteRawTrace(byte* buf, long long ntr, bool header_only=false);

    virtual float   GetSample(int idx, byte* inptrc);


signals:

public slots:

};




#endif // SGYFILE_H
