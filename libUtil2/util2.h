//---------------------------------------------------------------------------

#ifndef Util2H
#define Util2H

#include "compatx.h"

#include <stdarg.h>
#include <string>
#include <inttypes.h>

using namespace std;

typedef unsigned char byte;
typedef unsigned int  uns;

#ifdef WIN32

#include "Windows.h"

    char* ConvertTCharToUtf8(const TCHAR* src);
#endif



#ifdef _MSC_VER

   #include <io.h>
   typedef __int64 off64_t;
   #define lseek64 _lseeki64
   #define _USE_MATH_DEFINES
   #include <cmath>

// #include <vld.h>

#else

 #include <unistd.h>

#ifndef O_BINARY
    #define O_BINARY 0x8000
#endif


#endif


#define swapb(x,y) {byte tmp; tmp=(x); (x)=(y); (y)=tmp;}

int isnumeric(char *str);

char* strmem(char* str, char* buf, int blen);

char  hexc (byte* buf, int n);
char* hexs (byte *buf, int n, int count, char* str);

int            i4 (byte* buf, int nbyte, int swap);
unsigned int   ui4(byte* buf, int nbyte, int swap);
int            i3 (byte* buf, int nbyte, int swap);
short          i2 (byte* buf, int nbyte, int swap);
unsigned short ui2(byte* buf, int nbyte, int swap);
char           i1 (byte* buf, int nbyte);

void si4(byte* buf, int nbyte, int i, int swap);
void si2(byte* buf,int nbyte, short i, int swap);


double iFmt(int frmt, byte* buf, int nbyte, int swap);
void   sFmt(int frmt, byte *buf, int nbyte, double v, int swap);

char* strncpy1(void *d, void *s, int n);
char* memstr(char* mem, int maxl, char* str);


void swap2(void* x);
void swap4(void* x);
void swap8(void* x);

float ieee_to_ieee   (float x);

float ibm2ieee(float x, int swap);
float ieee2ibm(float x);

void toibm(int *addr, int ll);

float swapf4(float x, int swap = 1);
int   swapi4(int   x, int swap = 1);
short swapi2(short x, int swap = 1);

int ltod_open(char* fname,int write);

int is_ltod(char* inpfn);
int is_ltod(int   inpf);

int ck_ltod(char* inpfn);
int ck_ltod(int inpf, long long p=-1, int *pffid=NULL);

int ltod_read (int inpf, byte *buf, int len=0);
int ltod_write(int outf, byte* buf, int len);
int ltod_nxln (int inpf);

int is_segd_format(int Format);

int is_segd_f(char*   fname, int& FFID, long long pos = -1);
int is_segd_f(int     inpf,  int& FFID, long long pos = -1);

int is_segd_m(byte *buf  , int& FFID);

int is_segy_f(const char *fname, int &s, int &cgg, int &junk);
int is_segy_f(const char* fname);

int is_su_f  (const char* fname, int &s);

int  is_cst_f(const char* fname);
int  is_cst_f(const char *fname, int& cdp1);

bool is_txthdr_ebcdic(char* txt);

//void int2bcd(int v, char* b, int n);

void substr(char* inps, int p, int l, char* outs);

long long find_inf_f(int fd, char* pat, int plen);

off64_t getfilesize64(int fd);
off64_t getfilesize64(const char* fname);
off64_t tell64(int fd);

string Sprintf(const char *fmt,  ...);

char*  Tprintf(const char *fmt,  ...);


unsigned char ebasc(unsigned char ascii);
void          ebasd(unsigned char* ascii, unsigned char* ebcd);
void          ebasdn(char *ascii, char* ebcd, int l);
char          asebc(char ascii);
void          asebd( char* ebcd, char* ascii);
void          asebdn( char* ebcd, char* ascii, int l);

int is_month(byte *mnam);

//---------------------------------------------------------------------------

#define INSIDE  0
#define FIRSTPT 1
#define LASTPT  2

double hypot2(double a, double b);

double VertPtDist(double x1, double y1, double x2, double y2, double ax, double ay);

double VertPtDist( double  x1, double  y1, double x2, double y2,
                   double  ax, double  ay,
                   double& dx, double& dy, int& mode);

bool RectIntersection( int x11, int y11, int x12, int y12,
                       int x21, int y21, int x22, int y22,
                       int& lx, int& tx, int& rx, int& bx);

int PointInRange(double x1, double x2, double x);

//---------------------------------------------------------------------------

void trim(char *s);

void substr(char *dst, char *src, int pos, int len);

double getdbl(char *str, int pos1, int len, int *err);
int    getlng(char *str, int pos1, int len, int *err);

int is_str_empty(char* str);

//---------------------------------------------------------------------------

int gettoken  (int pos, char* str, char *token, int len=-1);
int gettokenap(int pos, char* str, char *token, int len=-1);
int gettokenan(int pos, char* str, char *token, int len=-1);
int gettokennm(int pos, char* str, char *token, int len=-1);

int skipws    (int pos, char* str);
int skipto    (int pos, char* str, char to);
int getto     (int pos, char* str, char to, char* data, int datalen);

//---------------------------------------------------------------------------

int strncmp(void* str1, void* str2, size_t len);

//---------------------------------------------------------------------------


byte               hexc2byte (char hex);
unsigned int       hex2uint  (char* hex);
int                hex2sint  (char* hex);
uint64_t           hex2uint64(char* hex);
int64_t            hex2sint64(char* hex);
char*              hex2ascii (char* hex);
float              hex2flt   (char* hex);
double             hex2dbl   (char* hex);


int   bcd_int_item(byte* buf, int pos, int count);



#endif
