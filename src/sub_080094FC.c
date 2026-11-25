/* Wipe-effect script command: advance the script cursor, then arm the wipe by
 * setting its active flag and timer to 1 and its fill count to 0x7C. */
void sub_080094FC(void *arg0) {
    u8 *state = (u8 *)arg0;

    *(s32 *)(state + 4) = *(s32 *)(state + 4) + 1;
    *(s32 *)(state + 0x98) = 1;
    *(s32 *)((state + 0x98) + 4) = 1;
    *(s32 *)(state + 0xA0) = 0x7C;
}
