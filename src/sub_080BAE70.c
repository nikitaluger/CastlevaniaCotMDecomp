/*
 * Actor script step: animate the actor's vertical bob and update its attached
 * parts; at step 0x0C load effect graphic 0x1AB, at step 0x3C load graphic
 * 0x1AD plus tile set 0x08441630, then restart the animation and advance the
 * script.
 */
extern s32 sub_08005E80(s32 resource);  /* load a graphics resource */
extern s32 sub_080BB984(s32 work, s32 anim);
extern s32 sub_080BB9C8(void *self);
extern s32 sub_080BBA4C(void *self);
extern s32 sub_080BE838(void);  /* load tile set 0x08441630 */
extern s32 sub_080C31E4(void *, void *, s32);

void sub_080BAE70(void *arg0)
{
    s32 work;
    s32 *stepCallback;

    work = *(s32 *)((s8 *)arg0 + 0x3C);
    sub_080BB984(work, work + 0x48);
    sub_080BB9C8(arg0);
    if (*(u8 *)((s8 *)((*(s16 *)((s8 *)arg0 + 0x22) * 2) + arg0) + 0x19) == 0xC) {
        sub_08005E80(0x1AB);
        sub_080BBA4C(arg0);
    }
    if (*(u8 *)((s8 *)((*(s16 *)((s8 *)arg0 + 0x22) * 2) + arg0) + 0x19) == 0x3C) {
        sub_08005E80(0x1AD);
        sub_080BE838();
        *(s8 *)((s8 *)((*(s16 *)((s8 *)arg0 + 0x22) * 2) + arg0) + 0x19) = 0;
        stepCallback = &(*(s32 *)0x08671BB0);
        sub_080C31E4((s8 *)arg0 + 0x18, (s8 *)arg0 + 0x22, *stepCallback);
    }
}
