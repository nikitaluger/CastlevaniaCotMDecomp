void sub_080C082C(s32);
void sub_080C09BC(void);

/* m4a/MP2k sound-engine shared state; its pointer lives at 0x03007FF0.
 * magic 0x68736D53 ("Smsh") guards access and is bumped while settings change. */
struct SoundInfo {
    u32 magic;           /* 0x00 */
    u8 _0x04;
    u8 volume;           /* 0x05 */
    u8 panning;          /* 0x06 */
    u8 extFreq;          /* 0x07 */
    u8 _0x08[0x48];
    u8 palette[0x300];   /* 0x50: 12 channel entries of 0x40 bytes */
};

/* Apply a sound-mode bitfield: master volume (0xFF), panning plus channel-palette
 * clear (0xF00), external frequency (0xF000), sound-register bits (0xB00000), and
 * a channel/sound reset (0xF0000). Restore the magic afterwards to publish it. */
void sub_080C08D0(s32 mode)
{
    struct SoundInfo *soundInfo;
    u32 field;
    u8 *pal;

    soundInfo = *(struct SoundInfo **)0x03007FF0;
    if (soundInfo->magic != 0x68736D53) return;
    soundInfo->magic = soundInfo->magic + 1;

    field = mode & 0xFF;
    if (field != 0) {
        soundInfo->volume = field & 0x7F;
    }
    field = mode & 0xF00;
    if (field != 0) {
        soundInfo->panning = field >> 8;
        field = 12;
        pal = soundInfo->palette;
        do {
            *pal = 0;
            field--;
            pal += 0x40;
        } while (field != 0);
    }
    field = mode & 0xF000;
    if (field != 0) {
        soundInfo->extFreq = field >> 12;
    }
    field = mode & 0xB00000;
    if (field != 0) {
        field = (field & 0x300000) >> 14;
        *(u8 *)0x04000089 = (*(u8 *)0x04000089 & 0x3F) | field;
    }
    field = mode & 0xF0000;
    if (field != 0) {
        sub_080C09BC();
        sub_080C082C(field);
    }
    soundInfo->magic = 0x68736D53;
}
