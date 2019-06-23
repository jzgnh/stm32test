

#include "app.h"

#include <assert.h>

typedef
struct {
    int mode;
    SPI_TypeDef *inst;
} SPIInst, *spictx;

static int _spi_init(spictx ctx, int mode);
static void _spi_deinit(spictx ctx);

static void _spi_cs(spictx ctx, int sel);
static int _spi_busy(spictx ctx);
static int _spi_write(spictx ctx, int b);
static int _spi_read(spictx ctx);
static int _spi_canread(spictx ctx);
static int _spi_canwrite(spictx ctx);



#define DEFIN_SPI_BUS(var,inst)                                             \
    static SPIInst Inst_##inst = { SPIBUS_MODE_NONE, inst};                 \
                                                                            \
    static int _##var##_init(int mode)                                      \
    { __HAL_RCC_##inst##_CLK_ENABLE();                                      \
      return _spi_init(&Inst_##inst,mode); }                                \
    static void _##var##_deinit() { _spi_deinit(&Inst_##inst); }            \
    static void _##var##_cs(int sel) { _spi_cs(&Inst_##inst,sel); }         \
    static int _##var##_busy() { return _spi_busy(&Inst_##inst); }          \
    static int _##var##_write(int b)                                        \
    { return _spi_write(&Inst_##inst, b); }                                 \
    static int _##var##_read()                                              \
    { return _spi_read(&Inst_##inst); }                                     \
    static int _##var##_canread() { return _spi_canread(&Inst_##inst); }    \
    static int _##var##_canwrite() { return _spi_canwrite(&Inst_##inst); }  \
                                                                            \
    static const SPIBUS _real_##var##_instance = {                          \
                                _##var##_init, _##var##_deinit,             \
                                _##var##_cs, _##var##_busy,                 \
                                _##var##_write, _##var##_read,              \
                                _##var##_canread, _##var##_canwrite   };    \
    SPIBUS const *const var = &_real_##var##_instance


DEFIN_SPI_BUS(bus_spi1, SPI1);
DEFIN_SPI_BUS(bus_spi2, SPI2);
//DEFIN_SPI_BUS(bus_spi3, SPI3);


////////////////////////////////////////////////////////////////////
__weak
extern void LL_MSP_init(SPI_TypeDef *SPIx)
{ }

static int _spi_init(spictx ctx, int mode)
{
    LL_SPI_InitTypeDef SPI_Init = {0};

    if (mode!=SPIBUS_MODE_MFRC522)
        return BUS_NOIMPL;

    assert(ctx->mode==SPIBUS_MODE_NONE);

    SPI_Init.TransferDirection = LL_SPI_FULL_DUPLEX;
    SPI_Init.Mode = LL_SPI_MODE_MASTER;
    SPI_Init.DataWidth = LL_SPI_DATAWIDTH_8BIT;
    SPI_Init.ClockPolarity = LL_SPI_POLARITY_LOW; /* ?????????? */
    SPI_Init.ClockPhase = LL_SPI_PHASE_1EDGE;
    SPI_Init.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV32;
    SPI_Init.BitOrder = LL_SPI_MSB_FIRST;
    SPI_Init.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;

    SPI_Init.NSS = LL_SPI_NSS_HARD_OUTPUT;

    LL_SPI_Init(ctx->inst, &SPI_Init);
    ctx->mode = mode;

    LL_MSP_init(ctx->inst);
    return BUS_OK;
}
static void _spi_deinit(spictx ctx)
{
    LL_SPI_DeInit(ctx->inst);
    ctx->mode = SPIBUS_MODE_NONE;
}

static void _spi_cs(spictx ctx, int sel)
{
    assert(ctx->mode!=SPIBUS_MODE_NONE);

    if (sel) LL_SPI_Enable(ctx->inst);
    else LL_SPI_Disable(ctx->inst);
}

static int _spi_busy(spictx ctx)
{
    assert(ctx->mode!=SPIBUS_MODE_NONE);
    return LL_SPI_IsActiveFlag_BSY(ctx->inst);
}

static int _spi_write(spictx ctx, int b)
{
    assert(ctx->mode!=SPIBUS_MODE_NONE);

    if (ctx->mode >= SPIBUS_MOD_DATA16)
        LL_SPI_TransmitData16(ctx->inst, (uint16_t)b);
    else
        LL_SPI_TransmitData8(ctx->inst, (uint8_t)b);
    return BUS_OK;
}

static int _spi_read(spictx ctx)
{
    assert(ctx->mode!=SPIBUS_MODE_NONE);

    if (ctx->mode >= SPIBUS_MOD_DATA16)
        return LL_SPI_ReceiveData16(ctx->inst);

    return LL_SPI_ReceiveData8(ctx->inst);
}

static int _spi_canread(spictx ctx)
{
    assert(ctx->mode!=SPIBUS_MODE_NONE);
    return LL_SPI_IsActiveFlag_RXNE(ctx->inst);
}

static int _spi_canwrite(spictx ctx)
{
    assert(ctx->mode!=SPIBUS_MODE_NONE);
    return LL_SPI_IsActiveFlag_TXE(ctx->inst);
}

