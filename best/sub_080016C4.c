extern void sub_08000BE8(void *);

void sub_080016C4(u8 *arg0, u32 arg1)
{
    u8 *p = arg0;
    u32 mask = (u32)(0x10000 << arg1) >> 16;
    u16 val = *(u16 *)(p + 0x34);
    if (mask & val) {
        u16 nv = val & ~mask;
        s32 zero = 0;
        u32 off;
        *(u16 *)(p + 0x34) = nv;
        off = arg1 << 4;
        p += 0x3C;
        p += off;
        sub_08000BE8(*(void **)p);
        *(u32 *)p = zero;
    }
}
