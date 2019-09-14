#ifndef _JMALLOC1_H
#define _JMALLOC1_H

#ifdef __cplusplus
extern "C" {
#endif

void *jmalloc2(unsigned int size);
void *calloc(unsigned int nmemb, unsigned int size);
void *realloc(void *ptr, unsigned int size);
void free(void *ptr);

#ifdef __cplusplus
}  /* extern C */
#endif

#endif