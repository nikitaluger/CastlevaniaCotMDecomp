struct S_02025FF0_1870 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0_1870 gMainWorkspace;

/* Set bit 0 of the animation flags on every list node of type 0x1D6, walking
 * both the object's list at +0x30 and the global list rooted at gMainWorkspace.v. */
void sub_080BE644(void *arg0)
{
    void *unused;
    void *node;
    s8 *listRoot;
    u16 *animFlags;
    node = *((void **)((u8 *)arg0 + 0x30));
    if (node != NULL) {
        do {
            if ((*((s16 *)(((s8 *)node) + 0))) == 0x1D6) {
                animFlags = *((u16 **)(((s8 *)node) + 0x3C));
                *animFlags |= 1;
            }
            node = *((void **)(((s8 *)node) + 0x2C));
        } while (NULL != node);
    }
    {
        listRoot = (s8 *)(void *)gMainWorkspace.v;
        node = *((void **)(listRoot + 0x30));
        if (node != NULL) {
            do {
                if ((*((s16 *)(((s8 *)node) + 0))) == 0x1D6) {
                    if (unused) {
                        animFlags = *((u16 **)(((s8 *)node) + 0x3C));
                        *animFlags |= 1;
                    } else {
                        animFlags = *((u16 **)(((s8 *)node) + 0x3C));
                        *animFlags |= 1;
                    }
                }
                node = *((void **)(((s8 *)node) + 0x2C));
            } while (NULL != node);
        }
    }
}
