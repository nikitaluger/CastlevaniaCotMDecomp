s32 sub_08011368(s32, s32, s32, s32);
void sub_08014668(s32, s32);

/* Play animation 0xC; when the entity's turn flag is set, reverse its
 * horizontal velocity, then update the sprite's facing from the velocity. */
void sub_08058890(void *entity) {
    s32 sprite;
    void *work;

    sprite = *(s32 *)((u8 *)entity + 0x38);
    work = *(void **)((u8 *)entity + 0x3C);
    sub_08011368(sprite, work + 0x34, 0xC, 1);
    if (1 & *(u16 *)((u8 *)work + 2)) {
        *(s32 *)((u8 *)work + 0x10) = (s32) (0 - *(s32 *)((u8 *)work + 0x10));
    }
    sub_08014668(sprite, *(s32 *)((u8 *)work + 0x10));
}
