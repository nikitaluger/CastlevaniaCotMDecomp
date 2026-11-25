struct S_02025FF0_1870 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0_1870 D_02025FF0;
extern void *sub_0805FAEC(void *, s32);

/* Spawn a 0x1AA entity at fixed-point position (x, y): allocate one from the
 * entity pool and store its position. */
void sub_080B074C(s32 x, s32 y)
{
    void *ent = sub_0805FAEC((void *)D_02025FF0.v, 0x1AA);
    if (ent != 0) {
        *(s32 *)((u8 *)ent + 0x4C) = x;
        *(s32 *)((u8 *)ent + 0x5C) = y;
    }
}
