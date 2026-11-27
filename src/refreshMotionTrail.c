extern void sub_080A8374(s32, s32, s32, s32, s32, s32, void *);

/* When the script's cached pose byte (behav+0x4C) disagrees with the low bit of
 * its state word (behav+0x9C), rebuild the entity's motion trail by feeding
 * its cached direction/motion components (entity+0xA8..0xBC) to the builder. */
void refreshMotionTrail(u8 *behav, u8 *entity)
{
    if (*(behav + 0x4C) != (*((s32 *)(behav + 0x9C)) & 1))
    {
        sub_080A8374(*((s32 *)(entity + 0xA8)), *((s32 *)(entity + 0xAC)),
                     *((s32 *)(entity + 0xB0)), *((s32 *)(entity + 0xB4)),
                     *((s32 *)(entity + 0xB8)), *((s32 *)(entity + 0xBC)), entity);
    }
}
