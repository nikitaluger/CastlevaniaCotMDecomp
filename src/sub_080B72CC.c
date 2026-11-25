extern s32 sub_080B7298(void *);

/* If the held object's flag bit 0 is set, clear it and spawn a landing effect
 * at this entity's recorded position. */
void sub_080B72CC(void *self)
{
    void *held = *(void **)((u8 *)*(void **)((u8 *)self + 0x3C) + 0x28);
    if (1 & *(u16 *)((u8 *)held + 0x14)) {
        *(u16 *)((u8 *)held + 0x14) = (u16)(0xFFFE & *(u16 *)((u8 *)held + 0x14));
        sub_080B7298(self);
    }
}
