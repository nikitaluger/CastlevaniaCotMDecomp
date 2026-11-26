extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 sub_08014A6C(void *, s32, s32, s32);
extern void sub_080284E8(void *);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Set animation 3 on the work state's animator. When work's distance to its
 * patrol target (via sub_08014A6C) is within 0x1000, flip the patrol direction,
 * reverse the target angle by 0x8000, clear this actor's script-action byte and
 * advance the script to step 2. */
void sub_080281F8(void *obj)
{
    void *sprite;
    u8 *work;
    u8 *animState;
    u8 *patrol;

    sprite = *(void **)((u8 *)obj + 0x38);
    work = *(u8 **)((u8 *)obj + 0x3C);
    animState = work + 0x34;
    patrol = work + 0x48;

    setAnimationFrame(sprite, animState, 3, 1);
    if (sub_08014A6C(work, *(s32 *)(patrol + 0x20), 0x1000, 0) == 1) {
        s16 slot;
        s32 *advance;

        sub_080284E8(obj);
        *(s32 *)(patrol + 0x20) = (*(s32 *)(patrol + 0x20) + 0x8000) & 0xFFFF;

        slot = *(s16 *)((u8 *)obj + 0x22);
        *(u8 *)((u8 *)obj + slot * 2 + 0x19) = 0;

        advance = (s32 *)0x08671BD0;
        sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, 2, *advance);
    }
}
