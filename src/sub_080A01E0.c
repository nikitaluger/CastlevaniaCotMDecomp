/* Place the effect object `obj` at `anchor`'s position, with its Y shifted by
 * yOffset and 32 px (0x200000 in 16.16 fixed point) upward. No-op if obj is NULL. */
void sub_080A01E0(void *obj, void *anchor, s32 yOffset) {
    if (obj != 0) {
        *(u32 *)((u8 *)obj + 0x4C) = *(u32 *)((u8 *)anchor + 0x08);
        {
            s32 tmp = yOffset + 0xFFE00000;
            *(u32 *)((u8 *)obj + 0x5C) = *(u32 *)((u8 *)anchor + 0x0C) + tmp;
        }
    }
}
