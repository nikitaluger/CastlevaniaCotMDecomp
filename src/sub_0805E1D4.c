extern void sub_0805F0C8(s32);
extern void sub_080C31E0(void *, void *);

/* Clear the owner's mirror bit and the attached object's flag, spawn the
 * sound/effect matching the current attack type, then run the entity script. */
void sub_0805E1D4(void *arg0) {
    u8 *owner = *(u8 **)((u8 *)arg0 + 0x38);
    u8 *source = *(u8 **)((u8 *)arg0 + 0xAC);
    u8 *attached = *(u8 **)((u8 *)arg0 + 0x3C);
    s32 soundId;
    u8 attr;

    attr = owner[0x2A] & 0xBF;
    soundId = 0;
    owner[0x2A] = attr;
    (*(u8 **)(attached + 0x28))[1] = soundId;

    switch (*(u16 *)(*(u8 **)(source + 4) + 6) & 0xF) {
    case 0:
        soundId = 0x8157;
        break;
    case 1:
        soundId = 0x8155;
        break;
    case 2:
        soundId = 0x8156;
        break;
    }

    sub_0805F0C8(soundId);
    sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
}
