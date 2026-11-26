extern u8 D_0810063C[];
extern void setAnimationFrame(void *, void *, s16, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Drive an object's animation from a per-kind action table, nudge its counter when
 * a sub-step finishes, and advance the script step / post a message on completion. */
void sub_08092854(u8 *effect)
{
    u8 *fx;
    u8 *work;
    u8 *anim;
    u8 *animTable;
    s16 stepIdx;
    u8 zeroByte;

    fx = *(u8 **)(effect + 0x38);
    work = *(u8 **)(effect + 0x3C);
    anim = work + 0x24;

    animTable = D_0810063C;
    {
        s32 tableOffset = *(s32 *)work * 4;
        animTable = animTable + 2;
        setAnimationFrame(fx, anim, *(s16 *)(animTable + tableOffset), 0);
    }

    if (anim[1] == 1 && *(u32 *)(anim + 4) == (u16)(*(u16 *)(anim + 2)) - 1) {
        *(s32 *)(work + 0x14) += 0xFFFE0000;
    }
    if (anim[1] == 2 && *(u32 *)(anim + 4) == (u16)(*(u16 *)(anim + 2)) - 1) {
        *(s32 *)(work + 0x14) += 0xFFFE0000;
    }

    zeroByte = 0;
    if (anim[0] & 2) {
        u8 *completionTable = D_0810063C;
        s32 tableOffset = *(s32 *)work * 4;
        setAnimationFrame(fx, anim, *(s16 *)(completionTable + tableOffset), 0);
        *(u16 *)(work + 0x0C) = 0;
        stepIdx = *(s16 *)(effect + 0x22);
        effect[stepIdx * 2 + 0x19] = zeroByte;
        {
            u32 msgLiteral = (u32)0x08671BD0;
            sub_080C31E8(effect + 0x18, effect + 0x22, 0, *(u32 *)msgLiteral);
        }
    }
}
