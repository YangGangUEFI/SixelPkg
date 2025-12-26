
#include "Wrapper.h"


int _fltused = 1;

int  errno  = 0;

FILE  *stderr = NULL;
FILE  *stdin  = NULL;
FILE  *stdout = NULL;


#define SIXELMEM_HEAD_SIGNATURE  SIGNATURE_32('s','m','h','d')

typedef struct {
  UINT32    Signature;
  UINTN     Size;
} SIXELMEM_HEAD;

#define SIXEL_OVERHEAD  sizeof(SIXELMEM_HEAD)


void *
malloc (
  size_t  size
  )
{
  SIXELMEM_HEAD  *PoolHdr;
  UINTN          NewSize;
  VOID           *Data;

  NewSize = (UINTN)(size) + SIXEL_OVERHEAD;

  Data = AllocatePool (NewSize);
  if (Data != NULL) {
    PoolHdr            = (SIXELMEM_HEAD *)Data;
    PoolHdr->Signature = SIXELMEM_HEAD_SIGNATURE;
    PoolHdr->Size      = size;

    return (VOID *)(PoolHdr + 1);
  }

  return NULL;
}

void *
realloc (
  void    *ptr,
  size_t  size
  )
{
  SIXELMEM_HEAD  *OldPoolHdr;
  SIXELMEM_HEAD  *NewPoolHdr;
  UINTN          OldSize;
  UINTN          NewSize;
  VOID           *Data;

  NewSize = (UINTN)size + SIXEL_OVERHEAD;
  Data    = AllocatePool (NewSize);
  if (Data != NULL) {
    NewPoolHdr            = (SIXELMEM_HEAD *)Data;
    NewPoolHdr->Signature = SIXELMEM_HEAD_SIGNATURE;
    NewPoolHdr->Size      = size;
    if (ptr != NULL) {
      OldPoolHdr = (SIXELMEM_HEAD *)ptr - 1;
      ASSERT (OldPoolHdr->Signature == SIXELMEM_HEAD_SIGNATURE);
      OldSize = OldPoolHdr->Size;

      CopyMem ((VOID *)(NewPoolHdr + 1), ptr, MIN (OldSize, size));
      FreePool ((VOID *)OldPoolHdr);
    }

    return (VOID *)(NewPoolHdr + 1);
  }

  return NULL;
}

void
free (
  void  *ptr
  )
{
  VOID           *EvalOnce;
  SIXELMEM_HEAD  *PoolHdr;

  EvalOnce = ptr;
  if (EvalOnce == NULL) {
    return;
  }

  PoolHdr = (SIXELMEM_HEAD *)EvalOnce - 1;
  if (PoolHdr->Signature == SIXELMEM_HEAD_SIGNATURE) {
    FreePool (PoolHdr);
  } else {
    FreePool (EvalOnce);
  }
}

/**
  Allocate and zero-initialize array.
**/
void *
calloc (
  size_t  Num,
  size_t  Size
  )
{
  void    *RetVal;
  size_t  NumSize;

  NumSize = Num * Size;
  RetVal  = NULL;
  if (NumSize != 0) {
    RetVal = malloc (NumSize);
    if ( RetVal != NULL) {
      (VOID)ZeroMem (RetVal, NumSize);
    }
  }

  DEBUG ((DEBUG_POOL, "0x%p = calloc(%d, %d)\n", RetVal, Num, Size));

  return RetVal;
}


int
fclose (
  FILE  *f
  )
{
  return 0;
}

FILE *
fopen (
  const char  *c,
  const char  *m
  )
{
  return NULL;
}

size_t
fread (
  void    *b,
  size_t  c,
  size_t  i,
  FILE    *f
  )
{
  return 0;
}

size_t
fwrite (
  const void  *buffer,
  size_t      size,
  size_t      count,
  FILE        *stream
  )
{
  return 0;
}


long
strtol (
  const char  *nptr,
  char        **endptr,
  int         base
  )
{
  return 0;
}

int
sscanf (
  const char  *buffer,
  const char  *format,
  ...
  )
{
  return 0;
}

char *
strerror (
  int  errnum
  )
{
  return NULL;
}

char *
getenv (
  const char  *varname
  )
{
  return NULL;
}

void
qsort (
  void *base,
  size_t num,
  size_t width,
  int ( *compare )(const void *, const void *)
  )
{
  ASSERT (base    != NULL);
  ASSERT (compare != NULL);

  PerformQuickSort (base, (UINTN)num, (UINTN)width, (SORT_COMPARE)compare);
  return;
}

int
isdigit (
  int  c
  )
{
  return (('0' <= (c)) && ((c) <= '9'));
}

int
isatty     (
   int file
  )
{
  return 0;
}

int
fileno     (
   FILE *stream
  )
{
  return 0;
}
