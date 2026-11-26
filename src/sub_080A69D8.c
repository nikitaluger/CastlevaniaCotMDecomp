void sub_08005E80(s32);
s32 sub_080A8784(void *, void *);
void sub_080AAC58(void);
void sub_080C31E4(void *, void *, s32);

struct S_02025FF0 { u8 _0[0x1754]; s32 phase; };
extern struct S_02025FF0 gMainWorkspace;
extern s32 D_081020AC[];

/* Enemy actor step: advance a clamped aim accumulator by a per-index step;
 * when the aim check passes, load a resource, advance the global phase, spawn
 * effects, reset the script byte and dispatch the handler. */
void sub_080A69D8(u8 *self) {
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *state = work + 0x48;
    u8 *angle = work + 0xE8;
    s32 newAngle = *(s32 *)angle + D_081020AC[*(u8 *)(self + 0x4C)];

    *(s32 *)angle = newAngle;
    if (newAngle < (s32)0xFFFFE800) *(s32 *)angle = (s32)0xFFFFE800;
    {
        s32 clampedAngle = *(s32 *)angle;
        if (clampedAngle > 0x1800) *(s32 *)angle = 0x1800;
    }
    if (sub_080A8784(self, state) != 0) {
        sub_08005E80(0x178);
        if (gMainWorkspace.phase <= 0x10) gMainWorkspace.phase = 0x11;
        sub_080AAC58();
        *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *handlerTable = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
        }
    }
}
