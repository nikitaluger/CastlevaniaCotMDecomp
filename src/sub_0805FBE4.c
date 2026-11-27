void *createChildObject(void *parent, s32 kind);

/* Allocate a kind-0x14 effect object as a child of `parent`, mark it inactive
 * and store its 16-bit parameter at +0x44; NULL if allocation failed. */
void *sub_0805FBE4(void *parent, u16 param) {
    void *obj = createChildObject(parent, 0x14);
    if (obj == NULL) {
        return NULL;
    }
    ((u8 *)obj)[0x3C] = 0;
    ((u16 *)((u8 *)obj + 0x3C))[4] = param;
    return obj;
}
