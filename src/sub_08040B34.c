void *sub_0805FAEC(s32, s32);

struct S_02025FF0_B34 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0_B34 D_02025FF0;

/* Allocate an effect object and place it relative to the state's position,
 * shifting one coordinate by +/-24 depending on flag 0x10; clear a flag. */
void sub_08040B34(s32 unused, void *flags, void *state) {
    void *effect = sub_0805FAEC(D_02025FF0.v, 0x108);
    if (effect != NULL) {
        s32 coord = *(s32 *)((u8 *)state + 8);
        if (*(u16 *)((u8 *)flags + 2) & 0x10) {
            s32 offset = 0x180000;
            *(s32 *)((u8 *)effect + 0x4C) = coord + offset;
        } else {
            s32 offset = (s32)0xFFE80000;
            *(s32 *)((u8 *)effect + 0x4C) = coord + offset;
        }
        *(s32 *)((u8 *)effect + 0x5C) = *(s32 *)((u8 *)state + 0xC);
        *(u8 *)((u8 *)effect + 0x7C) = 0;
    }
}
