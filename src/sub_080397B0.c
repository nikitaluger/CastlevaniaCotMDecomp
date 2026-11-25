extern void sub_08015974(void);
extern void sub_080161F0(void);
extern void sub_08016678(void *);
extern void sub_080C31E0(void *, s32);

/* Actor teardown: free the two optional list entries still attached to its
 * work block (+0x28 and +0x48) and the one at +0x2C, detach the work object,
 * then hand over to the update callback. */
void sub_080397B0(void *arg0) {
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    if (*(s32 *)(work + 0x28) != 0) {
        sub_080161F0();
    }
    if (*(s32 *)(work + 0x48) != 0) {
        sub_080161F0();
    }
    if (*(s32 *)(work + 0x2C) != 0) {
        sub_08015974();
    }
    sub_08016678(arg0);
    sub_080C31E0(arg0, *(s32 *)(work + 0x24));
}
