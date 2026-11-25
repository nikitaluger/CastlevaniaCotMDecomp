extern void sub_08003A6C(void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

void sub_0807F588(void *arg0, void *arg1) {
    sub_08003A6C(arg1 + 0x1C, 0, 0x084EBFC4);
    *(u32 *)(0x02025FF0 + 0x14F4) = 0;
    *(u32 *)(0x02025FF0 + 0x14F8) = 0;
    *(u8 *)(arg0 + (s32)*(s16 *)(arg0 + 0x22) * 2 + 0x19) = 0;
    sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 2, *(u32 *)0x08671BD0);
}

void sub_08080468(void) {
}

void sub_080809E8(void) {
}

void sub_080826AC(void) {
}
