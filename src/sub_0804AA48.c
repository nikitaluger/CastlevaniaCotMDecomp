extern void sub_08011368(void *, void *, s32, s32);
extern void sub_080113A8(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *D_08671BB0;

/* Idle update for a scripted object: refresh its animation and, after a
 * 32-frame delay, play animation 5 and execute the next script command. */
void sub_0804AA48(void *arg0)
{
    void *anim;
    u8 *motion;
    u8 *delay;
    u8 *animDesc;
    s16 scriptIdx;
    u8 *scriptPos;

    anim = *(void **)((u8 *)arg0 + 0x38);
    motion = *(u8 **)((u8 *)arg0 + 0x3C);
    animDesc = motion + 0x34;
    delay = motion + 0x48;

    sub_080113A8(anim, animDesc);

    if ((delay[0x0C] = delay[0x0C] + 1) == 0x20) {
        sub_08011368(anim, animDesc, 5, 0);

        scriptIdx = *(s16 *)((u8 *)arg0 + 0x22);
        ((u8 *)arg0)[scriptIdx * 2 + 0x19] = 0;

        {
            void **lit = &D_08671BB0;
            scriptPos = (u8 *)arg0 + 0x18;
            sub_080C31E4(scriptPos, (u8 *)arg0 + 0x22, *lit);
        }

        scriptIdx = *(s16 *)((u8 *)arg0 + 0x22);
        ((u8 *)arg0)[scriptIdx * 2 + 0x19]++;

        scriptIdx = *(s16 *)((u8 *)arg0 + 0x22);
        scriptPos = scriptPos + scriptIdx * 2;
        sub_080C31E0(arg0, *(void **)(*(u32 *)((u8 *)arg0 + 0x14) + scriptPos[0] * 4));
    }
}
