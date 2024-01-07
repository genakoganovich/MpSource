#ifndef MYSCROLLAREA_H
#define MYSCROLLAREA_H

#include <QWidget>
#include <QScrollArea>
#include <QRubberBand>
#include <QPainter>
#include <QScrollBar>

class MyScrollArea : public QScrollArea
{
    Q_OBJECT

private:

    QWidget* plot;
    int      mv;

    bool     ignore;

    int      mvrb; // moveable by right mouse button 1-hor, 2-vert, 3 - both;
    int      xo;
    int      yo;

    QRubberBand*    rubberBand;
    QPoint          origin;

//    QScrollBar *horizontalScrollBar() const;
//    QScrollBar *verticalScrollBar() const;

    virtual void wheelEvent        ( QWheelEvent*  event);
    virtual void mousePressEvent   ( QMouseEvent * event );
    virtual void mouseReleaseEvent ( QMouseEvent * event );
    virtual void mouseMoveEvent    ( QMouseEvent * event );

    void emitZoomChanged(double zx, double zy, int x, int y);

    void keyPressEvent(QKeyEvent *event);

    virtual void scrollContentsBy(int dx, int dy);

public:
    MyScrollArea(QWidget* plt, int mrb=0);

    void setZoomW(int on);

    void setVscroll(int v);
    void setHscroll(int v);

    int Vscroll() { return verticalScrollBar()  ->value(); }
    int Hscroll() { return horizontalScrollBar()->value(); }


signals:
  void zoomChanged(double zx, double zy, int x,  int y);
  void zoomW      (QRect r);
  void mouseEvent (QMouseEvent* event);
  void keyEvent   (QKeyEvent   *event);

private slots:

  void on_vScroll(int value);
  void on_hScroll(int value);


};

#endif // MYSCROLLAREA_H
