s32 sub_080B0910(void *, s32, s32, u8);
void sub_080C31E0(void *, s32);

/* On every other step of the current script, flip the entity's flag at +0x74
 * and update its animation using the values at +0x4C/+0x5C; if the byte at
 * +0x70 is set, run the update function stored at +0x24. */
void sub_080AEFE4(void *arg0)
{
    if (!(3 & *(u8 *)((s8 *)((*(s16 *)((s8 *)arg0 + 0x22) * 2) + (s32)arg0) + 0x19))) {
        *(u8 *)((s8 *)arg0 + 0x74) = (u8)((*(u8 *)((s8 *)arg0 + 0x74) + 1) & 1);
        sub_080B0910(arg0, *(s32 *)((s8 *)arg0 + 0x4C), *(s32 *)((s8 *)arg0 + 0x5C), *(u8 *)((s8 *)arg0 + 0x74));
    }
    if (*(u8 *)((s8 *)arg0 + 0x70) != 0) {
        sub_080C31E0(arg0, *(s32 *)((s8 *)arg0 + 0x24));
    }
}
