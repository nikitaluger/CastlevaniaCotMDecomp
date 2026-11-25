extern s32 sub_080148AC(void *, s32);

/* Add `offset` to the owner's base X field (owner+8), negating the offset when
 * the target is facing the other way. */
s32 sub_080148C0(void *owner, void *target, s32 offset) {
    return *(s32 *)((u8 *)owner + 8) + sub_080148AC(target, offset);
}
