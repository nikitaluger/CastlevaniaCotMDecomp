struct S_02025FF0_14B8 { u8 _0[0x14B8]; u32 activeFlag; };
extern struct S_02025FF0_14B8 gMainWorkspace;
void sub_0806D588(void *, void *);
void sub_080C31E0(void *, void *);

/* Actor step: while the +0x14B8 global flag is set, dispatch the entity's
 * script handler at +0x24; otherwise copy the mover's position to the sprite. */
void sub_080889F4(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *pos = *(u8 **)(self + 0x6C) + 4;
    u8 *sprite = *(u8 **)(self + 0x38);
    if (gMainWorkspace.activeFlag != 0) {
        sub_080C31E0(self, *(void **)(self + 0x24));
    } else {
        sub_0806D588(sprite, pos);
    }
}
