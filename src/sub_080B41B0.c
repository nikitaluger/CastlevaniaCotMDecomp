void sub_0809856C(s32, void *, s32);
void advanceAnimTrack(void *, void *);
void sub_08011EE8(void *, s32, s32);
void sub_080B7288(s32);
void sub_080C31E4(void *, void *, s32);

/* Object update: play its animation, apply gravity, then at frame 56 spawn a
 * projectile and at frame 60 reset the counter and run the next script
 * command. */
void sub_080B41B0(void *arg0)
{
    u8 *self = (u8 *)arg0;
    void *anim = *(void **)(self + 0x38);
    u8 *motion = *(u8 **)(self + 0x3C);
    u8 *animDesc = motion + 0x34;
    u8 *params = motion + 0x48;

    sub_0809856C(0x18F, motion + 0x6C, 0x0A);
    advanceAnimTrack(anim, animDesc);
    sub_08011EE8(motion, 0x4000, 0);

    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x38)
        sub_080B7288(*(s32 *)(params + 0x10));

    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x3C)
    {
        s32 *litp;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        litp = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *litp);
    }
}
