
#include <stdlib.h>
#include <string.h>

typedef _ssize_t ssize_t;

#include "mcuconfig.h"

#include "arm/semihosting.h"

#define OS_INTEGER_TRACE_TMP_ARRAY_SIZE  (16)

static ssize_t
_trace_write_semihosting_debug (const char* buf, size_t nbyte)
{
  // Since the single character debug channel is quite slow, try to
  // optimise and send a null terminated string, if possible.
  if (buf[nbyte] == '\0')
    {
      // send string
      call_host (SEMIHOSTING_SYS_WRITE0, (void*) buf);
    }
  else
    {
      // If not, use a local buffer to speed things up
      char tmp[OS_INTEGER_TRACE_TMP_ARRAY_SIZE];
      size_t togo = nbyte;
      while (togo > 0)
        {
          unsigned int n = ((togo < sizeof(tmp)) ? togo : sizeof(tmp));
          unsigned int i = 0;
          for (; i < n; ++i, ++buf)
            {
              tmp[i] = *buf;
            }
          tmp[i] = '\0';

          call_host (SEMIHOSTING_SYS_WRITE0, (void*) tmp);

          togo -= n;
        }
    }

  // All bytes written
  return (ssize_t) nbyte;
}

int
trace_putc(int c)
{
  return _trace_write_semihosting_debug((const char*)&c, 1);
}

int
trace_puts(const char *s)
{
  _trace_write_semihosting_debug(s, strlen(s));
  return _trace_write_semihosting_debug("\n", 1);
}
