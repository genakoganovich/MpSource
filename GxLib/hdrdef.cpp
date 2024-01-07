#include "hdrdef.h"

TrHdrsMap TraceHdrsSet;


TrHdrDef::TrHdrDef(QString n, QString d, int f, int p, bool e)
{
    frmt = f;
    pos  = p;
    desc = d;
    name = n;
    edit = e;
}

TrHdrDef::TrHdrDef(QString n, QString d, QString exp)
{
    frmt = -2;
    pos  =  1;
    desc =  d;
    name =  n;
    edit =  true;
//  expr.setExpr(exp);
}


TrHdrDef::TrHdrDef()
{
    frmt = -1;
    pos  =  1;
    edit =  false;
}


QString TrHdrDef::bytesStr()
{
    QString s = "";

    if(frmt>0)
    {
        s.sprintf("%d-%d",pos,pos+frmt-1);
    }
    return s;
}


//---------------------------------------------------------------------------

TrHdrDefList::TrHdrDefList(int type)
{
    Type = type;

    if(type==1) // SEG-Y
    {
        int fmt [] = {0,
                             4,  4,  4,  4,  4,  4,  4,  2,  2,  2,  2,  4,  4,  4,  4,  4,  4,  4,  4,  2,
                             2,  4,  4,  4,  4,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  2,
                             2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
                             2,  2,  2,  2,  2,  2,  2,  2,  2,  4,  4,  4,  4,  4,  2,  2
                            };

        int pos[] = {0,
                            1,  5,  9, 13, 17, 21, 25, 29, 31, 33, 35, 37, 41, 45, 49, 53, 57, 61, 65, 69,
                           71, 73, 77, 81, 85, 89, 91, 93, 95, 97, 99,101,103,105,107,109,111,113,115,117,
                          119,121,123,125,127,129,131,133,135,137,139,141,143,149,151,153,155,157,159,161,
                          163,165,167,169,171,173,175,177,179,181,185,189,193,197,201,203
                           };

        const char* desc[] = {
            "Trace index",                              // 0
            "Trace sequence number within line",        // 1
            "Trace sequence number within reel",        // 2
            "FFID - Original field record number ",     // 3
            "Trace number within field record",         // 4
            "SP - Energy source point number",          // 5
            "CDP ensemble  number ",                    // 6
            "Trace  number",                            // 7
            "Trace identification code",                // 8
            "Number of vertically summed traces",       // 9
            "Number of horizontally stacked traces",    //10
            "Data use ( 1-production, 2-test )",        //11
            "Distance from source point to receiv grp", //12
            "Receiver group elevation",                 //13
            "Surface elevation at source",              //14
            "Source depth below surface",               //15
            "Datum elevation at receiver group",        //16
            "Datum elevation at source",                //17
            "Water depth at source",                    //18
            "Water depth at group",                     //19
            "Scaler to all elevations & depths",        //20
            "Scaler to all coordinates",                //21
            "Source X coordinate",                      //22
            "Source Y coordinate",                      //23
            "Group  X coordinate",                      //24
            "Group  Y coordinate",                      //25
            "Coordinate units (1-lenm/ft 2-secarc)",    //26
            "Weathering velocity",                      //27
            "Subweathering velocity",                   //28
            "Uphole time at source",                    //29
            "Uphole time at group",                     //30
            "Source static correction",                 //31
            "Group  static correction",                 //32
            "Total static applied",                     //33
            "Lag time A",                               //34
            "Lag time B",                               //35
            "Delay Recording time",                     //36
            "Mute time start",                          //37
            "Mute time end",                            //38
            "Number of samples in this trace",          //39
            "Sample interval in ms for this trace",     //40
            "Gain type of field instruments",           //41
            "Instrument gain",                          //42
            "Instrument gain constant",                 //43
            "Correlated (1-yes / 2-no)",                //44
            "Sweep frequency at start",                 //45
            "Sweep frequency at end",                   //46
            "Sweep lenth in ms",                        //47
            "Sweep type 1-lin,2-parabol,2-exp,4-ohter", //48
            "Sweep trace taper length at start in ms",  //49
            "Sweep trace taper length at end   in ms",  //50
            "Taper type 1-lin,2-cos2,3-other",          //51
            "Alias filter frequency, if used",          //52
            "Alias filter slope",                       //53
            "Low cut frequency,  if used ",             //54
            "High cut frequency, if used ",             //55
            "Low cut slope",                            //56
            "High cut slope",                           //57
            "Year data recorded",                       //58
            "Day of year",                              //59
            "Hour of day",                              //60
            "Minute of hour",                           //61
            "Second of minute",                         //62
            "Time basis code 1-local,2-GMT,3-other",    //63
            "Trace weighting factor",                   //64
            "Geophone group number of roll sw pos 1",   //65
            "Geophone group number of trace # 1",       //66
            "Geophone group number of last trace",      //67
            "Gap size (total # of groups dropped)",     //68
            "Overtravel assoc w taper of beg/end line", //69
            "CDP X",                                    //70
            "CDP Y",                                    //71
            "Inline Number",                            //72
            "Clossline Number",                         //73
            "Shot Point Number",                        //74
            "Shot Point Scalar",                        //75
            "Trace value measurement unit"              //76
        };

        const char* name[] = {
            "Trace #",
            "SEQWL",
            "SEQWR",
            "FFID",
            "TRCFLD",
            "SP",
            "CDP",
            "TRCNUM",
            "TRCID",
            "NVST",
            "NHST",
            "DU",
            "DSREG",
            "RGE",
            "SES",
            "SDBS",
            "DERG",
            "DES",
            "WDS",
            "WGD",
            "SAED",
            "SAC",
            "SRCX",
            "SRCY",
            "GRPX",
            "GRPY",
            "UNITS",
            "WVEL",
            "SVEL",
            "UTSRC",
            "UTGRP",
            "SECSCOR",
            "GRPSCOR",
            "TSA",
            "LAGTA",
            "LAGTB",
            "DELRECT",
            "MTSTART",
            "MTEND",
            "NSMP",
            "SI",
            "GTFI",
            "IG",
            "IGC",
            "CORREL",
            "SFSTART",
            "SFEND",
            "SLEN",
            "STYP",
            "SSTRLS",
            "SSTLE",
            "TTYP",
            "AFF",
            "AFS",
            "LOCF",
            "HOCF",
            "LOCS",
            "HICS",
            "YEAR ",
            "DAY",
            "HOUR",
            "MINUTE",
            "SCE",
            "TMBS",
            "TWF",
            "GGNSW",
            "GGN1ST",
            "GGNLST",
            "GAPSZ",
            "OAWT",
            "CDP-X",
            "CDP-Y",
            "INLINE#",
            "XLINE#",
            "SP#",
            "SPS",
            "TVMU"
        };

        int len = sizeof(fmt)/sizeof(int);
        int n;

        Hdrs.clear();

        for(n=0;n<len;n++)
        {
            Hdrs.append(TrHdrDef(name[n],desc[n],fmt[n],pos[n],0));
        }

        for(n=0;n<len;n++) Hidx[Hdrs[n].name]=n;
    }
    else if(type==2) // CST
    {
        int n;

        char s[2048];

        static int fmt [66];
        static int pos[66];

        static QString desc[66];
        static QString name[66];

        fmt [0]=0;
        pos [0]=0;
        desc[0] = "Trace Index";
        name[0] = "Trace #";

        fmt [1]=2;
        pos [1]=5;
        desc[1] = "Shot Point Number";
        name[1] = "SP";

        fmt [2]=4;
        pos [2]=13;
        desc[2] = "CDP Number";
        name[2] = "CDP";

        for(n=3;n<66;n++)
        {
            int i = n-3;
            fmt[n]   = 4;
            pos[n]    = (i)*4+1;
            sprintf(s, "W-%02d",i+1);
            desc[n]   = s;
            name[n]   = s;
        }

        Hdrs.clear();

        for(n=0;n<66;n++)
        {
            Hdrs.append(TrHdrDef(name[n], desc[n], fmt[n],pos[n],false));
        }

        for(n=0;n<66;n++) Hidx[Hdrs[n].name]=n;
    }
}


//---------------------------------------------------------------------------

TrHdrsMap::TrHdrsMap(QObject *parent) :
    QObject(parent)
{
    HdrsList[0] = TrHdrDefList(0); // empty
    HdrsList[1] = TrHdrDefList(1); // SEG-Y / SU
    HdrsList[2] = TrHdrDefList(2); // CST
    cidx=1;
}



