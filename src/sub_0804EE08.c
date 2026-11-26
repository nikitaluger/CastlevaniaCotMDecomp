extern s32 setAnimationFrame(s32, s32, s32, s32);
extern s32 sub_080C31E8(void *, void *, s32, s32);

/* Play animation frame 7 forward; once the current script command has been
 * running for more than 90 frames, reset its timer and advance the command
 * script using the table at 0x08671BD0. */
void sub_0804EE08(void *entity) {
    u8 *obj = (u8 *)entity;
    s32 *scriptTable;
    s32 slotOffset;
    u8 *slot;
    setAnimationFrame(*(s32 *)(obj + 0x38), (s32)(*(void **)(obj + 0x3C) + 0x34), 7, 1);
    slotOffset = *(s16 *)(obj + 0x22);
    slotOffset = slotOffset * 2;
    slot = (u8 *)slotOffset;
    slot = slot + (s32)obj;
    if (*(u8 *)(slot + 0x19) > 0x5A) {
        *(u8 *)(slot + 0x19) = 0;
        scriptTable = (s32 *)0x08671BD0;
        sub_080C31E8(obj + 0x18, obj + 0x22, 1, *scriptTable);
    }
}
