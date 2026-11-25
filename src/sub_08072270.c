extern s32 sub_080C31E0(void *arg, s32 callback);

/* Dispatch the handler previously saved in (entity+0x6C)->+0x1C, passing the
 * entity itself as the only argument. */
void sub_08072270(void *entity) {
    sub_080C31E0(entity, *(s32 *)(*(void **)((u8 *)entity + 0x6C) + 0x1C));
}
