extern u8 gCameraState[];
extern u16 D_020279E0[];
void sub_08002D7C(void);
void sub_08061048(void);
void sub_08061084(void);
void sub_080610D0(void);

/* Hide the entity's sprite (OAM mode 2, 4bpp), give its pool slot back to the
 * free counter at 0x020279E0, then destroy the entity and all its children. */
void sub_0805FB5C(void *entity) {
    u16 **pp = (u16 **)((u8*)entity + 0xAC);
    u16 *oamAttr = *pp;
    u16 attr = *oamAttr;
    attr = (attr & 0xFFF6u) | 2u;
    *oamAttr = attr;
    D_020279E0[0] = D_020279E0[0] + 1;
    sub_08002D7C();
}

/* Clear the current map id at +0x1440 of the graphics workspace and report
 * success (1) to the map-command interpreter. */
s32 sub_0806000C(void) {
    u8 *gfxState = gCameraState;
    *(u16*)(gfxState + 0x1440) = 0;
    return 1;
}

/* Per-frame palette update: apply the current grey level, step the palette
 * fade while its flag (+0x145C bit 3) is set, and tick the timer at +0x1454. */
s32 sub_08060020(void) {
    u8 *gfxState = gCameraState;
    sub_08061048();
    if (gfxState[0x145C] & 8) {
        sub_080610D0();
        sub_08061084();
    }
    *(u32*)(gfxState + 0x1454) = *(u32*)(gfxState + 0x1454) + 1;
    return 0;
}

/* Rewind both tile/name-table write cursors (+0x1448, +0x144C) to the buffer
 * start at +0x1450, clear the row counter at +0x1443 and tick the timer. */
s32 sub_0806032C(void) {
    u8 *gfxState = gCameraState;
    u32 v = *(u32*)(gfxState + 0x1450);
    *(u32*)(gfxState + 0x1448) = v;
    *(u32*)(gfxState + 0x144C) = v;
    gfxState[0x1443] = 0;
    *(u32*)(gfxState + 0x1454) = *(u32*)(gfxState + 0x1454) + 1;
    return 0;
}
