struct S_02025FF0 { u8 _0[0x1870]; u32 p; };
extern struct S_02025FF0 gMainWorkspace;
extern void *sub_0805FAEC(void *, s32);

struct S_70 { u8 pad[0x70]; u8 b; };

/* Spawn a type-0x1AF object under the scene root, store the two given values in
 * it and clear its byte at +0x70; returns it, or NULL if none was free. */
void *sub_080B0934(s32 param0, s32 param1) {
    void *obj = sub_0805FAEC((void *)gMainWorkspace.p, 0x1AF);
    if (obj == NULL) return NULL;
    *(s32 *)((u8 *)obj + 0x4C) = param0;
    *(s32 *)((u8 *)obj + 0x5C) = param1;
    ((struct S_70 *)obj)->b = 0;
    return obj;
}
