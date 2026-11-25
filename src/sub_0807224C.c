void sub_080C31E0(void *, s32);

/* Spin the sprite's 1/1024-turn rotation phase by 0x40 each frame; once it
 * wraps past a full turn (0x400 units), run the entity's update callback. */
void sub_0807224C(void *entity) {
    void *sprite = *(void **)((u8 *)entity + 0x38);
    s32 angle = *(u16 *)((u8 *)sprite + 6);
    angle += 0x40;
    *(u16 *)((u8 *)sprite + 6) = angle;
    if ((angle << 16) > 0x03FF0000) {
        sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
    }
}
