struct S { u8 pad[2]; u16 f2; };

void setSpriteFlip(struct S *arg0, s32 arg1) {
    u32 v = arg1 & 0xFFFF;
    if (v != 0x4000 && v != 0xC000) {
        if ((v + 0xFFFFBFFF) <= 0x7FFE)
            arg0->f2 &= 0xFFEF;
        else
            arg0->f2 |= 0x10;
    }
}
