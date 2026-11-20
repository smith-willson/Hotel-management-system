#ifndef INPUT_H
#define INPUT_H
#include <stddef.h>
int readLine(const char *prompt, char *buffer, size_t size);
int readInt(const char *prompt, int *value);
#endif
