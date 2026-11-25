/* Store the derived stereo-pan gains, phase and sound type into a voice object. */
void sub_0809C4E8(void *voice, u8 soundType, s32 leftGain, s32 rightGain, u16 phase) {
    if (voice != 0) {
        *(s32 *)((u8 *)voice + 0x4C) = leftGain;
        *(s32 *)((u8 *)voice + 0x5C) = rightGain;
        *(u16 *)((u8 *)voice + 0x6C) = phase;
        *(u8 *)((u8 *)voice + 0x74) = soundType;
    }
}
