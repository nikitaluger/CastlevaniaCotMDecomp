extern s32 sub_08011EE8(void *, s32, s32);
extern void _call_via_r3(void *, void *, s32, void *);
extern void sub_080C31E4(void *, void *, s32);

// Updates this entity's movement, merges collision flags and dispatches the matching step callback.
void sub_08041E48(u8 *obj)
{
    u8 *physics = *((u8 **)(obj + 0x3C));
    u8 *sprite = physics + 0x48;
    u16 combinedFlags;
    u8 zero;
    u16 moveFlags;
    u16 flag4;
    s32 *callbackTable;

    sub_08011EE8(physics, 0x16C1, 0);
    combinedFlags = *(u16 *)(sprite + 2) | *(u16 *)(physics + 2);
    zero = 0;
    *(u16 *)(sprite + 2) = combinedFlags;
    moveFlags = *(u16 *)(physics + 2);
    flag4 = (u16)(moveFlags & 4);
    if (flag4 != 0) {
        *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = zero;
        callbackTable = (s32 *)0x08671BD0;
        _call_via_r3(obj + 0x18, obj + 0x22, 0, (void *)(*callbackTable));
    } else if ((moveFlags & 1) != 0) {
        *(s32 *)(physics + 0x10) = flag4;
        *(u16 *)(sprite + 2) = flag4;
        *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = zero;
        callbackTable = (s32 *)0x08671BB0;
        sub_080C31E4(obj + 0x18, obj + 0x22, *callbackTable);
    }
}
