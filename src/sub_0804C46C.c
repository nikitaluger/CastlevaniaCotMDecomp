extern u32 D_0866E4B8[];
extern void setAnimationFrame(void *, void *, s32, s32);

/* Step the actor's script on the 0x0866E4B8 command table: switch to animation
 * 0x0A, advance the script index and the current step's progress byte, call the
 * step's handler directly, then restore the index. */
void sub_0804C46C(void *actor)
{
    u8 *self = (u8 *)actor;
    s16 index;
    u8 command;

    setAnimationFrame(*(void **)(self + 0x38), *(u8 **)(self + 0x3C) + 0x34, 0x0A, 0);

    *(u32 *)(self + 0x14) = (u32)D_0866E4B8;
    *(u16 *)(self + 0x22) += 1;

    index = *(s16 *)(self + 0x22);
    *(u8 *)(self + 0x19 + index * 2) += 1;

    index = *(s16 *)(self + 0x22);
    {
        s32 offset = index * 2;
        u8 *step = self;
        step += 0x18;
        step = step + offset;
        command = *step;
    }

    ((void (**)(void *))*(u32 *)(self + 0x14))[command](actor);

    *(u16 *)(self + 0x22) -= 1;
}
