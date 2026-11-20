#include "../include/Date.h"
#include <stdio.h>
#include <time.h>
static int parse(const char *s, struct tm *out) {
    int d,m,y; char extra;
    if (sscanf(s,"%2d-%2d-%4d%c",&d,&m,&y,&extra)!=3) return 0;
    if (y<1900 || m<1 || m>12 || d<1 || d>31) return 0;
    *out=(struct tm){0}; out->tm_mday=d; out->tm_mon=m-1; out->tm_year=y-1900; out->tm_isdst=-1;
    time_t t=mktime(out); if (t==(time_t)-1) return 0;
    return out->tm_mday==d && out->tm_mon==m-1 && out->tm_year==y-1900;
}
int calculateStayDays(const char *start,const char *end,int *days) {
    struct tm a,b; if (!parse(start,&a)||!parse(end,&b)) return 0;
    time_t ta=mktime(&a), tb=mktime(&b); if (ta==(time_t)-1||tb==(time_t)-1||tb<=ta) return 0;
    *days=(int)((tb-ta)/86400); return *days>0;
}
