extern s32 sub_0800583C(s32);
extern void sub_08011368(void *, void *, s32, s32);
extern void sub_080113A8(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Entity update: advance the animation.  When its flag byte has bit 1 set
 * (the animation finished), give the sub-struct at actor+0x48 a random upward
 * speed, switch to animation 5, nudge the actor's x position left or right by
 * 0x200000 according to the gfx facing flag, set otherObj+1 to 5, clear the
 * local state and advance to the next state. */
void sub_080BD8B8(void *arg0)
{
    u8 *self = arg0;
    u8 *gfx = *(u8 **)(self + 0x38);
    u8 *actor = *(u8 **)(self + 0x3C);
    u8 *anim = actor + 0x34;
    u8 *actorSub = actor + 0x48;

    sub_080113A8(gfx, anim);
    if (anim[0] & 2) {
        *(s32 *)(actorSub + 0x10) = sub_0800583C(0x8000) + 0x10000;
        sub_08011368(gfx, anim, 5, 1);
        {
            s32 xPos = *(s32 *)(actor + 8);
            if (*(u16 *)(gfx + 2) & 0x10) {
                *(s32 *)(actor + 8) = xPos + 0xFFE00000;
            } else {
                *(s32 *)(actor + 8) = xPos + 0x00200000;
            }
        }
        {
            u8 *otherObj = *(u8 **)(actor + 0x28);
            s32 zero = 0;
            otherObj[1] = 5;
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        }
        {
            s32 *funcSlot = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *funcSlot);
        }
    }
}
