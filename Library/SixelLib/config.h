
#include "Wrapper.h"

#define HAVE_MEMCPY 1
#define HAVE_MEMMOVE 1
#define HAVE_CALLOC 1

#define HAVE_NANOSLEEP 0  // need impl nanosleep()
// static int
// nanosleep(const struct timespec *req, struct timespec *rem)

#define HAVE_ISATTY 0
