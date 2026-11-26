void setAnimationFrame(s32, void *, s32, s32);
void sub_080161F0(void);
void sub_080C31E8(void *, void *, s32, s32);

/* Set the work's animation state to 0xB, clamp its coordinate against the
 * target and clear velocity; once the animation flag is set, release the
 * linked object, clear this script slot and dispatch the next callback. */
void sub_0801B27C(void *actor) {
    s32 owner = *(s32 *)((u8 *)actor + 0x38);
    u8 *work = *(u8 **)((u8 *)actor + 0x3C);
    u8 *anim = work + 0x34;
    u8 *target = work + 0x48;
    s32 zero;
    u8 *child;
    void **nextScriptTable;

    setAnimationFrame(owner, anim, 0xB, 0);
    child = *(u8 **)(target + 0x34);
    zero = 0;
    child[1] = zero;
    *(s32 *)(work + 0x14) = 0xA000;
    if (*(s32 *)(work + 0x0C) >= *(s32 *)(target + 0x0C)) {
        *(s32 *)(work + 0x0C) = *(s32 *)(target + 0x0C);
        *(s32 *)(work + 0x14) = zero;
    }
    if (*anim & 2) {
        if (*(s32 *)(work + 0x0C) >= *(s32 *)(target + 0x0C)) {
            *(s32 *)(work + 0x0C) = *(s32 *)(target + 0x0C);
            *(s32 *)(work + 0x14) = zero;
            if (*(u32 *)(target + 0x34) != 0) {
                sub_080161F0();
                *(u32 *)(target + 0x34) = zero;
            }
            ((u8 *)actor + (*(s16 *)((u8 *)actor + 0x22)) * 2)[0x17] = zero;
            nextScriptTable = (void **)0x08671BD8;
            sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, 1, (s32)*nextScriptTable);
        }
    }
}
