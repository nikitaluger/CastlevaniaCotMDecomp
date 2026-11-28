void sub_08005E80(s32);
void sub_08014414(void *);
void sub_08051D3C(void *, void *, u16, s32);
void sub_0808DBF8(s32, s32, s32);
void spawnVariant2Effect(s32, s32, s32);
void sub_080C31E0(void *, s32);

/* Update an effect object: set its display attribute, draw and advance its
 * sprite, then at specific timer values play sounds, spawn children and retire it. */
void sub_0805101C(void *self) {
    u16 *attr;
    void *body;
    u8 *body48;

    attr = *(u16 **)((u8 *)self + 0x38);
    body = *(void **)((u8 *)self + 0x3C);
    body48 = (u8 *)body + 0x48;
    if ((*(u8 *)((u8 *)self + (*(s16 *)((u8 *)self + 0x22)) * 2 + 0x19) & 2) != 0) {
        *attr = (*attr & 0xFFF) | (0xE0 << 8);
    } else {
        *attr = (*attr & 0xFFF) | ((*(u16 *)((u8 *)body + 0x22) + 8) << 12);
    }
    sub_08051D3C(self, body48 + 0x58, *(u16 *)body48, 0);
    *(u16 *)body48 = (*(u16 *)body48 + 0x12) & 0xFF;
    if ((*(u8 *)((u8 *)self + (*(s16 *)((u8 *)self + 0x22)) * 2 + 0x19) & 3) == 0) {
        sub_08005E80(0x88);
        sub_0808DBF8(*(s32 *)((u8 *)body + 8), *(s32 *)((u8 *)body + 0xC) + (0x80 << 12), 8);
    }
    if (*(u8 *)((u8 *)self + (*(s16 *)((u8 *)self + 0x22)) * 2 + 0x19) == 0xB4) {
        spawnVariant2Effect(*(s32 *)((u8 *)body + 8), *(s32 *)((u8 *)body + 0xC) + (0x80 << 12), 8);
        sub_08005E80(0x85);
        sub_08014414(self);
        sub_080C31E0(self, *(s32 *)((u8 *)self + 0x24));
    }
}
