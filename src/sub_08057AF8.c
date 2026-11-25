extern s32 sub_080C31E0(s32, s32);

/* Reverse travel direction: flips the direction flag and steps the position
 * by one unit along the new heading using the sine table (0x4000 = quarter
 * turn, <<4 = one unit). */
void sub_08057AF8(void *arg0) {
    u8 *params = (u8 *)arg0;

    if (*params != 0) {
        *params = 0;
        {
            void **trigTable = (void **)0x08671BFC;
            *(s32 *)(params + 4) -= sub_080C31E0(*(s32 *)(params + 0xC) + (0x80 << 7), (s32)*trigTable) << 4;
            *(s32 *)(params + 8) += sub_080C31E0(*(s32 *)(params + 0xC), (s32)*trigTable) << 4;
        }
    } else {
        *params = 1;
        {
            void **trigTable = (void **)0x08671BFC;
            *(s32 *)(params + 4) += sub_080C31E0(*(s32 *)(params + 0xC) + (0x80 << 7), (s32)*trigTable) << 4;
            *(s32 *)(params + 8) -= sub_080C31E0(*(s32 *)(params + 0xC), (s32)*trigTable) << 4;
        }
    }
}
