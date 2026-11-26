extern u32 D_0866E898[];
extern void setAnimationFrame(void *, void *, s32, s32);

/* Run one script command out of line: start animation 0x14, swap in the
 * command table at D_0866E898, temporarily advance the step and its progress
 * byte, call the new step's handler directly, then restore the step index. */
void sub_0805A764(void *self)
{
    u8 *actor = (u8 *)self;
    s16 step;
    u8 command;

    setAnimationFrame(*(void **)(actor + 0x38), *(u8 **)(actor + 0x3C) + 0x34, 0x14, 1);

    *(u32 *)(actor + 0x14) = (u32)D_0866E898;
    *(u16 *)(actor + 0x22) += 1;

    step = *(s16 *)(actor + 0x22);
    *(u8 *)(actor + 0x19 + step * 2) += 1;

    step = *(s16 *)(actor + 0x22);
    {
        s32 offset = step * 2;
        u8 *entry = actor;
        entry += 0x18;
        entry = entry + offset;
        command = *entry;
    }

    ((void (**)(void *))*(u32 *)(actor + 0x14))[command](self);

    *(u16 *)(actor + 0x22) -= 1;
}
