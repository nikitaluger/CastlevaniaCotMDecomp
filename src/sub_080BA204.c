s32 sub_080BE58C(void *, s32);
s32 setEffectPartState(s32);
s32 sub_080BE8D0(s32, s32);
s32 sub_080C31E4(void *, void *, s32);

/* Decrement an effect's fixed-point countdown; when it expires, flag the
 * target sprite, run cleanup, repeat a helper eight times and dispatch the
 * next bytecode script command. */
void sub_080BA204(void *arg0) {
    s32 remaining;
    u32 i;
    void *effectState;
    void *sprite;

    effectState = *(s32 *)((u8 *)arg0 + 0x3C) + 0x48;
    sprite = *(void **)((u8 *)arg0 + 0x4C);
    remaining = *(s32 *)((u8 *)effectState + 0x40) + 0xFFFFF800;
    *(s32 *)((u8 *)effectState + 0x40) = remaining;
    if (remaining < 0) {
        *(s32 *)((u8 *)effectState + 0x40) = 0;
    }
    sub_080BE8D0(*(s32 *)((u8 *)effectState + 0x34), *(s32 *)((u8 *)effectState + 0x40));
    if (*(s32 *)((u8 *)effectState + 0x40) == 0) {
        *(s8 *)((u8 *)sprite + 0x34) = 1;
        setEffectPartState(*(s32 *)((u8 *)effectState + 0x34));
        i = 0;
        do {
            sub_080BE58C(arg0, 0);
            i += 1;
        } while (i <= 7U);
        *(s8 *)((u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2) + 0x19) = 0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *(s32 *)0x08671BB0);
    }
}
