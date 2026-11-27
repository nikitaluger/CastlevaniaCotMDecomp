/* Tear down an object: free its four optional sub-objects, reset its field
 * state, then hand control to the callback stored at fields+0x24. */
void unlinkAndFreeObject(void);
void freeMotionTracker(void);
void sub_08016678(void *);
void _call_via_r1(void *, void *);

void sub_08035D6C(void *obj) {
    u8 *fields = *(u8 **)((u8 *)obj + 0x3C);
    u8 *slots = fields + 0x48;
    if (*(s32 *)(fields + 0x28) != 0) unlinkAndFreeObject();
    if (*(s32 *)(fields + 0x48) != 0) unlinkAndFreeObject();
    if (*(s32 *)(slots + 4) != 0) unlinkAndFreeObject();
    if (*(s32 *)(fields + 0x2C) != 0) freeMotionTracker();
    sub_08016678(obj);
    _call_via_r1(obj, *(void **)(fields + 0x24));
}
