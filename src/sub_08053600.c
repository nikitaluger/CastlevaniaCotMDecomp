void setAnimationFrame(s32, void *, s32, s32);
void sub_080C31E0(void *, void *);

/* Clear the sub-object's second tile index, play animation frame 0x0C, and on
 * animation end switch the entity to its next script state. */
void sub_08053600(void *entity) {
    s32 sprite = *(s32 *)((u8 *)entity + 0x38);
    u8 *work = *(u8 **)((u8 *)entity + 0x3C);
    u8 *anim = work + 0x34;
    *(u8 *)(*(u8 **)(work + 0x28) + 1) = 0;
    setAnimationFrame(sprite, anim, 0x0C, 0);
    if (2 & *anim) {
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
    }
}
