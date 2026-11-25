s32 sub_08014848(s32, s32, s32, s32, s32, s32);
s32 sub_080C31E0(void *, s32);
u8 sub_080C389C(u8, s32);   /* unsigned remainder helper: value % divisor */

/* Falling-particle emitter step: every sixth tick spawn one particle of kind 1
 * just above the motion body (angles 0xC0000/0x100000); once the step phase
 * byte passes 0x3C, switch the entity to the next script handler at +0x24. */
void sub_0805309C(void *entity)
{
    void *motion;

    motion = *(void **) ((u8 *) entity + 0x3C);
    if (sub_080C389C(*(u8 *) ((u8 *) entity + *(s16 *) ((u8 *) entity + 0x22) * 2 + 0x19), 6) == 1) {
        sub_08014848(1, 1, *(s32 *) ((u8 *) motion + 8), *(s32 *) ((u8 *) motion + 0xC) + 0xFFF60000, 0xC0000, 0x100000);
    }
    if ((u32) *(u8 *) ((u8 *) entity + *(s16 *) ((u8 *) entity + 0x22) * 2 + 0x19) > 0x3C) {
        sub_080C31E0(entity, *(s32 *) ((u8 *) entity + 0x24));
    }
}
