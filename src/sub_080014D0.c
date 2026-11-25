extern void *sub_0800141C(s32);
extern void sub_08002D7C(void);
extern u16 D_0202574E[];

// Allocates an object of `type`, appends it to the parent's child list (starting
// one if empty), installs the child-list update callback and bumps its counter.
void *sub_080014D0(void *parent, s32 type)
{
    void *obj;
    s32 typeIndex;
    void *firstChild;
    void *child;
    void *objCopy;
    u32 ffff;

    typeIndex = type;
    obj = sub_0800141C(type);
    if (obj != NULL)
    {
        typeIndex &= 0x3FFF;
        ffff = 0xFFFF;
        do {
            *((u16 *)(((u8 *)obj) + 0x22)) = ffff;
            if (parent != NULL) {
                *((void **)(((u8 *)obj) + 0x28)) = parent;
                firstChild = *((void **)(((u8 *)parent) + 0x30));
                if (firstChild != NULL) {
                    child = firstChild;
                    while ((*((void **)(((u8 *)child) + 0x2C))) != NULL) {
                        child = *((void **)(((u8 *)child) + 0x2C));
                    }
                    *((void **)(((u8 *)child) + 0x2C)) = obj;
                } else {
                    *((void **)(((u8 *)parent) + 0x30)) = obj;
                }
            }
        } while (0);
        *((void **)(((u8 *)(objCopy = obj)) + 0x24)) = (void *)sub_08002D7C;
        D_0202574E[typeIndex]++;
    }
    return obj;
}
