struct S_02025FF0_1870 { u8 _0x000[0x1870]; u32 obj; };
extern struct S_02025FF0_1870 D_02025FF0;

/* Walk the entity list at obj+0x30 (next link at +0x2C); for every entry whose
 * type (s16 at +0x00) is 0x195, set bit 0 of the u16 flags at entry+0x3C. */
void sub_080A56D8(void)
{
    void *unused_r5;
    s8 *base;
    void *entry;
    u16 *flags;

    base = (s8 *)(void *)D_02025FF0.obj;
    entry = *((void **)(base + 0x30));
    if (entry != NULL) {
        do {
            do {
                if ((*((s16 *)(((s8 *)entry) + 0))) == 0x195) {
                    if (unused_r5) {
                        flags = *((u16 **)(((s8 *)entry) + 0x3C));
                        *flags |= 1;
                    } else {
                        flags = *((u16 **)(((s8 *)entry) + 0x3C));
                        *flags |= 1;
                    }
                }
                if (1) { }
            } while (0);
            entry = *((void **)(((s8 *)entry) + 0x2C));
        } while (NULL != entry);
    }
}
