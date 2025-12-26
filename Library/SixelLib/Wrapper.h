#ifndef __SIXEL_WRAPPER_H__
#define __SIXEL_WRAPPER_H__

#include <Base.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PrintLib.h>
#include <Library/SortLib.h>
#include <Library/DebugLib.h>

#define INT_MAX       0x7FFFFFFF
#define INT_MIN       (-INT_MAX-1)
#define UINT_MAX      0xFFFFFFFF
#define SHRT_MAX      0x7FFF
#define SHRT_MIN      (-SHRT_MAX-1)

#define MAX_STRING_SIZE  0x1000

typedef INT8    int8_t;
typedef UINT8   uint8_t;
typedef INT16   int16_t;
typedef UINT16  uint16_t;
typedef INT32   int32_t;
typedef UINT32  uint32_t;
typedef INT64   int64_t;
typedef UINT64  uint64_t;
typedef INTN    intmax_t;
typedef UINTN   uintmax_t;
typedef INTN    intptr_t;
typedef UINTN   uintptr_t;
typedef UINTN   size_t;

typedef INT64   time_t;

struct timespec
{
    time_t tv_sec;  // Seconds - >= 0
    long   tv_nsec; // Nanoseconds - [0, 999999999]
};


#define memcpy(dest, source, count)       CopyMem(dest,source,(UINTN)(count))
#define memset(dest, ch, count)           SetMem(dest,(UINTN)(count),(UINT8)(ch))
#define memcmp(buf1, buf2, count)         (int)(CompareMem(buf1,buf2,(UINTN)(count)))
#define memmove(dest, source, count)      CopyMem(dest,source,(UINTN)(count))
#define sprintf(buf, ...)                 AsciiSPrint(buf,MAX_STRING_SIZE,__VA_ARGS__)
#define strcmp(str1,str2)                 AsciiStrCmp(str1,str2)
#define strlen(str)                       (size_t)(AsciiStrnLenS(str,MAX_STRING_SIZE))
#define strncmp(string1, string2, count)  (int)(AsciiStrnCmp(string1,string2,(UINTN)(count)))
#define strstr(s1, s2)                    AsciiStrStr(s1,s2)
#define strcpy(strDest, strSource)        AsciiStrCpyS(strDest,(strlen(strSource)+1),strSource)
#define assert(expression)                ASSERT(expression)
#define atoi(nptr)                        AsciiStrDecimalToUintn(nptr)

#define va_list   VA_LIST
#define va_arg    VA_ARG
#define va_start  VA_START
#define va_end    VA_END

typedef VOID *FILE;

extern int   errno;
extern FILE  *stderr;
extern FILE  *stdin;
extern FILE  *stdout;

#define fprintf(...)

void *
malloc (
  size_t  size
  );

void *
realloc (
  void    *ptr,
  size_t  size
  );

void
free (
  void  *ptr
  );

void           *
calloc     (
  size_t  Num,
  size_t  Size
  );

FILE           *
fopen      (
  const char *,
  const char *
  );

size_t
fread       (
  void *,
  size_t,
  size_t,
  FILE *
  );

size_t
fwrite      (
  const void *,
  size_t,
  size_t,
  FILE *
  );

int
fclose      (
  FILE *
  );

long
strtol      (
  const char *,
  char **,
  int
  );

int
sscanf      (
  const char *,
  const char *,
  ...
  );

char           *
strerror   (
  int
  );

char           *
getenv     (
  const char *
  );

void
qsort       (
  void *,
  size_t,
  size_t,
  int (*)(const void *, const void *)
  );

int
isdigit     (
  int
  );

int
isatty     (
   int file
  );

int
fileno     (
   FILE *stream
  );

int
nanosleep(const struct timespec *req, struct timespec *rem);

#endif
