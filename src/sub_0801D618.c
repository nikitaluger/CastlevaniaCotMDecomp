void *sub_0805FAEC(s32, s32);
struct S_02025FF0 { u8 _p[0x1870]; u32 v; };
extern struct S_02025FF0 D_02025FF0;

/* Creates a type-0x92 object under the global parent, rounding its 16.16 fixed-
 * point x/y into s16 position fields and storing two extra 32-bit parameters. */
void *sub_0801D618(s32 xFixed, s32 yFixed, s32 param0, s32 param1) {
    void *obj;
    s32 xVal, yVal;
    s32 xPos, yPos;
    obj = sub_0805FAEC(D_02025FF0.v, 0x92);
    if (obj == NULL) return NULL;
    xVal = xFixed;
    if (xVal < 0) xVal += 0xFFFF;
    xPos = xVal >> 16;
    *(s16 *)((u8 *)obj + 0x4C) = xPos;
    yVal = yFixed;
    if (yVal < 0) yVal += 0xFFFF;
    yPos = yVal >> 16;
    *(s16 *)((u8 *)obj + 0x54) = yPos;
    *(u32 *)((u8 *)obj + 0x5C) = param0;
    *(u32 *)((u8 *)obj + 0x6C) = param1;
    return obj;
}
