s32 setAnimationFrame(s32, s32, s32, s32);
s32 sub_080199B0(void *, s32, s32, s16, s32);
s32 sub_080C31E0(s32, s32);
s32 sub_080C31E4(void *, void *, s32);
s32 sub_080C364C(s32, s32);
s32 sub_080C36E4(s16, s32);
extern u32 gMainObjTimerCallback[];

/* Periodic attack: sweep an angle, spawn a shot every few ticks, then advance state. */
void sub_08017EAC(void *arg0) {
    s32 gfx;
    void *work;
    void *animPtr;
    void *attack;
    void *trigTable;

    gfx = *((s32 *) (((s8 *) arg0) + 0x38));
    work = *((void **) (((s8 *) arg0) + 0x3C));
    animPtr = (void *) ((s8 *) work + 0x34);
    attack = (void *) ((s8 *) work + 0x48);
    setAnimationFrame(gfx, (s32) animPtr, 9, 0);
    if ((s32) *((s16 *) (((s8 *) attack) + 0x24)) > 0x3B) {
        *((s16 *) (((s8 *) attack) + 0x24)) = 0;
    }
    trigTable = (void *) 0x08671BFC;
    *((s32 *) (((s8 *) attack) + 0x20)) = (s32) (sub_080C31E0(sub_080C364C(*((s16 *) (((s8 *) attack) + 0x24)) << 0x10, 0x3C), *((s32 *) trigTable)) * 2);
    *((s16 *) (((s8 *) attack) + 0x24)) = (s16) ((u16) *((s16 *) (((s8 *) attack) + 0x24)) + 1);
    if ((sub_080C36E4(*((s16 *) (((s8 *) attack) + 0x16)), 3) << 0x10) == 0) {
        sub_080199B0(arg0, *((s32 *) (((s8 *) work) + 8)), *((s32 *) (((s8 *) attack) + 0xC)), *((s16 *) (((s8 *) attack) + 0x18)), 8);
        *((s16 *) (((s8 *) attack) + 0x18)) = (s16) ((u16) *((s16 *) (((s8 *) attack) + 0x18)) + 1);
    }
    *((s16 *) (((s8 *) attack) + 0x16)) = (s16) ((u16) *((s16 *) (((s8 *) attack) + 0x16)) + 1);
    if ((s32) *((s16 *) (((s8 *) attack) + 0x18)) > 9) {
        u32 *lit2;
        *((s16 *) (((s8 *) attack) + 0x16)) = 0xB4;
        *((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22)) * 2) + arg0)) + 0x19) = 0;
        lit2 = gMainObjTimerCallback;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *lit2);
    }
}
