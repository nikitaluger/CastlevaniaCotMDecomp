extern void setAnimationFrame(s32, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Play pose 5 with movement stopped; when the animation reports completion,
 * reset the current script step and dispatch the next script handler. */
void sub_0803E3B4(void *arg0) {
    u8 *self = (u8*)arg0;
    s32 sprite = *(s32*)(self + 0x38);
    u8 *body = *(u8**)(self + 0x3C);
    u8 *anim = body + 0x34;
    *(s32*)(body + 0x14) = 0;
    *(s32*)(body + 0x10) = 0;
    setAnimationFrame(sprite, anim, 5, 0);
    if (*(u8*)anim & 2) {
        s32 *handlerTable;
        *(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) = 0;
        handlerTable = (s32*)0x08671BD0;
        sub_080C31E8(self + 0x18, self + 0x22, 0, *handlerTable);
    }
}
