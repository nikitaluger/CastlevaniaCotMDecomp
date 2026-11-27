extern void stepAnimationTrack(s32, void *);
extern void setPolarOffset(void *, s32, s32);
extern void advanceMotion(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Projectile flight step: animate it, set its velocity from the fixed angle in
 * +0x4C and the shrinking speed budget in +0x48, integrate the position, then
 * spend one unit of budget; when the budget runs out, deactivate it and
 * advance the entity's script through the global callback. */
void sub_08035150(void *arg0)
{
    s32 parent = *(s32 *)((u8 *)arg0 + 0x38);
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    void *anim = work + 0x34;
    u8 *body = work + 0x48;

    stepAnimationTrack(parent, anim);
    setPolarOffset(work, *(s32 *)(body + 4), *(s32 *)(work + 0x48));
    advanceMotion(work, 0);

    *(s32 *)(work + 0x48) += 0xFFFF0000;
    if (*(s32 *)(work + 0x48) <= 0)
    {
        s32 zero = 0;
        s32 *callback;

        *(s32 *)(work + 0x48) = 0;
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = zero;
        callback = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *callback);
    }
}
