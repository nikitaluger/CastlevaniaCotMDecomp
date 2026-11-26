extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080146D0(void *, s32, s32);
extern s32 sub_08014990(void *);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, u32);

/* Scripted mover: advances the animation and a countdown; on expiry it picks a
 * left/right launch speed from the facing flag, fires the script callback and
 * otherwise wraps a phase value to update the work velocity from a table. */
void sub_0804F558(void *arg0) {
    void *sprite;
    void *work;
    u8 *steer;
    u8 *animState;
    u32 remaining;
    s32 facing;

    sprite = *(void **)((u8 *)arg0 + 0x38);
    work = *(void **)((u8 *)arg0 + 0x3C);
    animState = (u8 *)work + 0x34;
    steer = (u8 *)work + 0x48;
    setAnimationFrame(sprite, animState, 0, 1);
    remaining = *(u16 *)(steer + 0xC) - 1;
    *(u16 *)(steer + 0xC) = remaining;
    if ((s32)(remaining << 16) < 0) {
        s32 speed;
        u32 *callbacks;
        facing = sub_08014990(sprite);
        speed = 0;
        if (facing <= 0)
            speed = 0x8000;
        *(u32 *)(steer + 8) = speed;
        sub_080146D0(work, speed, 0x28000);
        *(u8 *)((u8 *)arg0 + ((s32)*(s16 *)((u8 *)arg0 + 0x22) * 2) + 0x19) = 0;
        callbacks = (u32 *)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *callbacks);
    } else {
        u32 phase;
        u32 *table;
        phase = (*(u32 *)(steer + 4) + 0x800) & 0xFFFF;
        *(u32 *)(steer + 4) = phase;
        table = (u32 *)0x08671BFC;
        *(u32 *)((u8 *)work + 0x14) = (sub_080C31E0(phase, *table) << 1) + *(u32 *)steer - *(u32 *)((u8 *)work + 0xC);
    }
}
