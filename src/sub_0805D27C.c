extern s32 sub_080C31E0(s32, s32);

struct S_02025FF0 { u8 _pad[0x189C]; u32 field189C; };
extern struct S_02025FF0 gMainWorkspace;

/* Effect update: in one mode, drive the state object's X from a phase counter
 * and a table function; then count down a timer, dispatch this entity's
 * completion callback when it expires, and near the end clear a handle flag. */
void sub_0805D27C(void *self) {
    void *handle;
    void *state;
    u8 *timerPtr;
    u8 *modePtr;

    handle = *(void **)((u8 *)self + 0x38);
    modePtr = (u8 *)self + 0x4C;
    state = *(void **)((u8 *)self + 0x3C);
    timerPtr = (u8 *)state + 0x48;

    if ((*(u16 *)(modePtr + 8) & 0xF) == 5 && (*(u16 *)((u8 *)state + 2) & 4) == 0) {
        u32 *funcTable = (u32 *)0x08671BFC;
        u32 *phase = (u32 *)((u8 *)state + 0x4C);
        u32 phaseValue = *phase;
        u32 phaseScaled = phaseValue * 0x222;
        *phase = phaseValue + 1;
        *(u32 *)((u8 *)state + 8) = (sub_080C31E0(phaseScaled, *funcTable) << 3) + *(u32 *)((u8 *)self + 0x4C);
    }

    {
        u32 timerMinusOne;
        s16 timerLeft;
        timerMinusOne = *(u16 *)timerPtr - 1;
        *(u16 *)timerPtr = timerMinusOne;
        timerLeft = (s16)timerMinusOne;
        if (timerLeft < 0) {
            sub_080C31E0((s32)self, *(s32 *)((u8 *)self + 0x24));
            return;
        }
        if (timerLeft <= 0x77 && (gMainWorkspace.field189C & 1)) {
            *(u8 *)((u8 *)handle + 0x2A) &= 0xBF;
        }
    }
}
