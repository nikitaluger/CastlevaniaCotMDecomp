s32 sub_080114DC(s32, s32, s32, s32);
s32 sub_08011528(s32, s32);
s32 sub_080148D8(s32, s32);
s32 sub_08014900(s32);
void sub_080C31E4(void *, void *, s32);

/* Enemy idle update: play its animation, face the player, and every 20
 * frames record whether the player is close (flag 0) or far (flag 1) before
 * running the next script command. */
void sub_080B38F8(void *arg0)
{
    s32 *litp;
    s32 anim;
    s32 animDesc;
    void *motion;

    anim = *((s32 *)((s8 *)arg0 + 0x38));
    motion = *((void **)((s8 *)arg0 + 0x3C));
    animDesc = (s32)((s8 *)motion + 0x34);
    sub_080114DC(anim, animDesc, 0, 1);
    sub_08011528(anim, animDesc);
    sub_080148D8(anim, *((s32 *)((s8 *)motion + 8)));
    if (*((u8 *)((s8 *)arg0 + *((s16 *)((s8 *)arg0 + 0x22)) * 2 + 0x19)) == 0x14) {
        if (sub_08014900(*((s32 *)((s8 *)motion + 8))) <= 0x3FFFFF) {
            *((u8 *)((s8 *)motion + 0x68)) = 0;
        } else {
            *((u8 *)((s8 *)motion + 0x68)) = 1;
        }
        *((s8 *)((s8 *)arg0 + *((s16 *)((s8 *)arg0 + 0x22)) * 2 + 0x19)) = 0;
        litp = (s32 *)0x08671BB0;
        sub_080C31E4((s8 *)arg0 + 0x18, (s8 *)arg0 + 0x22, *litp);
    }
}
