extern void sub_08015974(void);   /* release a 0x14-byte particle object */
extern void unlinkAndFreeObject(void);   /* release a 0x34-byte particle object */
extern void sub_08016678(void *);
extern void sub_080C31E0(void *, s32);

/* Tear down an effect's attached particles: free the two large objects at
 * work+0x28 and work+0x58, the two small ones at work+0x2C and work+0x5C and
 * the two large ones in the work+0x50 pair, then finalize the work state, clear
 * work+0x30 and run the object's callback. */
void sub_0804E410(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *slots;
    s32 i;
    slots = work + 0x48;
    if (*(u32 *)(work + 0x28) != 0) {
        unlinkAndFreeObject();
    }
    if (*(u32 *)(slots + 0x10) != 0) {
        unlinkAndFreeObject();
    }
    if (*(u32 *)(work + 0x2C) != 0) {
        sub_08015974();
    }
    if (*(u32 *)(slots + 0x14) != 0) {
        sub_08015974();
    }
    slots = work + 0x50;
    i = 1;
    do {
        if (*(u32 *)slots != 0) {
            unlinkAndFreeObject();
        }
        slots += 4;
        i--;
    } while (i >= 0);
    sub_08016678(arg0);
    sub_080C31E0(arg0, *(s32 *)(work + 0x24));
}
