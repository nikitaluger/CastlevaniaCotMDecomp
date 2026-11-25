extern s32 sub_080C31E0(s32, s32);

static inline u32 andOne(u16 v) { u32 m = 1; m &= v; return m; }

void sub_080AFFE8(u8 *arg0)
{
    u8 *r1base = *(u8 **)(arg0 + 0x3C);
    u8 **r5 = (u8 **)(r1base + 0x48);
    u8 *t28 = *(u8 **)(arg0 + 0x28);
    u8 *t28_38 = *(u8 **)(t28 + 0x38);
    u8 *r8 = *(u8 **)(t28 + 0x3C);
    s32 spv[3];
    s32 var_r1;
    u32 r4val;
    s32 r10v;
    u32 *pd86;
    s32 var_r6, var_r7;
    u32 i;
    u8 **p;

    *(u8 *)(r5[0] + 0x60) = *(u8 *)(arg0 + 0x50);
    *(u8 *)(r5[1] + 0x60) = *(u8 *)(arg0 + 0x50);
    *(u8 *)(r5[2] + 0x60) = *(u8 *)(arg0 + 0x50);
    *(u8 *)(r5[3] + 0x60) = *(u8 *)(arg0 + 0x50);

    var_r1 = (*(u16 *)(t28_38 + 0x02) & 0x10) ? 1 : -1;

    r4val = andOne(*(u16 *)r8);
    r10v = var_r1 * 2;
    pd86 = (u32 *)0x08671BFC;

    i = 0;
    p = r5;
    do {
        u8 *obj = *p;
        *(u8 *)(obj + 0x58) = (u8)var_r1;
        obj = *p;
        p++;
        *(u8 *)(obj + 0x54) = (u8)r4val;
        i++;
    } while (i <= 3);

    spv[0] = *(s32 *)(arg0 + 0x5C);
    spv[1] = *(s32 *)(arg0 + 0x6C) + spv[0];
    spv[2] = *(s32 *)(arg0 + 0x7C) + spv[1];

    if (var_r1 == -1) {
        var_r6 = 0x4100 - spv[0];
        var_r7 = 0x3F00 - spv[1];
    } else {
        var_r6 = spv[0] + 0x3F00;
        var_r7 = spv[1] + 0x4100;
    }

    *(s32 *)(r5[0] + 0x6C) = *(s32 *)(r8 + 0x08) + ((var_r1 << 16) + (r10v << 16));
    *(s32 *)(r5[0] + 0x7C) = *(s32 *)(r8 + 0x0C) + 0xFFFE0000;

    *(s32 *)(r5[1] + 0x6C) = *(s32 *)(r5[0] + 0x6C);
    *(s32 *)(r5[1] + 0x7C) = *(s32 *)(r5[0] + 0x7C);

    *(s32 *)(r5[2] + 0x6C) = *(s32 *)(r5[1] + 0x6C) + ((sub_080C31E0(var_r6 + 0x4000, *pd86) >> 8) * 0xC00);
    *(s32 *)(r5[2] + 0x7C) = *(s32 *)(r5[1] + 0x7C) + ((sub_080C31E0(var_r6, *pd86) >> 8) * 0xC00);

    *(s32 *)(r5[3] + 0x6C) = *(s32 *)(r5[2] + 0x6C) + ((sub_080C31E0(var_r7 + 0x4000, *pd86) >> 8) << 12);
    *(s32 *)(r5[3] + 0x7C) = *(s32 *)(r5[2] + 0x7C) + ((sub_080C31E0(var_r7, *pd86) >> 8) << 12);

    *(s32 *)(r5[1] + 0x8C) = spv[0];
    *(s32 *)(r5[2] + 0x8C) = spv[1];
    *(s32 *)(r5[3] + 0x8C) = spv[2];
}
