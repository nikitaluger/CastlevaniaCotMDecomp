struct S_02025FF0 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0 gMainWorkspace;
extern void *sub_0805FAEC(s32, s32);
struct S_E38 { u8 pad[0x4C]; u8 b[9]; };

/* Spawn a type-0x18F object from the shared pool, store the given value in its
 * first parameter byte and clear the last one; returns the object, or NULL if
 * none was free. */
void *sub_080A2E38(s32 param) {
    void *obj = sub_0805FAEC(gMainWorkspace.v, 0x18F);
    if (obj == NULL) return NULL;
    ((struct S_E38 *)obj)->b[0] = param;
    ((struct S_E38 *)obj)->b[8] = 0;
    return obj;
}
