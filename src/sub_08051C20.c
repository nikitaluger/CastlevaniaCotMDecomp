extern void setAnimationFrame(s32 sprite, s32 anim, s32 animId, s32 arg3);
extern void stepAnimationTrack(s32 sprite, s32 anim);
extern void sub_080C31E0(void *obj, s32 arg1);

/* Play animation 0x1A on the actor's model and update its animation frame;
 * when the animator reports completion (bit 2 of the state byte), switch to
 * the object's state handler at +0x24. */
void sub_08051C20(void *obj) {
    s32 animAddr;
    s32 sprite;
    void *work;

    sprite = *(s32 *)((u8 *)obj + 0x38);
    work = *(void **)((u8 *)obj + 0x3C);
    animAddr = work + 0x34;
    setAnimationFrame(sprite, animAddr, 0x1A, 0);
    stepAnimationTrack(sprite, animAddr);
    if (2 & *(u8 *)((u8 *)work + 0x34)) {
        sub_080C31E0(obj, *(s32 *)((u8 *)obj + 0x24));
    }
}
