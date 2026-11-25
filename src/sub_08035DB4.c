/* Task state: the effect object this task drives lives at +0x30. */
struct Task_35DB4 {
    u8 pad[0x30];
    void *volatile effect;
};

/*
 * Copies the work object's position (+8 x, +0xC y) onto the effect object the
 * task carries at +0x30, and sets the effect's facing (+0x6C) from bit 0x10 of
 * the sprite's flags.
 */
void sub_08035DB4(void *task, void *work, void *sprite) {
    struct Task_35DB4 *t;
    u16 facing;
    void *effect;

    t = (struct Task_35DB4 *)task;
    effect = t->effect;
    if (effect) {
        *(u32 *)((u8 *)effect + 0x4C) = *(u32 *)((u8 *)work + 8);
        *(u32 *)((u8 *)t->effect + 0x5C) = *(u32 *)((u8 *)work + 0xC);
        facing = 0x10 & *(u16 *)((u8 *)sprite + 2);
        if (facing)
            *(u8 *)((u8 *)t->effect + 0x6C) = 1;
        else
            *(u8 *)((u8 *)t->effect + 0x6C) = 0;
    }
}
