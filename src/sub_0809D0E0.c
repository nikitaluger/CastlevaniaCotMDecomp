void sub_080114DC(s32, s32, s32, s32);
void sub_0809E278(s32, s32, void *, s32);
void sub_080C31E4(void *, void *, s32);

/* Actor step: start animation 5 on the animator and advance its wave script;
 * when the animator's "finished" flag (bit 1) is set, clear the current script
 * step and dispatch the actor's script handler. */
void sub_0809D0E0(void *actor) {
    u8 *self = (u8 *)actor;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *anim = work + 0x34;
    u8 *body = work + 0x48;
    sub_080114DC(sprite, (s32)anim, 5, 0);
    sub_0809E278(sprite, (s32)anim, work, (s32)body);
    if (*anim & 2) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *handlerTable = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
        }
    }
}
