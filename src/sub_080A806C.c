void sub_08011650(s32);
void sub_08015974();
void unlinkAndFreeObject();
void sub_08016678(void *);
void sub_080C31E0(void *, s32);

/* Tear down an object: free its sub-objects, release the actor's resources,
 * reset its field state, then dispatch its stored callback. */
void sub_080A806C(void *arg0) {
    s32 actor = *(s32 *)((u8 *)arg0 + 0x38);
    u8 *fields = *(u8 **)((u8 *)arg0 + 0x3C);
    if (*(s32 *)(fields + 0x28) != 0) unlinkAndFreeObject();
    if (*(s32 *)(fields + 0x15C) != 0) unlinkAndFreeObject();
    sub_08011650(actor);
    if (*(s32 *)(fields + 0x2C) != 0) sub_08015974();
    sub_08016678(arg0);
    sub_080C31E0(arg0, *(s32 *)(fields + 0x24));
}
