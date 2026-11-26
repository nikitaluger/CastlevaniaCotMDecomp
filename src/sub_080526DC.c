void setAnimationFrame(void *, void *, s32, s32);
void sub_080148D8(void *, void *);
void sub_080C31E4(void *, void *, u32);

/* Action step: keep the parent facing the motion object, and on the 30th tick
 * play animation 5, clear the two action bytes, and advance the script. */
void sub_080526DC(void *arg0) {
    void *parent;
    void *motion;
    u8 *anim;
    u32 *callback;
    parent = *(void **)((u8 *)arg0 + 0x38);
    motion = *(void **)((u8 *)arg0 + 0x3C);
    anim = (u8 *)motion + 0x34;
    sub_080148D8(parent, *(void **)((u8 *)motion + 8));
    if (*(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0) + 0x19) == 0x1E) {
        setAnimationFrame(parent, anim, 5, 0);
        *(u8 *)((u8 *)arg0 + 0x6C) = 0;
        *(u8 *)((u8 *)arg0 + 0x70) = 0;
        *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0) + 0x19) = 0;
        callback = (u32 *)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *callback);
    }
}
