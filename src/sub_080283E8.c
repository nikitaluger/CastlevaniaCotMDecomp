s32 setAnimationFrame(s32, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E8(void *, void *, s32, s32);
s32 sub_080C364C(s32, s32);
s32 sub_080C31E0(s32, s32);
s32 sub_0800583C(s32);

/* Decrement the state timer at +0x12; when it expires, clear the current
 * script slot's byte and run its script action with argument 0. */
void sub_080283E8(void *obj) {
    u8 *state = (u8 *)*(void **)((u8 *)obj + 0x3C) + 0x48;
    s32 timer = *(u16 *)(state + 0x12) - 1;
    *(u16 *)(state + 0x12) = timer;
    if ((timer << 16) < 0) {
        s32 slot = *(s16 *)((u8 *)obj + 0x22);
        s32 *litp;
        *(u8 *)((u8 *)obj + slot * 2 + 0x17) = 0;
        litp = (s32 *)0x08671BD8;
        sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, 0, *litp);
    }
}
