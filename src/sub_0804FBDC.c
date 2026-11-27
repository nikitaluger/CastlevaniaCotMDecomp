extern u32 gScriptStepCallbacks[];

s32 scaleByRandom(s32);
void setAnimationFrame(s32, void *, u16, u8);
s32 sub_08014900(s32);
s32 sub_0801491C(s32);
void sub_080C31E8(void *, void *, s32, s32);

// Idle animator step: play frame 0 and decrement the pose countdown; when it
// expires, reset it randomly and, if work X/Y positions are in range, reset
// the script-step byte and dispatch via gScriptStepCallbacks, otherwise use countdown 8.
void sub_0804FBDC(u8 *arg0) {
    u8 *self = arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animator = work + 0x34;
    u8 *pose = work + 0x48;
    s32 countdown;

    setAnimationFrame(sprite, animator, 0, 1);

    countdown = *(u16 *)(pose + 2) - 1;
    *(u16 *)(pose + 2) = countdown;
    if ((s32)(countdown << 16) <= 0) {
        *(u16 *)(pose + 2) = scaleByRandom(0x33) + 0x64;
        if (sub_08014900(*(s32 *)(work + 8)) <= 0x00800000 &&
            sub_0801491C(*(s32 *)(work + 0xC)) <= 0x00600000) {
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
            {
                u32 *scriptTable = gScriptStepCallbacks;
                sub_080C31E8(self + 0x18, self + 0x22, 1, *scriptTable);
            }
        } else {
            *(u16 *)(pose + 2) = 8;
        }
    }
}
