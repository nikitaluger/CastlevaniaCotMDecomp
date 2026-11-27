extern u32 D_02027860;
void allocWorkSlot(void *, s32, s32, s32);
s32 spawnBudgetedEffect(s32, s32);
void sub_080C31E0(void *, s32);
void sub_080AFFE8(void);

/* Spawn a four-part entity: create a parent object at self+0x3C, then allocate
 * four child objects (id 0x1B1) into its pointer array at +0x48.  Each child is
 * tagged with its part index and a variant byte from self+0x4C.  Finally install
 * sub_080AFFE8 as the update handler (it arranges the parts) and advance state. */
void sub_080AFF54(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 **childList;
    u8 **dst;
    u8 *child;
    u8 *variantByte;
    u32 i;
    u32 flags;

    allocWorkSlot(self, 0, 0x58, 0);
    childList = *(u8 ***)(self + 0x3C);
    if (childList == 0) {
        sub_080C31E0(self, *(s32 *)(self + 0x24));
        return;
    }
    childList = (u8 **)((u8 *)childList + 0x48);
    *(u8 ***)(self + 0x8C) = childList;
    i = 0;
    variantByte = self + 0x4C;
    {
        u32 base = (u32)&D_02027860;
        dst = childList;
        do {
            child = (u8 *)spawnBudgetedEffect(*(s32 *)base, 0x1B1);
            *dst = child;
            child[0x4C] = 0;
            ((u8 *)*dst)[0x50] = (u8)i;
            {
                u8 *part = *dst++;
                u8 variant = *variantByte;
                part[0x5C] = variant;
            }
            i++;
        } while (i <= 3);
    }
    flags = (u16)(0x1000 | *(u16 *)(self + 0x02));
    *(u16 *)(self + 0x02) = flags;
    *(u16 *)(self + 0x02) |= 0x800;
    *(void **)(self + 0x14) = (void *)sub_080AFFE8;
    *(u16 *)(self + 0x22) = 1;
    sub_080C31E0(self, (s32)(u32)sub_080AFFE8);
}
