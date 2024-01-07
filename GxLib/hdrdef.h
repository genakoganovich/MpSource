#ifndef HDRDEF_H
#define HDRDEF_H

using namespace std;

#include <string>
#include <stdio.h>

#include <QObject>
#include <QMap>
#include <QStringList>

#include "seistrexpr.h"

/*
class TraceExpr
{
    string exprstr;

public:

    void setExprStr(QString e);

    string ExprStr(QString s);
};
*/

class CkList
{
private:
    QStringList Items;

public:

    int operator[](QString i)
    {
        if(Items.contains(i)) return 2;
        return 0;
    }

    void clear()
    {
        Items.clear();
    }

    void del(QString i)
    {
        Items.removeAll(i);
    }

    void set(QString i)
    {
        if(!Items.contains(i))
        {
            Items.append(i);
        }
    }

    QStringList List()
    {
        return Items;
    }

    void setList(QStringList list)
    {
        Items=list;
    }
};

class CkListSet
{
private:
    int cidx;
    QMap<int,CkList> Items;

public:
    CkListSet()
    {
        cidx=0;
    }

    void setListIdx(int i)
    {
        cidx=i;
    }

    int listIdx()
    {
        return cidx;
    }

    int operator[](QString i)
    {
        return Items[cidx][i];
    }

    void clear()
    {
        Items[cidx].clear();
    }

    void set(QString i)
    {
        Items[cidx].set(i);
    }

    void del(QString i)
    {
        Items[cidx].del(i);
    }

    QStringList List()
    {
        return Items[cidx].List();
    }

    void setList(QStringList list)
    {
        Items[cidx].setList(list);
    }
};


static QString _fname [] =
{
  "Integer 8-bit",
  "Integer 16-bit",
  "Unsigned Integer 16-bit",
  "Integer 32-bit",
  "IEEE Float 32-bit",
  "IEEE Float 64-bit",
  "IBM  Float 32-bit"
};

static int _fcode [] =
{
   1, // Integer 1
   2, // Integer 2
  12, // Unsigned Integer 2
   4, // Integer 4
  14, // IEEE Float 4
  18, // IEEE Float 8
  24  // IBM  Float 4
};


class FormatList
{

public:

  static int codei(int idx)
  {
      if(idx<0 || idx>= count()) return -1;
      return _fcode[idx];
  }

  static QString namei(int idx)
  {
      if(idx<0 || idx>= count()) return "";
      return _fname[idx];
  }


  static int index(int code)
  {
      int n;

      for(n=0;n<count();n++)
          if(_fcode[n]==code) return n;

        return -1;
  }


  static int index(QString name)
  {
      int n;

      for(n=0;n<count();n++)
          if(_fname[n]==name) return n;

        return -1;
  }


  static QString name(int code)
  {
    int n;

    for(n=0;n<count();n++)
        if(_fcode[n]==code) return _fname[n];
      return "Unknown";
  }

  static int code(QString name)
  {
    int n;

    for(n=0;n<count();n++)
        if(_fname[n]==name) return _fcode[n];
    return -1;
  }

  static int count()
  {
      return  sizeof(_fcode)/sizeof(int);
  }
};



class TrHdrDef
{
public:

    int           frmt; // format array
    int           pos;  // position
    QString       desc; // description
    QString       name; // short name
    int           edit; // 2 - editable

    SeisTrExpr    expr;

public:

    QString bytesStr();

    explicit TrHdrDef();
    explicit TrHdrDef(QString n, QString d, int f, int p, bool e = true);
    explicit TrHdrDef(QString n, QString d, QString expr);
};

class TrHdrDefList
{

private:

    QList<TrHdrDef>   Hdrs;
    QMap<QString,int> Hidx;
    int               Type;

    void reindex()
    {
        int n;

        Hidx.clear();

        for(n=0;n<Hdrs.size();n++)
        {
            Hidx[item(n)->name]=n;
        }
    }

public:

    QStringList NameList()
    {
        return Hidx.keys();
    }

    TrHdrDefList& Assign(const TrHdrDefList& src)
    {
        if (this ==&src)return *this;

        Hdrs = src.Hdrs;
        Hidx = src.Hidx;
        Type = src.Type;

        return *this;
    }

    TrHdrDefList& operator=(const TrHdrDefList& src)
    {
        return Assign(src);
    }

    explicit TrHdrDefList(int type=0);

    TrHdrDef* item(int i)
    {
        if(i<0 || i>=Hdrs.size()) return NULL;

        return &(Hdrs[i]);
    }

    TrHdrDef* item(QString hname)
    {
        if(Hidx.contains(hname))
        {
            int i=Hidx[hname]; return item(i);
        }

        return NULL;
    }

    void setItem(TrHdrDef h, int i)
    {
        TrHdrDef* hdr = item(i);

        QString name = hdr->name;

        hdr->desc=h.desc;
        hdr->pos =h.pos;
        hdr->frmt=h.frmt;
        hdr->name=h.name;

        if(name!=h.name)
        {
            reindex();
        }
    }

    int index(QString hname)
    {
        if(Hidx.contains(hname))
        {
            return Hidx[hname];
        }

        return -1;
    }

    void del(QString hname)
    {
        int i = index(hname);
        Hdrs.removeAt(i);
        reindex();
    }

    void add(TrHdrDef hdr)
    {
        int i = index(hdr.name); if(i>=0) return;
        if(hdr.name.trimmed()=="") return;

        Hdrs.append(hdr);
        Hidx[hdr.name]=Hdrs.size()-1;
    }

    void edit(TrHdrDef hdr)
    {
        int i = index(hdr.name);

        Hdrs[i].desc=hdr.desc;
        Hdrs[i].frmt=hdr.frmt;
        Hdrs[i].pos =hdr.pos;
    }

    int count()
    {
        return Hdrs.count();
    }

    void setType(int t)
    {
        Type=t;
    }

    int type()
    {
        return Type;
    }
};


class TrHdrsMap: public QObject
{
    Q_OBJECT
private:
    int cidx;

public:
    QMap<int, TrHdrDefList> HdrsList;

    explicit TrHdrsMap(QObject *parent = 0);


    TrHdrDefList& operator[](int i)
    {
        if(HdrsList.contains(i)) return HdrsList[i];
        return HdrsList[0];
    }

    TrHdrDefList* List(int i = -1)
    {
        if(i<0) i = cidx;
        if(HdrsList.contains(i)) return &HdrsList[i];
        return NULL;
    }

    void setListIdx(int i)
    {
        cidx=i;
    }

    int listIdx()
    {
        return cidx;
    }
};

#endif // HDRDEF_H
