
#include "mcuconfig.h"

typedef
struct {
    unsigned char y;
    unsigned char m;
    unsigned char d;


    unsigned char H;
    unsigned char M;
    unsigned char S;

    unsigned char w;    // day of week, 01-07, 00 for unsupport
} TS_DATATypeDef;


void DS_Init();
void DS_DeInit();

void DS_Get(TS_DATATypeDef *);
void DS_Set(TS_DATATypeDef *);

