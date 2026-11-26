struct S_02025FF0_1870 { u8 _0x000[0x1870]; u32 obj; };
extern struct S_02025FF0_1870 gMainWorkspace;
extern void *sub_0805FAEC(void *, s32);
extern void sub_080C31E0(void *, s32);

/* Find the entity of type 0x1AA and store two values in its fields +0x4C/+0x5C. */
void sub_080B074C(s32 value_4C, s32 value_5C)
{
    void *ent = sub_0805FAEC((void *)gMainWorkspace.obj, 0x1AA);
    if (ent != 0) {
        *(s32 *)((u8 *)ent + 0x4C) = value_4C;
        *(s32 *)((u8 *)ent + 0x5C) = value_5C;
    }
}

/* Walk the entity list at obj+0x30 and flag (set bit 0 of +0x3C u16) every 0x1AA. */
void sub_080B07EC(void)
{
    void *ent = *(void **)((u8 *)(void *)gMainWorkspace.obj + 0x30);
    while (ent != 0) {
        if (*(s16 *)ent == 0x1AA) {
            u16 *flags = *(u16 **)((u8 *)ent + 0x3C);
            *flags |= 1;
        }
        ent = *(void **)((u8 *)ent + 0x2C);
    }
}

/* Find the entity of type 0x1AB and store its fields +0x5C/+0x6C/+0x4C. */
void sub_080B0828(s32 value_5C, s32 value_6C, u8 value_4C)
{
    void *ent = sub_0805FAEC((void *)gMainWorkspace.obj, 0x1AB);
    if (ent != 0) {
        *(s32 *)((u8 *)ent + 0x5C) = value_5C;
        *(s32 *)((u8 *)ent + 0x6C) = value_6C;
        *(u8 *)((u8 *)ent + 0x4C) = value_4C;
    }
}

/* Walk the entity list at obj+0x30 and update every 0x1AB entry via sub_080C31E0. */
void sub_080B0860(void)
{
    void *ent = *(void **)((u8 *)(void *)gMainWorkspace.obj + 0x30);
    while (ent != 0) {
        if (*(s16 *)ent == 0x1AB) {
            sub_080C31E0(ent, *(s32 *)((u8 *)ent + 0x24));
        }
        ent = *(void **)((u8 *)ent + 0x2C);
    }
}
