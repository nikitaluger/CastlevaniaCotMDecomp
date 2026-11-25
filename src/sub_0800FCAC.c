extern u32 D_02025368;
extern u16 D_080CB228[];

/* Configure an object's graphics from the character index in self[0x44]: map the
 * indexed runtime status word to a graphics-set selector, set a flag byte, and
 * install the chosen graphics pointer plus a couple of derived attribute words. */
void sub_0800FCAC(void *arg0) {
    u8 *self = arg0;
    void *obj = *(void **)(self + 0x38);
    u32 statusBase = 0x02025368;
    s32 gfxSel = 0;
    u32 tableOff = 0xEF << 2;
    u32 statusAddrs[4];
    s32 zero;
    s32 mask;
    statusAddrs[0] = statusBase + tableOff;
    statusAddrs[1] = statusBase + tableOff + 2;
    statusAddrs[2] = statusBase + tableOff + 4;
    statusAddrs[3] = statusBase + 0x3C2;
    {
        s8 charIdx = (s8)self[0x44];
        s32 status = *(u16 *)statusAddrs[charIdx];
        switch (status) {
        case 2: gfxSel = 1; break;
        case 0x100: gfxSel = 2; break;
        case 0x200: gfxSel = 3; break;
        }
    }
    {
        volatile u8 *flag = (volatile u8 *)((u8 *)obj + 0x2A);
        s32 bits = *flag;
        s32 newBits = (mask = 0x40, zero = 0, bits | mask);
        *flag = newBits;
    }
    *(u32 *)((u8 *)obj + 0x24) = (D_080CB228[gfxSel] << 3) + 0x086426B4;
    *(u32 *)((u8 *)obj + 0x14) = zero;
    {
        s8 charIdx = (s8)self[0x44];
        *(u32 *)((u8 *)obj + 0x18) = charIdx << 0x14;
    }
}
