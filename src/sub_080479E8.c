/* Tear down an object: free/link-out its four optional sub-objects, reset its
 * field state, then dispatch its stored callback. */
void sub_08015974();
void sub_080161F0();
void sub_08016678(void *);
void sub_080C31E0(void *, s32);

void sub_080479E8(void *arg0) {
    u8 *fields = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *slots = fields + 0x48;
    if (*(s32 *)(fields + 0x28) != 0) sub_080161F0();
    if (*(s32 *)(slots + 0x10) != 0) sub_080161F0();
    if (*(s32 *)(fields + 0x2C) != 0) sub_08015974();
    if (*(s32 *)(slots + 0x14) != 0) sub_08015974();
    sub_08016678(arg0);
    sub_080C31E0(arg0, *(s32 *)(fields + 0x24));
}
