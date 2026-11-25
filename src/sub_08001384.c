extern void sub_08000BE8(void *);
extern vu16 D_0202574E[];

/* Dispose an object: free each live child pointer in the table at obj+0x3C
 * (selected bit by bit from the mask at obj+0x34), then decrement the global
 * counter for the object's kind (low 14 bits of obj's first halfword) and
 * clear that word. */
void sub_08001384(void *obj) {
    u32 liveMask = 1;
    s32 child = 0;
    do {
        if (*(u16 *)((u8 *)obj + 0x34) & liveMask) {
            u8 *slot = (u8 *)obj;
            s32 slotOffset = child << 4;
            slot = slot + 0x3C;
            slot = slot + slotOffset;
            sub_08000BE8(*(void **)slot);
        }
        liveMask <<= 1;
        child++;
    } while (child < 8);

    {
        u16 kindWord = *(vu16 *)obj;
        u16 *count = (u16 *)((u8 *)D_0202574E + ((kindWord & 0x3FFF) << 1));
        *count = *count - 1;
        *(u16 *)obj = 0;
    }
}
