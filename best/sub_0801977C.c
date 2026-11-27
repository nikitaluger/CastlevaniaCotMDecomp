extern s32 sub_080C31E0(s32, s32);
extern u8 gMainWorkspace[];

void sub_0801977C(u8 *self) {
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *ext = work + 0x48;
    s32 result;
    s32 diff;
    u8 *p;
    s32 frac;
    u32 pos;

    *(u32 *)(work + 0x14) = 0;
    *(u32 *)(work + 0x10) = 0;

    diff = *(s32 *)(work + 0xC) - *(s32 *)(*(u32 *)(ext + 0x10) + 8);
    *(u32 *)(work + 0xC) = diff;
    result = *(s32 *)(ext + 4) + (s32)0xFF800000;
    if (diff < result) {
        *(u32 *)(work + 0xC) = *(u32 *)(ext + 4);
        result = sub_080C31E0(*(s32 *)(ext + 0xC), *(s32 *)0x08671BFC);
    }

    p = *(u8 **)(ext + 0x10);
    *(u32 *)(work + 8) = *(u32 *)(work + 0x48) + result * *(s16 *)(p + 6);
    frac = *(s32 *)(p + 8);
    if (frac < 0) {
        frac = (frac + 0x3F) >> 6;
    }
    pos = (*(u32 *)(ext + 0xC) + frac) & 0xFFFF;
    *(u32 *)(ext + 0xC) = pos;
    pos = pos + 0xFFFFC000;
    if ((u32)pos > 0x7FFF) {
        *(u16 *)sprite |= *(u16 *)(gMainWorkspace + 0x18C2);
        *(u32 *)(sprite + 0x1C) = 0x8000000B;
    } else {
        *(u16 *)sprite |= *(u16 *)(gMainWorkspace + 0x18C2);
        *(u32 *)(sprite + 0x1C) = 0x80000009;
    }

    *(u32 *)(self + 0x14) = 0x0866D5F4;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
    {
        s16 idx = *(s16 *)(self + 0x22);
        u8 *slot = (u8 *)((u32)(idx * 2) + (u32)self);
        slot[0x19] = slot[0x19] + 1;
    }
    {
        s16 idx = *(s16 *)(self + 0x22);
        s32 cmdOffset = idx * 2;
        u8 *actionList = self + 0x18;
        u8 cmd = *(u8 *)((u32)actionList + (u32)cmdOffset);
        sub_080C31E0((s32)self, *(s32 *)(*(u32 *)(self + 0x14) + cmd * 4));
    }
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
}
