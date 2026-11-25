typedef s32 (*Fn3)(s32, s32, s32);
void sub_080C30B8(void);

s32 sub_080C3100(s32 arg0, s32 arg1, s32 arg2)
{
    u16 count;
    u16 buf[0x60];
    u16 *src;
    u16 *dst;
    u8 *dstfp;

    *(vu16 *)0x04000204 = (*(vu16 *)0x04000204 & 0xFFFC) | 3;

    src = (u16 *)&sub_080C30B8;
    src = (u16 *)((u32)src ^ 1);
    dst = buf;
    count = (u16)(((u32)&sub_080C3100 - (u32)&sub_080C30B8) >> 1);

    while (count != 0) {
        *dst++ = *src++;
        count--;
    }

    dstfp = (u8 *)buf + 1;
    return ((Fn3)dstfp)(arg0, arg1, arg2);
}
