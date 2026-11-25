extern u16 D_080CFA54[];   /* per-form sprite coordinate pairs */

/* Copy the sprite offsets for the current form into the object's OAM entry.
 * Forms 0..8 also clear an attribute bit and use the second half of the table. */
void sub_080502D0(void *form, void *sprite)
{
    u16 *coords;
    void *f = form;
    void *s = sprite;

    coords = D_080CFA54;

    if ((*(u16 *)((u8 *)f + 0x28)) <= 8) {
        u8 *attr = *(u8 **)((u8 *)s + 0x28);
        attr[1] &= 0xFA;
        coords += 0xC;
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
