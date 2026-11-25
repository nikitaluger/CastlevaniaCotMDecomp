void sub_080C31E0(void *, u32);
void sub_080C31E8(void *, void *, u32, u32);

extern u16 D_03000830[];
extern u32 D_08671BD0;
extern u8 D_02021E90[];
extern u8 D_080C98AF[];

void sub_08005D28(void *arg0) {
    s16 idx = *(s16 *)((u8 *)arg0 + 0x22);
    u8 *entry = (u8 *)((s32)(idx * 2) + (s32)arg0);
    u8 *r4p;
    u32 *pd;

    if (entry[0x19] == 0x10) {
        u32 base = (u32)D_02021E90;
        u16 *q = (u16 *)(base + (0x93 << 5));
        s32 tmp;
        s32 z;
        tmp = 0x2000 | *q;
        z = 0;
        *q = tmp;
        {
            s16 i = *(s16 *)((u8 *)arg0 + 0x22);
            *(u8 *)((u8 *)arg0 + i * 2 + 0x19) = z;
        }
        pd = &D_08671BD0;
        r4p = (u8 *)arg0 + 0x18;
        sub_080C31E8(r4p, (u8 *)arg0 + 0x22, 6, *pd);
        {
            s16 i = *(s16 *)((u8 *)arg0 + 0x22);
            u8 *e2 = (u8 *)((s32)(i * 2) + (s32)arg0);
            e2[0x19] = e2[0x19] + 1;
        }
        {
            s16 i = *(s16 *)((u8 *)arg0 + 0x22);
            u8 b;
            u32 *base2;
            r4p += i * 2;
            b = r4p[0];
            base2 = *(u32 **)((u8 *)arg0 + 0x14);
            sub_080C31E0(arg0, base2[b]);
        }
    } else {
        volatile u16 *dst = D_03000830;
        u8 *tbl = D_080C98AF;
        u8 v = entry[0x19];
        s32 vi = (s32)v - 1;
        u8 c = tbl[vi];
        dst[3] = (u16)((c << 8) | (0x10 - c));
    }
}
