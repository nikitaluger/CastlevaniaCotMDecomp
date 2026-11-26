extern s32 signOf(s32); /* sign(shared target X - x) */
struct Sprite { u8 pad[2]; u16 flags; };

/* Set or clear the sprite's X-facing bit (+2, bit 0x10) according to which
 * side of the given X coordinate the shared target X lies on. */
void sub_080148D8(struct Sprite *sprite, s32 x)
{
    if (signOf(x) > 0)
        sprite->flags |= 0x10;
    else
        sprite->flags &= 0xFFEF;
}
