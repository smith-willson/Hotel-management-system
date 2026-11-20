#include "../include/Input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int readLine(const char *prompt, char *buffer, size_t size) {
    if (prompt) { fputs(prompt, stdout); fflush(stdout); }
    if (!fgets(buffer, (int)size, stdin)) return 0;
    size_t n = strlen(buffer);
    if (n && buffer[n-1] == '\n') buffer[n-1] = '\0';
    else { int ch; while ((ch=getchar())!='\n' && ch!=EOF) {} }
    return 1;
}
int readInt(const char *prompt, int *value) {
    char line[64], *end; long v;
    if (!readLine(prompt,line,sizeof line)) return 0;
    v=strtol(line,&end,10);
    while (*end==' ' || *end=='\t') end++;
    if (end==line || *end!='\0' || v < -2147483647L-1 || v > 2147483647L) return 0;
    *value=(int)v; return 1;
}
