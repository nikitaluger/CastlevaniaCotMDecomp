struct S_02025FF0_1870 { u8 _0[0x1870]; u32 v; };
extern struct S_02025FF0_1870 gMainWorkspace;
void *sub_0805FAEC(s32, s32);

/* Spawn an effect object from the gMainWorkspace pool: copy the two source
 * offsets from the caller's body and scale its motion by a signed byte. */
void sub_080520CC(void *self, void *body, s32 scale) {
    void *fx = sub_0805FAEC((s32)gMainWorkspace.v, 0xA3 << 1);
    if (fx != NULL) {
        *(s32 *)((u8 *)fx + 0x4C) = *(s32 *)((u8 *)body + 0x80);
        *(s32 *)((u8 *)fx + 0x5C) = *(s32 *)((u8 *)body + 0xA4);
        *(s32 *)((u8 *)fx + 0x6C) = (s8)*(u8 *)((u8 *)self + 0x6C) * scale;
    }
}
