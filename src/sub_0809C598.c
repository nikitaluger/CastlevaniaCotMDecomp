void *sub_0805FAEC(void *parent, s32 type);

/* Spawn a type-0x177 object under `parent`, storing its world position (x, y)
 * and angle/value in the three s32 fields at +0x4C/+0x5C/+0x6C.
 * Returns NULL when the spawn budget or the object pool is exhausted. */
void *sub_0809C598(void *parent, s32 x, s32 y, s32 angle)
{
    void *obj = sub_0805FAEC(parent, 0x177);
    if (obj == 0)
        return 0;
    *(s32 *)((u8 *)obj + 0x4C) = x;
    *(s32 *)((u8 *)obj + 0x5C) = y;
    *(s32 *)((u8 *)obj + 0x6C) = angle;
    return obj;
}
