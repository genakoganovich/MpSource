#ifndef GFXOBJSEISSECT_H
#define GFXOBJSEISSECT_H

#include <QRgb>

#include "gfxobjseis.h"
#include "gfxsrcseis.h"

class GfxObjSeisSect : public GfxObjSeis
{
protected:

    int         m_SelTr;              // Selected trace index

    int*   _si;
    int*   _sj;
    int    _nj;
    int    _ns;

    double m_Ti;                      // Increment for time lines
    bool   m_Tl;                      // Show Time Lines

public:

    GfxObjSeisSect(QObject *parent = 0);

    virtual ~GfxObjSeisSect();

    virtual void   DoDraw()  ;
    virtual void   DoPreset();

    void  setTi(double v)
    {
        m_Ti=v; Update();
    }

    void  setTl(double v)
    {
        m_Tl=v; Update();
    }

    bool Tl()
    {
        return m_Tl;
    }


    void  setSelTr(int v)
    {
        m_SelTr=v; Update();
    }

    int selTr()
    {
        return m_SelTr;
    }


    float getSelMaxAmp();

};

#endif // GFXOBJSEISSECT_H
