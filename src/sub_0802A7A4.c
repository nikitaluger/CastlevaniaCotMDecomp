extern u16 D_080CE974[];   /* per-form sprite coordinate pairs */

/* Copy the sprite offsets for the current form into the object's OAM entry.
 * Forms 0x1E..0x22 also clear two attribute bits; forms 0x0E..0x1A use the
 * second half of the coordinate table. */
void sub_0802A7A4(void *form, void *sprite)
{
    u16 *coords;
    void *f = form;
    void *s = sprite;

    coords = D_080CE974;

    if ((u16)(*(u16 *)((u8 *)f + 0x28) - 0x1E) <= 4) {
        u8 *attr = *(u8 **)((u8 *)s + 0x28);
        attr[1] &= 0xFA;
    }

    if ((u16)(*(u16 *)((u8 *)f + 0x28) - 0x0E) <= 0x0C) {
        coords += 0x10;
    }

    {
        u16 *dest;
        dest = *(u16 *volatile *)((u8 *)s + 0x28);
        dest[3] = coords[0];
        dest = *(u16 *volatile *)((u8 *)s + 0x28);
        dest[4] = coords[1];
        dest = *(u16 *volatile *)((u8 *)s + 0x28);
        dest[5] = coords[2];
        dest = *(u16 *volatile *)((u8 *)s + 0x28);
        dest[6] = coords[3];
    }
}
