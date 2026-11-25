extern s16 D_0810063C[][2];
extern void sub_08011368(void *, void *, s16, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Drive an object's animation from a per-kind action table, nudge its counter when
 * a sub-step finishes, and advance the script step / post a message on completion. */
void sub_08092744(u8 *effect)
{
    u8 *fx;
    u8 *work;
    u8 *anim;
    u8 zeroByte;

    fx = *(u8 **)(effect + 0x38);
    work = *(u8 **)(effect + 0x3C);
    anim = work + 0x24;

    sub_08011368(fx, anim, D_0810063C[*(s32 *)work][0], 0);

    if (anim[1] == 1 && *(u32 *)(anim + 4) == (u16)(*(u16 *)(anim + 2)) - 1) {
        *(s32 *)(work + 0x14) += 0x20000;
    }
    if (anim[1] == 2 && *(u32 *)(anim + 4) == (u16)(*(u16 *)(anim + 2)) - 1) {
        *(s32 *)(work + 0x14) += 0x20000;
    }

    zeroByte = 0;
    if (anim[0] & 2) {
        sub_08011368(fx, anim, D_0810063C[*(s32 *)work][1], 0);
        *(u16 *)(work + 0x0C) = 0;
        effect[*(s16 *)(effect + 0x22) * 2 + 0x19] = zeroByte;
        {
            s32 *lit = (s32 *)0x08671BB0;
            sub_080C31E4(effect + 0x18, effect + 0x22, *lit);
        }
    }
}
