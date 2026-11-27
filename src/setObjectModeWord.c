/* Set the companion/effect object's mode word at +0x5C. */
void setObjectModeWord(void *obj, s32 mode) {
    *(s32 *)((s8 *)obj + 0x5C) = mode;
}
