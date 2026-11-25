void sub_080144D8(void *, void *);
void sub_080144FC(void *, void *);
void sub_080C31E4(void *, void *, s32);
s32 sub_08014990(void *);
void sub_080C31E0(void *, void *);

/* Run one step of an entity's phased AI: set up its view sprite, dispatch the
 * handler chosen by the current phase's state byte out of the behavior table
 * at +0x14, then place the sprite in the world. */
void sub_0803FC0C(void *self) {
    u8 *base = (u8 *)self;
    u8 stateBase;
    s32 slotOffset;
    void *sprite = *(void **)(base + 0x38);
    sub_080144D8(self, sprite);
    *(u32 *)(base + 0x14) = 0x0866E0C4;
    *(u16 *)(base + 0x22) = *(u16 *)(base + 0x22) + 1;
    ((u8 *)(base + (*(s16 *)(base + 0x22)) * 2))[0x19]++;
    slotOffset = (*(s16 *)(base + 0x22)) * 2;
    stateBase = 0x18;
    sub_080C31E0(self, (void *)((u32 *)*(u32 **)(base + 0x14))[((u8 *)(stateBase + base))[slotOffset]]);
    *(u16 *)(base + 0x22) = *(u16 *)(base + 0x22) - 1;
    sub_080144FC(self, sprite);
}
