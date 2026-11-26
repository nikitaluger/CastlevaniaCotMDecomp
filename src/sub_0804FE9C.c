extern void setAnimationFrame(s32, void *, s32, s32);
extern void sub_080C31E8(void *, void *, void *, void *);

/* Plays animation 9 on an entity's sprite; when it finishes, clears the current
 * script step's counter and advances the script. */
void sub_0804FE9C(void *entity) {
    u8 *bytes = (u8 *)entity;
    void **scriptStepFn;
    u32 sprite = *(u32 *)(bytes + 0x38);
    u8 *anim = *(u8 **)(bytes + 0x3C) + 0x34;

    setAnimationFrame(sprite, anim, 0x09, 0);
    if (*anim & 2) {
        ((u8 *)(bytes + (*(s16 *)(bytes + 0x22)) * 2))[0x19] = 0;
        scriptStepFn = (void **)0x08671BD0;
        sub_080C31E8(bytes + 0x18, bytes + 0x22, (void *)0, *scriptStepFn);
    }
}
