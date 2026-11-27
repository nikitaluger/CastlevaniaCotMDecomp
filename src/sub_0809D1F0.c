s32 setObjectAnimation(s32, s32, s32, s32);
s32 setSpriteFacingToTarget(s32, s32);
s32 sub_0809E278(s32, s32, void *, void *);
s32 sub_0809E3B4(s32, void *);
s32 sub_080C31E8(void *, void *, s32, s32);

/* Drive an actor's animation and spawn state: update its facing flag, advance
 * the animation script and choose a spawn target, then on state 4 finish the
 * command and dispatch the next bytecode step. */
void sub_0809D1F0(void *arg0)
{
    s32 sprite;
    s32 anim;
    s32 *commandIdPtr;
    void *work;
    void *effectState;

    sprite = *(s32 *)((u8 *)arg0 + 0x38);
    work = *(void **)((u8 *)arg0 + 0x3C);
    anim = work + 0x34;
    effectState = work + 0x48;
    setSpriteFacingToTarget(sprite, *(s32 *)((u8 *)work + 8));
    setObjectAnimation(sprite, anim, 0, 1);
    sub_0809E278(sprite, anim, work, effectState);
    sub_0809E3B4(*(s32 *)((u8 *)effectState + 0x20), work + 0x5C);
    if (*(u8 *)((u8 *)effectState + 0x14) == 4) {
        *(s32 *)((u8 *)effectState + 0x44) = 0;
        *(s8 *)((u8 *)effectState + 0x11) = 1;
        *(s8 *)((u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2) + 0x19) = 0;
        commandIdPtr = (s32 *)0x08671BD0;
        sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 1, *commandIdPtr);
    }
}
