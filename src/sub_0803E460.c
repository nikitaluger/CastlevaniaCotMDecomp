/* Tear down an object: free its optional sub-objects (the pair at fields+0x4C
 * and 0x50), reset its field state, then dispatch its stored callback. */
extern void sub_08015974(void);
extern void unlinkAndFreeObject(void);
extern void sub_08016678(void *);
extern void sub_080C31E0(void *, s32);

void sub_0803E460(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *fields = *(u8 **)(self + 0x3C);
    u32 *slotPtr;
    s32 count;
    if (*(u32 *)(fields + 0x28) != 0) {
        unlinkAndFreeObject();
    }
    if (*(u32 *)(fields + 0x2C) != 0) {
        sub_08015974();
    }
    slotPtr = (u32 *)(fields + 0x4C);
    count = 1;
    do {
        if (*slotPtr != 0) {
            unlinkAndFreeObject();
        }
        slotPtr++;
        count--;
    } while (count >= 0);
    sub_08016678(arg0);
    sub_080C31E0(arg0, *(s32 *)(fields + 0x24));
}
