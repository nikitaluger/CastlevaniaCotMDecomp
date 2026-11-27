extern void freeMotionTracker(void);
extern void unlinkAndFreeObject(void);
extern void sub_08016678(void *);
extern void sub_080C31E0(void *, s32);

/* Actor teardown: free the two optional list entries attached to its work block
 * and the one in its +0x48 sub-block (the values are left in r0 for the
 * callees), detach the work object, then hand over to the update callback. */
void sub_0803443C(void *arg0) {
    void *work = *(void **)((s8 *)arg0 + 0x3C);
    void *sub = (s8 *)work + 0x48;
    if (*(s32 *)((s8 *)work + 0x28) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)((s8 *)sub + 0x0C) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)((s8 *)work + 0x2C) != 0) {
        freeMotionTracker();
    }
    sub_08016678(arg0);
    sub_080C31E0(arg0, *(s32 *)((s8 *)work + 0x24));
}
