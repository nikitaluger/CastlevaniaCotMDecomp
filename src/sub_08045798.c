/* Tear down an object: free its four optional sub-objects, reset its field
 * state, then dispatch its stored callback. */
void sub_08015974();
void unlinkAndFreeObject();
void sub_08016678(void *);
void sub_080C31E0(void *, s32);

void sub_08045798(void *arg0) {
    u8 *fields = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *slots = fields + 0x48;
    if (*(s32 *)(fields + 0x28) != 0) unlinkAndFreeObject();
    if (*(s32 *)(fields + 0x2C) != 0) sub_08015974();
    if (*(s32 *)(slots + 8) != 0) unlinkAndFreeObject();
    if (*(s32 *)(slots + 0xC) != 0) unlinkAndFreeObject();
    sub_08016678(arg0);
    sub_080C31E0(arg0, *(s32 *)(fields + 0x24));
}
