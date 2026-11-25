void sub_080113A8(s32, void *);
void sub_0801165C(void *, s32);

/* Step the entity's animation and integrate its motion; once the current script
 * step counter reaches 0x50, set bit 0 of the work record. */
void sub_08052C40(void *arg0) {
    s32 sprite = *(s32 *)((u8 *)arg0 + 0x38);
    u16 *work = *(u16 **)((u8 *)arg0 + 0x3C);
    u16 one = 1;
    sub_080113A8(sprite, (u8 *)work + 0x34);
    sub_0801165C(work, 0);
    if (*(u8 *)(*(s16 *)((u8 *)arg0 + 0x22) * 2 + (u8 *)arg0 + 0x19) == 0x50) {
        *work = one | *work;
    }
}
