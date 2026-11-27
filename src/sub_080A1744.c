extern void setSpriteFacingToTarget(void *, s32);

/* Set or clear an object's 0x10 flag from the distance value held in another
 * object: forward it to setSpriteFacingToTarget, then set the flag for small values and
 * clear it for large ones. */
void sub_080A1744(void *obj, void *other)
{
    s32 distance;
    setSpriteFacingToTarget(obj, *(s32 *)((u8 *)other + 8));
    distance = *(s32 *)((u8 *)other + 8);
    if (distance <= 0x47FFFF) {
        u16 flags = 0x10 | *(u16 *)((u8 *)obj + 2);
        *(u16 *)((u8 *)obj + 2) = flags;
    } else if (distance > 0x01B80000) {
        *(u16 *)((u8 *)obj + 2) &= 0xFFEF;
    }
}
