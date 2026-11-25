struct ScanlineState {
    u8 _0[0x1361];
    u8 mode;
    u8 _1362[6];
    u8 offset;
    u8 kind;
};

/* Waits for VBlank, then sets up the GBA window and blend registers and the
 * scanline (VCOUNT) compare value used for the raster effect, taking the kind
 * and offset from the shared state at 0x02021E90.
 */
void sub_080BF454(void)
{
    struct ScanlineState *state = (struct ScanlineState *)0x02021E90;
    u32 vblankFlag;
    struct ScanlineState *s;
    state->mode = 5;
    vblankFlag = *(vu8 *)0x04000004 & 2;
    s = state;
    if (!vblankFlag)
    {
        vu8 *dispstat = (vu8 *)0x04000004;
        s32 mask = 2;
        while (!(*dispstat & mask)) {}
    }
    *(vu16 *)0x04000050 = 0x20FE;
    *(vu16 *)0x04000000 |= 0x100;
    *(vu16 *)0x04000054 = 6;
    switch (s->kind)
    {
    case 0:
    case 0x50:
        *(vu8 *)0x04000005 = s->kind + 0x29 + s->offset - 1;
        break;
    case 0x48:
        *(vu8 *)0x04000005 = s->offset + 0x50;
        break;
    }
}
