/* Draft from identical target sub_0801797C, retargeted and judged independently. */
void setAnimationFrame(void *, void *, s32, s32);
s32 getSpriteFacingSign(void *);
s32 divInt32(s32, s32);
s32 sub_080C31E0(s32, void *);
void sub_080C31E4(void *, void *, s32);

void sub_0801B120(void *arg0) {
    s32 r0_a1;
    u8 *self = (u8 *)arg0;
    u8 *v38 = *(u8 **)(self + 0x38);
    u8 *v3C = *(u8 **)(self + 0x3C);
    u8 *p34 = v3C + 0x34;
    u8 *r5 = v3C + 0x48;
    u32 *t1;
    u32 *t2;
    s32 r0;
    
    s32 p;

    setAnimationFrame(v38, p34, 9, 0);
    if (0x78 - *(s16 *)(r5 + 0x16) > 0x11)
        *(u8 *)(*(u32 *)(r5 + 0x34) + 1) = 5;
    if (getSpriteFacingSign(v38) < 0) {
        p = 0x02025FF0;
        if (*(s32 *)(p + 0x174C) > *(s32 *)(v3C + 8) + (s32)0xFFDC0000)
            *(u16 *)(r5 + 0x16) = 0;
    } else {
        p = 0x02025FF0;
        if (*(s32 *)(p + 0x174C) < *(s32 *)(v3C + 8) + 0x240000)
            *(u16 *)(r5 + 0x16) = 0;
    }
    if (*(u16 *)v3C & 2)
        *(u16 *)(r5 + 0x16) = 0;

    if (*(s32 *)(p + 0x172C) < *(s32 *)(v3C + 0x0C) + (s32)0xFFDC0000) {
        u32 *t2_a1;
        
        *(s32 *)(v3C + 0x14) = (s32)0xFFFF6000;
        do { t2_a1 = (void *) *(s32 *)(r5 + 0x0C); } while (0); r0_a1 = (u32) t2_a1 + (s32)0xFFC80000;
        if (*(s32 *)(v3C + 0x0C) <= r0_a1) {
            *(s32 *)(v3C + 0x0C) = r0_a1;
            *(s32 *)(v3C + 0x14) = 0;
        }
    }
    if (*(s32 *)(p + 0x172C) > *(s32 *)(v3C + 0x0C) + (s32)0xFFE00000) {
        *(s32 *)(v3C + 0x14) = 0xA000;
        r0 = *(s32 *)(r5 + 0x0C);
        if (*(s32 *)(v3C + 0x0C) >= r0) {
            *(s32 *)(v3C + 0x0C) = r0;
            *(s32 *)(v3C + 0x14) = 0;
        }
    }

    if (*(s32 *)(v3C + 0x14) == 0) {
        if (*(s16 *)(r5 + 0x24) > 0x3B)
            *(u16 *)(r5 + 0x24) = 0;
        t1 = (u32 *)0x08671BFC;
        r0 = divInt32((s32)*(s16 *)(r5 + 0x24) << 16, 0x3C);
        r0 = sub_080C31E0(r0, *t1);
        *(s32 *)(r5 + 0x20) = r0 << 1;
        *(u16 *)(r5 + 0x24) = *(u16 *)(r5 + 0x24) + 1;
    }

    r0 = *(u16 *)(r5 + 0x16) - 1;
    r0_a1 = 0;
    *(u16 *)(r5 + 0x16) = r0;
    if ((s16)r0 < 0) {
        u8 *q = *(u8 **)(r5 + 0x30);
        if (q != NULL)
            *(u16 *)(q + 0x5C) |= 2;
        *(s32 *)(r5 + 0x20) = r0_a1;
        *(u16 *)(r5 + 0x24) = r0_a1;
        *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        t2 = (u32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *t2);
    }
}
