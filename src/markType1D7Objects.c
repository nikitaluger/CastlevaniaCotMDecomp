struct S_02025FF0_1870 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0_1870 gMainWorkspace;

/* Walk the object list rooted in the shared scene state and set bit 0 in the
 * flag word of every node whose type is 0x1D7. */
void markType1D7Objects(void)
{
    void *unused;
    s8 *root;
    void *node;
    u16 *flags;
    root = (s8 *)(void *)gMainWorkspace.v;
    node = *((void **)(root + 0x30));
    if (node != NULL) {
        do {
            do {
                if ((*((s16 *)(((s8 *)node) + 0))) == 0x1D7) {
                    if (unused) {
                        flags = *((u16 **)(((s8 *)node) + 0x3C));
                        *flags |= 1;
                    } else {
                        flags = *((u16 **)(((s8 *)node) + 0x3C));
                        *flags |= 1;
                    }
                }
                if (1) { }
            } while (0);
            node = *((void **)(((s8 *)node) + 0x2C));
        } while (NULL != node);
    }
}
