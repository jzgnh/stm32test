
#include "app.h"

void Error_Handler(void)
{
    log_adds(__FUNCTION__);
}

static char buf[512];
static char *ps = buf;
static char *pe = buf;

void log_addc(char c)
{
	*pe = c;

	if ( pe+1 == ps || (pe+1 == &buf[sizeof(buf)] && ps==0)) {
		*pe = '|';
	}
	else {
		if (&buf[sizeof(buf)] == ++pe)
			pe = buf;
	}
}
void log_adds0(const char *s)
{
	while (*s) log_addc(*s++);
	//log_addc('\n');
}
void log_adds(const char *s)
{
	while (*s) log_addc(*s++);
	log_addc('\n');
}

static int uc = EOF;
int log_getc() {
    int r = EOF;

	if (uc!=EOF) {
		r = uc;
		uc = EOF;
		return r;
	}

    if (pe!=ps) {
        r = *ps++;
        if (ps >= &buf[sizeof(buf)])
            ps = buf;
    }
    return r;
}

int log_ugetc(int c) {
	uc = c;
	return c;
}

void log_data(void *d, int sz)
{
    static const uint8_t digits[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    uint8_t *sdata = (uint8_t*)d;
    for (int i=0;i<sz;++i) {
        log_addc(digits[sdata[i]>>4]);
        log_addc(digits[sdata[i]&0x0f]);
        log_addc(' ');
    }
    log_addc('\n');
}
