#define REG_DISPCNT (*(vu16 *)0x04000000)
#define REG_DISPSTAT ((vu8 *)0x04000004)
#define REG_BLDCNT (*(vu16 *)0x04000050)
#define REG_BLDY (*(vu16 *)0x04000054)
#define SAVED_VIDEO_STATE ((u8 *)0x02021E90)

/* Wait for VBlank, then restore the blend control/window settings from the
 * saved global video state and clear the blend brightness register. */
void sub_080BF50C(void)
{
    vu8 *dispStat = REG_DISPSTAT;
    u8 *savedState;
    u32 stat;
    u32 vblankBit;

    stat = *dispStat;
    vblankBit = stat & 2;
    savedState = SAVED_VIDEO_STATE;
    if (vblankBit == 0) {
        u32 vblankMask = 2;
        do {
            stat = *dispStat;
        } while ((stat & vblankMask) == 0);
    }

    REG_BLDY = 0;
    REG_DISPCNT &= 0xFEFF;
    REG_BLDCNT = *(u16 *)(savedState + 0x1364);
    REG_BLDY = *(u16 *)(savedState + 0x1366);
}
