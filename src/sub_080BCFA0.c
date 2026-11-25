/* Tear-down for the large (0x32-slot) variant: free its effect slots and its
 * extra effect object, release its sprite, free the linked object, stop its
 * motion and run the object's stored callback. */
extern void sub_08011650(s32);
extern void sub_08015974(void *);
extern void sub_080161F0(void *);
extern void sub_08016678(void *);
extern void sub_080C31E0(void *, s32);

void sub_080BCFA0(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 sprite;
    void *work;
    u8 *slot;
    u32 i;

    sprite = *(s32 *)(self + 0x38);
    work = *(void **)(self + 0x3C);
    slot = (u8 *)work + 0x48;
    if (*(s32 *)((u8 *)work + 0x28) != 0) sub_080161F0(*(void **)((u8 *)work + 0x28));
    i = 0;
    do {
        if (*(s32 *)slot != 0) sub_080161F0(*(void **)slot);
        slot += 4;
        i += 1;
    } while (i <= 0x31U);
    sub_08011650(sprite);
    if (*(s32 *)((u8 *)work + 0x2C) != 0) sub_08015974(*(void **)((u8 *)work + 0x2C));
    sub_08016678(arg0);
    sub_080C31E0(arg0, *(s32 *)((u8 *)work + 0x24));
}
