struct Enemy {
    u8 _0[0x18]; u8 f18; u8 _19[9]; s16 f22; u8 _24[0x14];
    u32 f38; u8 _3C[0x30]; u32 f6C;
};
struct EnemyState { u8 _0[0xD0]; u16 fD0; u16 fD2; };
struct AiWork { u8 _0[8]; u32 f08; u32 f0C; u8 _10[0x1A]; u16 f2A; u16 f2C; u8 _2E[0x12]; u32 f40; u8 _44[0x80]; u32 fC4; };
extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_0806AB04(void *, void *, void *, void *);
extern void sub_0806A7AC(void *, void *, s32);
extern void sub_0806A884(void *, void *);
extern void sub_0806A800(void *, s32);
extern void sub_08003A6C(void *, s32, void *);
extern u16 sub_0806BCD8(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void sub_08003740(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void *gMainObjTimerCallback;
extern void *D_08671BD0;
extern void *D_08671BD8;

/*
 * Per-frame AI update for an enemy: run the shared camera/AI-work setup, apply
 * the movement step, tick the script timer and dispatch script commands for the
 * current state (with special moves for enemy type 0x14).
 */
void sub_08064F94(struct Enemy *enemy) {
    struct EnemyState *state; struct AiWork *work; struct AiWork *workEnd; s32 sprite; s32 status; u8 *timer; s32 *scriptTable;
    state = (struct EnemyState *)enemy->f6C;
    workEnd = (struct AiWork *)((u8 *)state + 4);
    sprite = enemy->f38;
    work = workEnd;
    status = sub_0806C4B4(work, work);
    if (status != 0) return;
    sub_0806C5EC(enemy, (void *)sprite, work, work);
    if (work->f2A > 1) state->fD0 |= 2;
    sub_0806AB04(enemy, (void *)sprite, work, work);
    if (work->f40 == 0) {
        sub_0806A7AC((void *)sprite, work, 0x10);
        *(u8 *)((u32)enemy->f22 * 2 + (u32)enemy + 0x17) = status;
        { void **script = &D_08671BD8; sub_080C31E8((u8 *)enemy + 0x18, (u8 *)enemy + 0x22, 3, *script); }
    }
    sub_0806A884((void *)sprite, work);
    timer = (u8 *)state + 0x2C;
    sub_08003740(timer, (void *)sprite);
    if (enemy->f18 == 0x14) {
        switch (work->f2C) {
        case 3:
            sub_0806A800(work, 0x87);
            if (state->fD2 & 0x200) {
                sub_0806A800(work, 0x1D);
                sub_08003A6C(timer, 0, (void *)0x0846B23C);
                work->f08 = (u32)status;
                work->f0C = (u32)status;
                *(u8 *)((u32)enemy->f22 * 2 + (u32)enemy + 0x19) = status;
                { void **script = &D_08671BD0; sub_080C31E8((u8 *)enemy + 0x18, (u8 *)enemy + 0x22, 3, *script); }
            }
            break;
        case 4:
            sub_0806A800(work, 0x88);
            *(u8 *)((u32)enemy->f22 * 2 + (u32)enemy + 0x19) = status;
            scriptTable = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)enemy + 0x18, (u8 *)enemy + 0x22, *scriptTable);
            break;
        }
    }
    workEnd->fC4 = sub_0806BCD8(enemy, (void *)sprite, workEnd, work);
    if (workEnd->fC4 != 0) {
        sub_08003740((u8 *)workEnd + 0x28, (void *)sprite);
        *(u8 *)((u32)enemy->f22 * 2 + (u32)enemy + 0x17) = 0;
        { void **script = &D_08671BD8; sub_080C31E8((u8 *)enemy + 0x18, (u8 *)enemy + 0x22, workEnd->fC4, *script); }
    }
    sub_0806C6B0(enemy, (void *)sprite, workEnd, work);
}
