extern s32 sub_08005820(s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 sub_08014990(void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s32 D_08671BD0;

/* Decrements a timer; on expiry, nudges the facing flag toward the target X
 * and restarts the timer with a random delay before firing a script event. */
void sub_0803F170(void *arg0) {
    void *mainObj;
    u8 *state;
    u8 *anim;
    u8 *target;
    void *unused = arg0;
    s32 remaining;
    s32 *lit;
    u8 zero;
    s32 delay;
    mainObj = *((void **)((u8 *)arg0 + 0x38));
    state = *((u8 **)((u8 *)arg0 + 0x3C));
    anim = state + 0x34;
    target = state + 0x48;
    setAnimationFrame(mainObj, anim, 7, 0);
    remaining = (*(u16 *)(target + 0x0E)) - 1;
    *(u16 *)(target + 0x0E) = (u16)remaining;
    if ((s32)((u16)remaining << 16) < 0) {
        if (sub_08014990(mainObj) < 0) {
            if (*(s32 *)(state + 0x08) < (*(s32 *)(state + 0x48) + (s32)0xFFE00000)) {
                *(u16 *)((u8 *)mainObj + 2) = *(u16 *)((u8 *)mainObj + 2) | 0x10;
            }
        } else if (*(s32 *)(state + 0x08) > (*(s32 *)(state + 0x48) + 0x200000)) {
            *(u16 *)((u8 *)mainObj + 2) = *(u16 *)((u8 *)mainObj + 2) & 0xFFEF;
        }
        delay = sub_08005820(0x3D) + 0x78;
        zero = 0;
        *(u16 *)(target + 0x0E) = (u16)delay;
        *(((u8 *)arg0) + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = zero;
        lit = &D_08671BD0;
        sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 0, *lit);
    }
}
