void sub_080C31E0(void *, void *);

/* Initialize the linked object's sprite for the fade: set +4 to 0x400 and
 * +6 to 0x80, flag 0x800 on self, reset the step index and install
 * sub_0809F38C as the next handler. Without a sprite, call the callback at
 * +0x24 instead. */
void sub_0809F348(void *self)
{
    void *linked = *(void **)((u8 *)self + 0x28);
    void *sprite = *(void **)((u8 *)linked + 0x38);
    if (sprite == 0) {
        sub_080C31E0(self, *(void **)((u8 *)self + 0x24));
        return;
    }
    do {
        u32 zero = 0;
        u16 value = 0x400;
        *(u16 *)((u8 *)sprite + 4) = value;
        linked = (void *)(*(vu32 *)((u8 *)self + 0x28));
        sprite = *(void **)((u8 *)linked + 0x38);
        value = 0x80;
        *(u16 *)((u8 *)sprite + 6) = value;
        value = (u16)(*(u16 *)((u8 *)self + 2) | 0x800);
        *(u16 *)((u8 *)self + 2) = value;
        *(u16 *)((u8 *)self + 0x22) = (u16)zero;
        *(u32 *)((u8 *)self + 0x14) = 0x0809F38D;
    } while (0);
}
