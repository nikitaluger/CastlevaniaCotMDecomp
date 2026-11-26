struct S_02025FF0_1870 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0_1870 gMainWorkspace;
extern void *sub_0805FAEC(s32, s32);

/* Spawn a type-0x1D7 child and fill its +0x4C/+0x5C/+0x6C parameter slots. */
void sub_080BE70C(s32 value1, s32 value2, s32 value3)
{
    void *obj = sub_0805FAEC(gMainWorkspace.v, 0x1D7);
    if (obj != 0) {
        *(s32 *)((u8 *)obj + 0x4C) = value1;
        *(s32 *)((u8 *)obj + 0x5C) = value2;
        *(s32 *)((u8 *)obj + 0x6C) = value3;
    }
}
