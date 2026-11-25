extern u8 D_02021E90[];

/*
 * Resets the map-drawing state: clears the transition flags (+0x145C) and the
 * current map id (+0x1440), clears the map height in tiles (+0x1443), and
 * stages the pending map/mode byte (+0x143C) into +0x1445.
 */
void sub_0805FDF0(void) {
    u16 *mapId;
    u8 *gfx = D_02021E90;

    D_02021E90[0x145C] = 0;
    mapId = (u16 *)(gfx + 0x1440);
    *mapId = 0;
    D_02021E90[0x1443] = 0;
    {
        u8 pending = gfx[0x143C];
        D_02021E90[0x1445] = pending;
    }
}
