extern u8 gCameraState[];

/*
 * Resets the map-drawing state: clears the transition flags (+0x145C) and the
 * current map id (+0x1440), clears the map height in tiles (+0x1443), and
 * stages the pending map/mode byte (+0x143C) into +0x1445.
 */
void resetMapRender(void) {
    u16 *mapId;
    u8 *gfx = gCameraState;

    gCameraState[0x145C] = 0;
    mapId = (u16 *)(gfx + 0x1440);
    *mapId = 0;
    gCameraState[0x1443] = 0;
    {
        u8 pending = gfx[0x143C];
        gCameraState[0x1445] = pending;
    }
}
