extern s32 sub_080C31E0(void *, s32);

/* Fade follow-up update: once the timer at entity+0x22 passes 11, chain to the
 * saved update callback stored at entity+0x24. */
void sub_080627C8(void *entity) {
    if ((s32)(*(s16 *)((s8 *)entity + 0x22)) > 0xB) {
        sub_080C31E0(entity, *(s32 *)((s8 *)entity + 0x24));
    }
}
