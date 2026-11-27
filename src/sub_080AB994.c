/* Advance an actor's attack action: set state flags, apply one sequence step,
 * write two global registers, spawn/configure a projectile with a randomized
 * offset, and finish the script when its byte reaches 0xB4. */
extern s32 randomSignedOffset(s32);
extern void sub_080AC908(void *, void *, void *, void *);
extern void sub_080B089C(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u16 gCrossfadeGfxState[];

void sub_080AB994(void *actor)
{
    u8 *self = (u8 *)actor;
    u8 *state = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *seq = work + 0x34;
    u8 *params = work + 0x48;
    s16 scriptIndex = *(s16 *)(self + 0x22);
    s32 *dispatchArg;

    if ((*(u8 *)(self + scriptIndex * 2 + 0x19) & 2) == 0) {
        *(u16 *)state = (*(u16 *)state & 0x0FFF) | (0xE0 << 8);
    }

    sub_080AC908(state, seq, work, params);

    gCrossfadeGfxState[2] = 0xFD << 6;
    {
        u8 byte95 = *(u8 *)(work + 0x95);
        gCrossfadeGfxState[3] = byte95 | ((0x10 - byte95) << 8);
    }

    sub_080B089C(*(s32 *)(work + 8) + randomSignedOffset(0xC0 << 13), 0x88 << 16);

    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0xB4) {
        u16 flags = *(u16 *)(state + 2);
        flags |= (0x80 << 3);
        *(u16 *)(state + 2) = flags;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        dispatchArg = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *dispatchArg);
    }
}
