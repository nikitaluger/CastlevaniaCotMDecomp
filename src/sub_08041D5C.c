extern s32 stepAnimationTrack(s32, s32);
extern s32 sub_08011EE8(void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Run one step of the entity's movement, merge its collision flags into the
 * motion state, animate the sprite, and when the animation has finished clear
 * the state counter and dispatch the handler from the table at 0x08671BC0. */
void sub_08041D5C(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 sprite;
    u8 *body;
    u8 *motion;
    u8 *anim;
    s32 *handlerTable;

    sprite = *(s32 *)(self + 0x38);
    body = *(u8 **)(self + 0x3C);
    anim = body + 0x34;
    motion = body + 0x48;
    sub_08011EE8(body, 0x16C1, 0);
    *(u16 *)(motion + 2) = *(u16 *)(motion + 2) | *(u16 *)(body + 2);
    stepAnimationTrack(sprite, (s32)anim);
    if (*(u8 *)anim & 2) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        handlerTable = (s32 *)0x08671BC0;
        sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
    }
}
