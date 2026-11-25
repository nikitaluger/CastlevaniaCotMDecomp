s32 sub_08014620(s32, s32, s32);
void sub_08005E80(u16);
void sub_080C31E0(void *, s32);

/* Spawn an effect object at the state's position with parameter 8, start
 * song 0x83, then run the entity's saved update callback. */
void sub_080BC718(void *entity) {
    u8 *work = *(u8 **)((u8 *)entity + 0x3C);
    sub_08014620(*(s32 *)(work + 8), *(s32 *)(work + 0xC), 8);
    sub_08005E80(0x83);
    sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
}
