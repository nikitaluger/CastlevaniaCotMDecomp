/* Increments the 32-bit counter stored at offset +4 of the object. */
void sub_0800951C(void *obj) {
    *(s32 *)((s8 *)obj + 4) = (s32)(*(s32 *)((s8 *)obj + 4) + 1);
}
