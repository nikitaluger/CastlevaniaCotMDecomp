extern void unlinkAndFreeObject(void);
extern void sub_080C050C(s32);
extern void sub_080C31E0(void *, s32);

/* Cleanup handler: if this object's animation still holds a global-list link,
 * unlink and free it, play sound 0x1BE, then dispatch the handler at +8. */
void sub_08090484(void *self) {
    void *anim;

    anim = *(void **)((u8 *)self + 0x3C);
    if (*(s32 *)((u8 *)anim + 4) != 0) {
        unlinkAndFreeObject();
    }
    sub_080C050C(0x1BE);
    sub_080C31E0(self, *(s32 *)((u8 *)anim + 8));
}
