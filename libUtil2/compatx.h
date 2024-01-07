#ifndef COMPATX_H
#define COMPATX_H


#ifdef _MSC_VER
    #pragma warning( disable : 4267 4100 4068 4244 4267 4305 4068)
#endif

#define _CRT_SECURE_NO_WARNINGS 1

#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
#pragma GCC diagnostic ignored "-Wreserved-id-macro"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
//#pragma GCC diagnostic ignored "-Wunused-parameter"


#endif // COMPATX_H
