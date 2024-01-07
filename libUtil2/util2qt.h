#ifndef Util2QtH
#define Util2QtH

 #ifdef QT_VERSION

 #include <stdio.h>
 #include <QString>
 #include <QRgb>
 #include <QList>

 int     is_segd_f(QString fname, int& FFID, long long pos = -1);
 int     is_cst_f(QString fname);
 int     is_segy_f(QString     fname, int &s, int &cgg, int &junk);
 int     is_segy_f(QString fname);
 off64_t getfilesize64(QString     fname);
 int     open_q  (QString fn, int flags, int perm=0644);
 FILE*   fopen_q (QString fn, QString ff);
 int     unlink_q(QString fn);

 //---------------------------------------------------------------------------

 bool FileExists(QString Name);
 bool DirExists (QString Name);

 bool RemoveDir(const QString &dirName);

 bool IsDirEmpty(QString path);

 QList<QRgb> MkVPalette(QRgb* colors, int ncolors, double vmin, double vmax, double vinc);

 #endif
#endif
