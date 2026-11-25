typedef s32 M2C_UNK;
M2C_UNK sub_0808DC40(s32, s32, s32);
M2C_UNK sub_080C31E0(void *, s32);

/* Script step: set the animator's pose/facing bits from the step byte or the
 * work object's facing value; once the step passes 0x17, spawn a small effect
 * at the work position and dispatch the entity's saved handler. */
void sub_08051880(u8 *self)
{
    u16 *flags = *(u16 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);

    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) & 2)
        *flags = (*flags & 0xFFF) | 0xE000;
    else
        *flags = (*flags & 0xFFF) | (u16)((*(u16 *)(work + 0x22) + 8) << 12);

    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) > 0x17)
    {
        sub_0808DC40(*(s32 *)(work + 0x08), *(s32 *)(work + 0x0C), 8);
        sub_080C31E0(self, *(s32 *)(self + 0x24));
    }
}
