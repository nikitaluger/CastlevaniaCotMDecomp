extern void sub_08015974(void);
extern void unlinkAndFreeObject(void);
extern void sub_08016678(void *);
extern void sub_080C31E0(void *, s32);

/* Actor teardown: free the two optional list entries attached to its work block
 * and the one in its +0x48 sub-block (the values are left in r0 for the
 * callees), detach the work object, then hand over to the update callback. */
void sub_08030F54(void *arg0) {
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *sub = work + 0x48;
    if (*(s32 *)(work + 0x28) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)(work + 0x2C) != 0) {
        sub_08015974();
    }
    if (*(s32 *)(sub + 0x14) != 0) {
        unlinkAndFreeObject();
    }
    sub_08016678(arg0);
    sub_080C31E0(arg0, *(s32 *)(work + 0x24));
}
