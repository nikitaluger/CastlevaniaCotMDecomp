s32 sub_08014848(s32, s32, s32, s32, s32, s32);
s32 sub_080C31E0(void *, s32);
u8 sub_080C389C(u8, s32);

/* Falling-particle emitter step (raised variant): every 6th tick spawn one
 * particle of kind 1 at the +0x48 sub-object of the motion body, using that
 * sub-object's +0xC/+0x10 coordinates with angles 0xC0000/0x10000; once the
 * step phase byte passes 0x3C, switch the entity to the next script handler
 * at +0x24. */
void sub_0805A800(void *entity)
{
    void *motion;

    motion = *(s32 *) ((u8 *) entity + 0x3C) + 0x48;
    if (sub_080C389C(*(u8 *) ((u8 *) entity + *(s16 *) ((u8 *) entity + 0x22) * 2 + 0x19), 6) == 1) {
        sub_08014848(1, 1, *(s32 *) ((u8 *) motion + 0xC), *(s32 *) ((u8 *) motion + 0x10), 0xC0000, 0x10000);
    }
    if ((u32) *(u8 *) ((u8 *) entity + *(s16 *) ((u8 *) entity + 0x22) * 2 + 0x19) > 0x3C) {
        sub_080C31E0(entity, *(s32 *) ((u8 *) entity + 0x24));
    }
}
