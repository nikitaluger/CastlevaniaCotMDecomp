void sub_08005E80(s32);
void sub_0809C510(s32, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Drives the stereo panning of this effect's looping sound: plays SE 0x166 when
 * the phase counter hits 10, refreshes the voice panning while the counter is
 * 10..20, and at 36 resets the counter and runs the next script step. */
void sub_08099DCC(u8 *arg0) {
    u8 *soundState = *(u8 **)(arg0 + 0x3C) + 0x48;
    s32 phaseOffset;
    s32 phaseOffset2;
    u8 *phasePtr;
    u8 *phasePtr2;
    u8 phase;

    phaseOffset = *(s16 *)(arg0 + 0x22) * 2;
    phaseOffset += (s32)arg0;
    phasePtr = (u8 *)phaseOffset;
    phase = *(phasePtr + 0x19);
    if (phase > 9) {
        if (phase == 0xA) {
            sub_08005E80(0x166);
        }
        phaseOffset2 = *(s16 *)(arg0 + 0x22) * 2;
        phaseOffset2 += (s32)arg0;
        phasePtr2 = (u8 *)phaseOffset2;
        phase = *(phasePtr2 + 0x19);
        if (phase <= 0x14) {
            sub_0809C510(*(s32 *)(soundState + 8), *(s32 *)(soundState + 0x18), 3);
            return;
        }
        if (phase == 0x24) {
            *(phasePtr2 + 0x19) = 0;
            {
                s32 *stepTable = (s32 *)0x08671BB0;
                sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *stepTable);
            }
        }
    }
}
