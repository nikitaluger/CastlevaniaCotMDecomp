void setObjectAnimation(s32, void *, s32, s32);
void sub_08005E80(s32);
void sub_080B719C(s32);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E0(void *, s32);

/* Entity update: run animation 0x52.  When local state reaches 0x0F, play
 * sound 0x194, switch to animation 0x54, flag the sub-struct at actor+0x48,
 * then chain to the next handler: advance state via the function at
 * 0x08671BB0, bump the local state to 1 and dispatch through the pointer
 * table at self+0x14. */
void sub_080B437C(void *arg0)
{
    u8 *self = (u8 *)arg0;
    s32 gfx = *(s32 *)(self + 0x38);
    u8 *actor = *(u8 **)(self + 0x3C);
    u8 *anim = actor + 0x34;
    u8 *actorSub = actor + 0x48;

    setObjectAnimation(gfx, anim, 0x52, 0);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x0F)
    {
        sub_08005E80(0x194);
        setObjectAnimation(gfx, anim, 0x54, 0);
        sub_080B719C(*(s32 *)(actorSub + 0x0C));

        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            const u32 *stateFunc;
            void *statePtr;
            stateFunc = (const u32 *)0x08671BB0;
            statePtr = self + 0x18;
            sub_080C31E4(statePtr, self + 0x22, *stateFunc);
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
            statePtr = (u8 *)statePtr + *(s16 *)(self + 0x22) * 2;
            sub_080C31E0(arg0, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)statePtr * 4));
        }
    }
}
