extern void *sub_0805FAEC(s32, s32);

struct S_02025FF0 { u8 pad[0x1870]; u32 objPool; };
extern struct S_02025FF0 gMainWorkspace;

/* Allocate object 0x16A and store the integer coordinates derived from two
 * 16.16 fixed-point inputs (rounded toward zero) at +0x4C and +0x54. */
void *sub_0805B2B8(s32 x, s32 y) {
    void *obj;
    s32 rawX, rawY, gridX, gridY;
    obj = sub_0805FAEC(gMainWorkspace.objPool, 0x16A);
    if (obj == NULL)
        return NULL;
    rawX = x;
    if (rawX < 0)
        rawX += 0xFFFF;
    gridX = rawX >> 16;
    *(s16 *)((u8 *)obj + 0x4C) = gridX;
    rawY = y;
    if (rawY < 0)
        rawY += 0xFFFF;
    gridY = rawY >> 16;
    *(s16 *)((u8 *)obj + 0x54) = gridY;
    return obj;
}
