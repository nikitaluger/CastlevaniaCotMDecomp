/* Starts a multi-part actor's part moving toward a target: sets its state flag
 * to 1 and stores the 16.16 target X/Y position. */
void sub_080BE568(void *part, s32 targetX, s32 targetY) {
    *(s32 *)((s8 *)part + 0x5C) = 1;
    *(s32 *)((s8 *)part + 0x6C) = targetX;
    *(s32 *)((s8 *)part + 0x7C) = targetY;
}
