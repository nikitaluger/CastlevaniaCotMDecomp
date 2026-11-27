/* Tear down an object: free its four optional sub-objects, reset its field
 * state, then hand control to the callback stored at fields+0x24. */
void freeMotionTracker();
void unlinkAndFreeObject();
void sub_08016678(void *);
void sub_080C31E0(void *, s32);

void sub_08037E34(void *obj) {
    u8 *fields = *(u8 **)((u8 *)obj + 0x3C);
    u8 *slots = fields + 0x48;
    if (*(s32 *)(fields + 0x28) != 0) unlinkAndFreeObject();
    if (*(s32 *)(slots + 0xC) != 0) unlinkAndFreeObject();
    if (*(s32 *)(slots + 0x10) != 0) unlinkAndFreeObject();
    if (*(s32 *)(fields + 0x2C) != 0) freeMotionTracker();
    sub_08016678(obj);
    sub_080C31E0(obj, *(s32 *)(fields + 0x24));
}
