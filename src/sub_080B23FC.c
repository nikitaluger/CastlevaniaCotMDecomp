void setAnimationFrame(s32, s32, s32, s32);
void sub_080113A8(s32, s32);
void sub_0801165C(void *, s32);
void sub_080C31E0(void *, s32);

/* Per-frame update: refreshes the animator and integrates the object's motion;
 * at script step 0x18 it switches to animation 0x57, and it destroys the
 * object once the status byte reports done (bit 1). */
void sub_080B23FC(void *entity) {
    s32 sprite;
    s32 animState;
    void *work;

    sprite = *(s32 *)((u8 *)entity + 0x38);
    work = *(void **)((u8 *)entity + 0x3C);
    animState = (s32)work + 0x34;
    sub_080113A8(sprite, animState);
    sub_0801165C(work, 0);
    if (*(u8 *)(((*(s16 *)((u8 *)entity + 0x22) * 2) + (u8 *)entity) + 0x19) == 0x18) {
        setAnimationFrame(sprite, animState, 0x57, 0);
    }
    if (2 & *(u8 *)((u8 *)work + 0x34)) {
        sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
    }
}
