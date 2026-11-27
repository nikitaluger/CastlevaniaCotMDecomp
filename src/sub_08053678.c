struct S_02025FF0 { u8 _p[0x1870]; u32 v; };
extern struct S_02025FF0 gMainWorkspace;
void *spawnBudgetedEffect(u32, s32);
s32 divideInt(s32, s32);

/* Creates a type-0x14B object under the global parent, converting its 16.16
 * fixed-point x/y into s16 position fields. */
void *sub_08053678(s32 xFixed, s32 yFixed) {
    void *obj;
    s32 xVal, yVal;
    s32 xPos, yPos;
    obj = spawnBudgetedEffect(gMainWorkspace.v, 0x14B);
    if (obj == NULL) return NULL;
    xVal = xFixed;
    if (xVal < 0) xVal += 0xFFFF;
    xPos = xVal >> 16;
    *(s16 *)((u8 *)obj + 0x4C) = xPos;
    yVal = yFixed;
    if (yVal < 0) yVal += 0xFFFF;
    yPos = yVal >> 16;
    *(s16 *)((u8 *)obj + 0x54) = yPos;
    return obj;
}
