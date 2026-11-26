extern void setObjectAnimation(void *, void *, s32, s32);
extern void sub_080A1894(void *, void *, void *, void *);
extern s32 sub_080A2D30(void *, void *, s32, s32, s32, s32);
extern void sub_080A2D80(s32, s32, s32);
extern s32 sub_080A2D8C(s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

static inline u32 addIndex(u32 index, u32 base)
{
    return index + base;
}

void sub_080A10E0(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *temp_r0 = *(void **)(self + 0x38);
    u8 *temp_r4;
    u8 *temp_r5 = *(u8 **)(self + 0x3C);
    u8 *temp_r1 = temp_r5 + 0x34;
    u32 temp_r6;
    s32 var_r2;
    s32 var_r0;
    u32 f;

    temp_r4 = temp_r5 + 0x48;
    sub_080A1894(temp_r0, temp_r5, temp_r1, temp_r4);
    {
        u32 *tablep = *(u32 **)(temp_r1 + 8);
        u32 index = (u32)(*(s16 *)(temp_r1 + 0xE) + temp_r1[1]);
        u32 table = *tablep;
        u8 *entry = (u8 *)addIndex(index * 4, table);
        entry -= 4;
        temp_r6 = *(u16 *)(entry + 2);
    }
    if (*(u16 *)(temp_r4 + 0x14) != temp_r6) {
        switch (temp_r6) {
        case 9:
            f = *(u16 *)((u8 *)temp_r0 + 2) & 0x10;
            var_r2 = 0x100000;
            if (f) {
                var_r2 = 0xFFF00000;
            }
            var_r0 = sub_080A2D30(arg0, temp_r0, 0, *(s32 *)(temp_r5 + 8) + var_r2, *(s32 *)(temp_r5 + 0xC) + 0xFFD00000, 0);
            *(s32 *)(temp_r4 + 0xC) = var_r0;
            break;
        case 11:
            f = *(u16 *)((u8 *)temp_r0 + 2) & 0x10;
            var_r2 = 0xFFF00000;
            if (f) {
                var_r2 = 0x100000;
            }
            sub_080A2D80(*(s32 *)(temp_r4 + 0xC), *(s32 *)(temp_r5 + 8) + var_r2, *(s32 *)(temp_r5 + 0xC) + 0xFFD00000);
            break;
        case 12:
            sub_080A2D8C(*(s32 *)(temp_r4 + 0xC), 1);
            *(s32 *)(temp_r4 + 0xC) = 0;
            break;
        }
        *(u16 *)(temp_r4 + 0x14) = temp_r6;
    }
    if (temp_r5[0x34] & 2) {
        s32 temp_r2 = *(s32 *)(temp_r5 + 8);
        if (*(u16 *)((u8 *)temp_r0 + 2) & 0x10) {
            *(s32 *)(temp_r5 + 8) = temp_r2 + 0x120000;
        } else {
            *(s32 *)(temp_r5 + 8) = temp_r2 + 0xFFEE0000;
        }
        setObjectAnimation(temp_r0, temp_r1, 0, 0);
        self[(*(s16 *)(self + 0x22)) * 2 + 0x19] = 0;
        {
            s32 *fp = (s32 *)0x08671BD0;
            sub_080C31E8(self + 0x18, self + 0x22, 4, *fp);
        }
    }
}
