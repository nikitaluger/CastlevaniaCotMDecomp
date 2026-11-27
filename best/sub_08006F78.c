extern void updateObjectTree(void *);
extern u8 gMainWorkspace[];

void sub_08006F78(void *arg0)
{
    u8 *ws = (u8 *)gMainWorkspace;
    u32 *flags = (u32 *)(ws + 0x14A8);
    u32 f = *flags;

    if (!(f & 0x40000000)) {
        updateObjectTree(*(void **)(ws + 0x18F0));
        *(u32 *)(ws + 0x1894) += 1;
    }
    if (!(f & 0x20000000)) {
        updateObjectTree(*(void **)(ws + 0x18D4));
    }
    if (!(f & 0x10000000)) {
        updateObjectTree(*(void **)(ws + 0x18BC));
    }
    if (!(f & 0x08000000)) {
        updateObjectTree(*(void **)(ws + 0x18DC));
    }
    if (!(f & 0x04000000)) {
        /* placeholder */
    }
}
