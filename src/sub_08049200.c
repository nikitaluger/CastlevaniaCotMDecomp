extern void *sub_0805FAEC(s32 arg0, s32 arg1);
extern s32 sub_080C31E0(s32 arg0, s32 arg1);
extern s32 D_08671BFC;
extern u8 D_02025FF0[];

/* Spawn an object at an angular offset from another object, setting its
 * position and velocity from a direction lookup and copying over a type byte. */
void *sub_08049200(void *arg0, void *arg1, s32 arg2, s32 arg3)
{
    void *newObj;
    s32 cosVal;
    s32 sinVal;
    s32 speedBase;
    u32 base;

    base = (u32)D_02025FF0;
    newObj = sub_0805FAEC(*(s32 *)(base + 0x1870), 0x130);
    if (newObj != 0)
    {
        s32 angle;
        s32 speed;
        s32 *table;
        u8 typeByte;

        table = &D_08671BFC;
        angle = arg2 << 12;
        cosVal = sub_080C31E0(angle + 0x4000, *table) >> 8;
        sinVal = sub_080C31E0(angle, *table) >> 8;
        speedBase = 0x28000;
        if (arg3 != 0)
        {
            speedBase = 0x14000;
        }
        *(s32 *)((u8 *)newObj + 0x4C) = *(s32 *)((u8 *)arg1 + 8) + cosVal * 0xC00;
        *(s32 *)((u8 *)newObj + 0x5C) = *(s32 *)((u8 *)arg1 + 0x0C) + sinVal * 0xC00;
        speed = speedBase >> 8;
        *(s32 *)((u8 *)newObj + 0x6C) = speed * cosVal;
        *(s32 *)((u8 *)newObj + 0x7C) = speed * sinVal;
        *(u8 *)((u8 *)newObj + 0x8C) = (u8)arg3;
        *(u8 *)((u8 *)newObj + 0x90) = (u8)arg2;
        typeByte = *(u8 *)((u8 *)arg0 + 0x4C);
        *(u8 *)((u8 *)newObj + 0x94) = typeByte;
    }
    return newObj;
}
