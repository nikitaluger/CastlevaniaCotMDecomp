/* Copy a four-halfword attribute record (a pose/hitbox entry) from `src` into
 * the object at `dst`+6, +8, +0xA and +0xC. */
void sub_08014588(void *dst, void *src) {
    *(u16 *)((s8 *)dst + 6) = (u16)*(u16 *)((s8 *)src + 0);
    *(u16 *)((s8 *)dst + 8) = (u16)*(u16 *)((s8 *)src + 2);
    *(u16 *)((s8 *)dst + 0xA) = (u16)*(u16 *)((s8 *)src + 4);
    *(u16 *)((s8 *)dst + 0xC) = (u16)*(u16 *)((s8 *)src + 6);
}
