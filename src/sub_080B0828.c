struct S_02025FF0_1870 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0_1870 D_02025FF0;
extern void *sub_0805FAEC(void *, s32);
extern void sub_080C31E0(void *, s32);

void sub_080B074C(s32 arg0, s32 arg1)
{
    void *r = sub_0805FAEC((void *)D_02025FF0.v, 0x1AA);
    if (r != 0) {
        *(s32 *)((u8 *)r + 0x4C) = arg0;
        *(s32 *)((u8 *)r + 0x5C) = arg1;
    }
}

void sub_080B07EC(void)
{
    void *r2 = *(void **)((u8 *)(void *)D_02025FF0.v + 0x30);
    while (r2 != 0) {
        if (*(s16 *)r2 == 0x1AA) {
            u16 *p = *(u16 **)((u8 *)r2 + 0x3C);
            *p |= 1;
        }
        r2 = *(void **)((u8 *)r2 + 0x2C);
    }
}

/* Spawn a type-0x1AB child, storing two word parameters and a byte flag. */
void sub_080B0828(s32 value1, s32 value2, u8 flag)
{
    void *obj = sub_0805FAEC((void *)D_02025FF0.v, 0x1AB);
    if (obj != 0) {
        *(s32 *)((u8 *)obj + 0x5C) = value1;
        *(s32 *)((u8 *)obj + 0x6C) = value2;
        *(u8 *)((u8 *)obj + 0x4C) = flag;
    }
}

void sub_080B0860(void)
{
    void *r4 = *(void **)((u8 *)(void *)D_02025FF0.v + 0x30);
    while (r4 != 0) {
        if (*(s16 *)r4 == 0x1AB) {
            sub_080C31E0(r4, *(s32 *)((u8 *)r4 + 0x24));
        }
        r4 = *(void **)((u8 *)r4 + 0x2C);
    }
}
