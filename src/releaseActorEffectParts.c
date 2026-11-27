struct S_02025FF0_1780 { u8 pad[0x1780]; s32 arr[1]; };
extern struct S_02025FF0_1780 gMainWorkspace;
extern void unlinkAndFreeObject(void);
extern void sub_080C31E0(void *, s32);

/* Release each of the five sub-object handles this object holds, clear its
 * global slot, then run the cleanup callback. */
void releaseActorEffectParts(void *obj) {
    u8 *parts = *(u8 **)((u8 *)obj + 0x6C) + 4;
    u8 *partsCopy = parts;
    if (*(s32 *)(parts + 0x2C)) unlinkAndFreeObject();
    if (*(s32 *)(parts + 0x30)) unlinkAndFreeObject();
    if (*(s32 *)(parts + 0x34)) unlinkAndFreeObject();
    if (*(s32 *)(parts + 0x38)) unlinkAndFreeObject();
    if (*(s32 *)(parts + 0x3C)) unlinkAndFreeObject();
    gMainWorkspace.arr[*(s32 *)((u8 *)obj + 0xAC)] = 0;
    sub_080C31E0(obj, *(s32 *)(partsCopy + 0x18));
}
