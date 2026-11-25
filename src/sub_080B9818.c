/* Restart a travelling object: set its active flag at +0x4C and store the
 * given step value at +0x5C. */
void sub_080B9818(void *mover, s32 stepValue) {
    *(s8 *)((s8 *)mover + 0x4C) = 1;
    *(s32 *)((s8 *)mover + 0x5C) = stepValue;
}
