extern void sub_08015974(void);
extern void sub_080161F0(void);
extern void sub_08016678(void *);
extern void sub_080C31E0(void *, s32);

/* Actor teardown: release the optional +0x28 entry from the main object list
 * and the +0x2C and +0x48 entries from the secondary list, detach the work
 * object, then hand over to the update callback. */
void sub_0804D744(void *arg0) {
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    if (*(s32 *)(work + 0x28) != 0) {
        sub_080161F0();
    }
    if (*(s32 *)(work + 0x2C) != 0) {
        sub_08015974();
    }
    if (*(s32 *)(work + 0x48) != 0) {
        sub_08015974();
    }
    sub_08016678(arg0);
    sub_080C31E0(arg0, *(s32 *)(work + 0x24));
}
