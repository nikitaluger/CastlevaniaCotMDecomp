s32 setAnimationFrame(s32 obj, void *anim, s32 frame, s32 mode);
void sub_080C31E0(void *, s32);

/* Start animation frame 0x16 on the entity's sub-object animation state and,
 * when the state's bit 1 is set afterwards, run the entity's +0x24 callback. */
void sub_0802A728(void *entity)
{
    s32 obj;
    void *anim;
    int off;
    void *state;

    obj = *(s32 *)((u8 *)entity + 0x38);
    anim = *(void **)((u8 *)entity + 0x3C);
    off = 0x34;
    setAnimationFrame(obj, anim + off, 0x16, 0);
    state = anim;
    if (2 & *(u8 *)((u8 *)state + 0x34)) {
        sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
    }
}
