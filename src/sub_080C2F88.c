typedef s32 (*Fn3)(s32, s32, s32);
extern void sub_080C2F50(void);

void sub_080C2F88(s32 arg0, s32 arg1, s32 arg2) {
    u16 cnt;
    u16 buf[0x40];
    u16 *src;
    u16 *dst;
    u8 *dstfp;
    *(vu16 *)0x04000204 = (*(vu16 *)0x04000204 & 0xFFFC) | 3;
    src = (u16 *)&sub_080C2F50;
    src = (u16 *)((u32)src ^ 1);
    dst = buf;
    cnt = (u16)(((u32)&sub_080C2F88 - (u32)&sub_080C2F50) >> 1);
    while (cnt != 0) {
        *dst++ = *src++;
        cnt--;
    }
    dstfp = (u8 *)buf + 1;
    ((Fn3)dstfp)(arg0, arg1, arg2);
}
