extern s32 setAnimationFrame(s32, s32, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Reset the entity's motion, play pose 5, then bump the state counter and
 * dispatch the handler selected from the table at 0x08671BB0. */
void sub_08041F1C(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *body;
    u8 *anim;
    u8 *statePtr;
    const u32 *handlerTable;
    u8 zero;
    s32 sprite;

    sprite = *(s32 *)(self + 0x38);
    body = *(u8 **)(self + 0x3C);
    anim = body + 0x34;
    zero = 0;
    *(s32 *)(body + 0x10) = zero;
    *(s32 *)(body + 0x14) = zero;
    setAnimationFrame(sprite, (s32)anim, 5, 0);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    handlerTable = (const u32 *)0x08671BB0;
    statePtr = self + 0x18;
    sub_080C31E4(statePtr, self + 0x22, *handlerTable);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    statePtr += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)statePtr * 4));
}
