void sub_080C31E0(void *entity, void *release);

/* A sprite's screen-space position, in 16.16 fixed point. */
struct SpritePos {
    u8 pad[0x14];
    s32 x;
    s32 y;
};

/*
 * Releases the entity through its +0x24 callback once its sprite has left the
 * extended screen area (x outside [-64, 312) or y beyond 224 pixels), so
 * off-screen entities stop updating.
 */
void sub_0806D330(void *entity, void *sprite) {
    struct SpritePos *pos = (struct SpritePos *)sprite;

    if (((u32)(pos->x + 0x400000) > 0x01780000u) ||
        (pos->y > 0xE00000))
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
}
