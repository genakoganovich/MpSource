#ifndef CWP_H
#define CWP_H


#include <string.h>
#include <math.h>
#define _USE_MATH_DEFINES
#include <cmath>


#define NINT(x) ((int)((x)>0.0?(x)+0.5:(x)-0.5))

void mksinc (float d, int lsinc, float sinc[]);
double dsinc (double x);

void stoepf (int n, float  r[], float  g[], float  f[], float  a[]);
void stoepd (int n, double r[], double g[], double f[], double a[]);

void ints8r (int nxin, float dxin, float fxin, float yin[],
    float yinl, float yinr, int nxout, float xout[], float yout[]);

void intt8r (int ntable, float table[][8],
    int nxin, float dxin, float fxin, float yin[], float yinl, float yinr,
    int nxout, float xout[], float yout[]);


typedef struct _complexStruct
{  //complex number
	float r,i;
} complex;

complex cadd (complex a, complex b);
complex csub (complex a, complex b);
complex cmul (complex a, complex b);
complex cdiv (complex a, complex b);
float   rcabs (complex z);
complex cmplx (float re, float im);
complex conjg (complex z);
complex cneg (complex z);
complex cinv (complex z);
complex cwp_csqrt (complex z);
complex cwp_cexp (complex z);
complex crmul (complex a, float x);


void polygonalFilter(float *f, float *amps,
            int npoly, int nfft, float dt, float *filter);

int  npfa (int nmin);
int  npfao (int nmin, int nmax);
int  npfar (int nmin);
int  npfaro (int nmin, int nmax);
void pfacc (int isign, int n, complex z[]);
void pfacr (int isign, int n, complex cz[], float rz[]);
void pfarc (int isign, int n, float rz[], complex cz[]);
void pfamcc (int isign, int n, int nt, int k, int kt, complex z[]);
void pfa2cc (int isign, int idim, int n1, int n2, complex z[]);
void pfa2cr (int isign, int idim, int n1, int n2, complex cz[], float rz[]);
void pfa2rc (int isign, int idim, int n1, int n2, float rz[], complex cz[]);

void intlin (int nin, float xin[], float yin[], float yinl, float yinr,
             int nout, float xout[], float yout[]);

void maketz (int nt, float dt, float ft, float v[],
             int nz, float dz, float fz, float t[]);

void maketz2(int nt, float dt, float ft, float v[],
             int nz, float dz, float fz, float t[]);

#define PFA_MAX   720720
#define SU_NFLTS  65535

class CwpFilter
{
public:
    float*   f;      // array of filter frequencies
    int      npoly;  // .... sizes of f and intfr
    float*   filter; // filter array
    float*   amps;   // array of amplitude values
    int      namps;  // .... size of amps
    float    dt;     // sample spacing
    float    nyq;    // nyquist frequency
    int      nt;     // number of points on input trace
    int      nfft;   // number of points for fft trace
    int      nf;        // number of frequencies (incl Nyq)
    float*   rt;    // real trace
    complex* ct;    // complex transformed trace
    char     err[1024];
    int      ok;

    CwpFilter()
    {
        err[0] = 0;
        ok     = 0;
        f      = NULL;
        amps   = NULL;
        filter = NULL;
        rt     = NULL;
        ct     = NULL;
    }

    ~CwpFilter()
    {
        Clear();
    }

    void Clear()
    {
        if(f   ) delete [] f;
        if(amps) delete [] amps;

        if(filter) delete [] filter;
        if(rt    ) delete [] rt;
        if(ct    ) delete [] ct;

        err[0] = 0;
        ok     = 0;
        f      = NULL;
        amps   = NULL;
        filter = NULL;
        rt     = NULL;
        ct     = NULL;
    }

    void Err(const char* ers)
    {
        strncpy(err,ers,1023);
        ok=-1;
    }

    int Init(int Nsmp, float Dt, int Nf, float* F, int Na, float* Amps);

    int Apply(float* Inp, float* Out=NULL);
};


class CwpTimeToDepth
{
public:
    int nt;		// number of time samples
    int it;		// counter
    int nz;		// numer of depth samples

    float dt;	// time sampling interval
    float ft;	// first time value
    float dz;	// depth sampling interval for velocities
    float fz;	// first depth value
    float t;	// timevalues for velocities
    float vmin;	// minimum velocity
    float vmax;	// maximum velocity

    float *vt;		// v(t) velocity as a function of t
    float *tz;		// t(z) time as a function of z
//  float *temp;	// temporary storage array

    char     err[1024];
    int      ok;

    CwpTimeToDepth()
    {
        err[0] = 0;
        ok     = 0;

        vt=NULL;
        tz=NULL;
    }

    ~CwpTimeToDepth()
    {
        Clear();
    }

    void Clear()
    {
        err[0] = 0;
        ok     = 0;

        if(vt)   delete [] vt;
        if(tz)   delete [] tz;

        vt   = NULL;
        tz   = NULL;
    }

    void Err(const char* ers)
    {
        strncpy(err,ers,1023);
        ok=-1;
    }

//  int Init();

    int Exec(int Nsmp, float Dt, int Nv, float* V, float* T, float Dz, float* Ttr, float* Dtr);
};

//void suttoz();


#endif // CWP_H
