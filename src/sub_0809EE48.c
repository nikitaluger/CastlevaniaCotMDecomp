void sub_08011368(void *, void *, s32, s32);
void sub_080C31E4(void *, void *, u32);

/* Shrinks the sprite's X/Y scale by 8 per frame; once this step's progress
 * counter passes 15 it restores the scale to 1.0, plays animation 9, flags the
 * work object's linked entry and moves on to the next script step. */
void sub_0809EE48(void *arg0) {
    void *sprite;
    void *work;
    void *animator;
    u32 scale;
    u32 *stepTable;

    sprite = *(void **)((u8 *)arg0 + 0x38);
    work = *(void **)((u8 *)arg0 + 0x3C);
    animator = (u8 *)work + 0x34;

    scale = *(u16 *)((u8 *)sprite + 4) - 8;
    *(u16 *)((u8 *)sprite + 4) = scale;
    *(u16 *)((u8 *)sprite + 6) = scale;

    if (*(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) > 0x0F) {
        u16 fullScale;
        sub_08011368(sprite, animator, 9, 0);
        fullScale = 0x100;
        *(u16 *)((u8 *)sprite + 4) = fullScale;
        *(u16 *)((u8 *)sprite + 6) = fullScale;
        *(u8 *)(*(u32 *)((u8 *)work + 0x28) + 1) = 1;
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = 0;
        stepTable = (u32 *)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *stepTable);
    }
}
