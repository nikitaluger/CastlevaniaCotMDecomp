void unlinkAndFreeObject(void);
void sub_08015974(void);
void sub_08016678(void *);
void sub_080C31E0(void *, void *);

/* Tear down an entity: unlink/free the lists its work object points to at
 * +0x28 and +0x2C, clear work+0x30, decrement the global counter at
 * gMainWorkspace+0x18BC when state+0x0A is 1, then release work+0x24. */
void sub_0805A85C(void *arg0) {
    u8 *self = arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *moveState = work + 0x48;

    if (*(u32 *)(work + 0x28) != 0) {
        unlinkAndFreeObject();
    }
    if (*(u32 *)(work + 0x2C) != 0) {
        sub_08015974();
    }
    sub_08016678(arg0);
    if (*(s16 *)(moveState + 0x0A) == 1) {
        extern u8 gMainWorkspace[];
        u8 *counter = gMainWorkspace;
        counter += 0x18BC;
        *(u16 *)counter = *(u16 *)counter - 1;
    }
    sub_080C31E0(arg0, *(void **)(work + 0x24));
}
