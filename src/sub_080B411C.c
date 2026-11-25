s32 sub_080114DC(s32, s32, s32, s32);
s32 sub_080148D8(s32, s32);
s32 sub_080B7280(s32);
void sub_080C31E4(void *, void *, s32);

/* Entity update: run animation 0x42 and set the gfx flip bit from sub_08014938.
 * When local state reaches 0x1E, switch to animation 0x44, mark the sub-struct
 * at actor+0x48, set a left/right horizontal speed in actor+0x10, clear the
 * related fields and advance to the next state (function at 0x08671BB0). */
void sub_080B411C(void *arg0) {
    u8 *self = arg0;
    u8 *gfx = *(u8 **)(self + 0x38);
    u8 *actor = *(u8 **)(self + 0x3C);
    u8 *anim = actor + 0x34;
    u8 *actorSub = actor + 0x48;
    u8 *stateSlot;
    s32 *funcSlot;
    u8 *stateBase;

    sub_080114DC((s32)gfx, (s32)anim, 0x42, 0);
    sub_080148D8((s32)gfx, *(s32 *)(actor + 8));
    stateSlot = (u8 *)((s32)*(s16 *)(self + 0x22) * 2 + (s32)self);
    if (stateSlot[0x19] == 0x1E) {
        sub_080114DC((s32)gfx, (s32)anim, 0x44, 1);
        sub_080B7280(*(s32 *)(actorSub + 0x10));
        {
            s32 hSpeed = (*(u16 *)(gfx + 2) & 0x10) ? (0x80 << 11) : (s32)0xFFFC0000;
            *(s32 *)(actor + 0x10) = hSpeed;
        }
        *(s32 *)(actor + 0x14) = 0;
        *(s32 *)(actorSub + 0x24) = 0;
        stateSlot = (u8 *)((s32)*(s16 *)(self + 0x22) * 2 + (s32)self);
        stateSlot[0x19] = 0;
        funcSlot = (s32 *)0x08671BB0;
        stateBase = self + 0x18;
        sub_080C31E4(stateBase, self + 0x22, *funcSlot);
    }
}
