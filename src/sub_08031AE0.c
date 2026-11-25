extern void sub_08015974(void);
extern void sub_080161F0(void);
extern void sub_08016678(void *);
extern void sub_080C31E0(void *, s32);

/* Actor teardown: frees the optional list entries attached to its work block,
 * detaches the work object, then invokes its completion callback. */
void sub_08031AE0(void *self) {
    u8 *work;

    work = *(u8 **)((u8 *)self + 0x3C);
    if (*(s32 *)(work + 0x28) != 0) {
        sub_080161F0();
    }
    if (*(s32 *)(work + 0x2C) != 0) {
        sub_08015974();
    }
    if (*(s32 *)(work + 0x48) != 0) {
        sub_08015974();
    }
    sub_08016678(self);
    sub_080C31E0(self, *(s32 *)(work + 0x24));
}
