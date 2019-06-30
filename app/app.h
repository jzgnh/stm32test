
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



/**********************************************/
/** SPI Driver **/

#define BUS_OK          0
#define BUS_BUSY        1
#define BUS_NOIMPL      2
#define BUS_BADSTATE    3

enum {
    SPIBUS_MODE_NONE    = 0,

    SPIBUS_MOD_DATA8    = 0,

    SPIBUS_MODE_MFRC522,

    SPIBUS_MOD_DATA16    = 64,
};

typedef
struct {
    int  (*init)(int mode);
    void (*deinit)();

    void (*cs)(int sel);

    int (*busy)();

    int (*write)(int b);
    int (*read)();

    int (*canread)();
    int (*canwrite)();

} SPIBUS;

extern SPIBUS const *const bus_spi1;
extern SPIBUS const *const bus_spi2;
extern SPIBUS const *const bus_spi3;


static inline int spi_rw(SPIBUS const *bus, int w) {
    while(!bus_spi1->canwrite())
        continue;
    bus_spi1->write(w);

    while(!bus_spi1->canread())
        continue;

    return bus_spi1->read();
}


/**********************************************/
/** USB Driver **/

void USBInit();

int USBIsReadey();
