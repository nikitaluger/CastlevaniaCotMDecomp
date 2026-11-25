extern void sub_08011460(s32 sprite, void *anim, s32 rate);
extern void sub_0801165C(void *work, s32 delta);
extern void sub_080C31E0(void *obj, s32 handler);

/* Advance the model's animation counters and start frame playback at a fixed
 * rate; when the animator reports completion (bit 2 of its state byte), switch
 * to the object's state handler at +0x24. */
void sub_080A00F4(void *obj) {
    s32 sprite;
    void *animAddr;
    void *work;

    sprite = *(s32 *)((u8 *)obj + 0x38);
    work = *(void **)((u8 *)obj + 0x3C);
    animAddr = work + 0x34;
    sub_0801165C(work, 0);
    sub_08011460(sprite, animAddr, 0x20000);
    if (2 & *(u8 *)((u8 *)work + 0x34)) {
        sub_080C31E0(obj, *(s32 *)((u8 *)obj + 0x24));
    }
}
