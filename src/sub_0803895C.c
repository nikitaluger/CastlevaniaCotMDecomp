void stepAnimationTrack(void *, void *);
void sub_08011EE8(void *, s32, s32);

/* Refresh the current animation frame of the object at +0x38 using the state
 * at +0x34 of the work structure at +0x3C, then advance that work structure's
 * motion/collision with parameters 0x16C1 and 0xE0<<12. */
void sub_0803895C(void *entity)
{
    void *obj;
    void *work;
    obj = *(void **)((u8 *)entity + 0x38);
    work = *(void **)((u8 *)entity + 0x3C);
    stepAnimationTrack(obj, (u8 *)work + 0x34);
    sub_08011EE8(work, 0x16C1, 0xE0 << 12);
}
