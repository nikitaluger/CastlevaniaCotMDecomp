extern void *sub_0805FAEC(s32, s32);

struct ObjectPool { u8 _p[0x1870]; u32 pool; };
extern struct ObjectPool D_02025FF0;

/* Spawn an object of type 0xAB from the global pool and initialize it: x/y
 * come from two 16.16 fixed-point values, plus a flag and two extra fields. */
void *sub_08025A8C(s32 xFixed, s32 yFixed, u16 flag, s32 value6C, u16 value7C) {
    void *object;
    s32 xVal, yVal;
    s32 xInt, yInt;
    object = sub_0805FAEC(D_02025FF0.pool, 0xAB);
    if (object == 0) return 0;
    xVal = xFixed;
    if (xVal < 0) xVal += 0xFFFF;
    xInt = xVal >> 16;
    *(s16 *)((u8 *)object + 0x4C) = xInt;
    yVal = yFixed;
    if (yVal < 0) yVal += 0xFFFF;
    yInt = yVal >> 16;
    *(s16 *)((u8 *)object + 0x54) = yInt;
    *(u16 *)((u8 *)object + 0x5C) = flag;
    *(s32 *)((u8 *)object + 0x6C) = value6C;
    *(u16 *)((u8 *)object + 0x7C) = value7C;
    return object;
}
