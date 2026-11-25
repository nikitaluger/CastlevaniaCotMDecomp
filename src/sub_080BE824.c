/* Turn off an effect part by clearing its mode/kind dword at +0x4C. */
void sub_080BE824(void *part) {
    *(s32 *)((u8 *)part + 0x4C) = 0;
}
