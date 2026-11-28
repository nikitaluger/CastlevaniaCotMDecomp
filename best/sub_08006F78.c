extern void updateObjectTree(void *);
extern u8 gMainWorkspace[];

void sub_08006F78(void *arg0)
{
    u8 *ws;
    u32 *flags;
    u8 *temp;
    temp = (u8 *)gMainWorkspace;
    ws = temp;
    flags = (u32 *)(ws + 0x14A8);
    if (!((*flags) & 0x40000000)) {
        do { updateObjectTree(*(void **)(ws + 0x18F0)); } while (0);
        *(u32 *)(ws + 0x1894) += 1;
    }
    if (!((*flags) & 0x20000000)) {
        do { updateObjectTree(*(void **)(ws + 0x18D4)); } while (0);
    }
    if (!((*flags) & 0x10000000)) {
        do { updateObjectTree(*(void **)(ws + 0x18BC)); } while (0);
    }
    if (!((*flags) & 0x08000000)) {
        do { updateObjectTree(*(void **)(ws + 0x18DC)); } while (0);
    }
    if (!((*flags) & 0x04000000)) {
        /* placeholder */
    }
}
