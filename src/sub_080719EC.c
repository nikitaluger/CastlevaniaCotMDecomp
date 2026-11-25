extern s32 sub_0806E114(s32, s32, s32, s32);

/* Spawn a kind-8 effect at `position` when the entity's pending flag is set
 * and not already fired, then clear the flag. */
void sub_080719EC(void *source, void *entity, void *position)
{
    if ((1 & (*((u16 *) (((s8 *) (*((void **) (((s8 *) entity) + 0x3C)))) + 0x14)))) && (!(2 & (*((u16 *) (((s8 *) (*((void **) (((s8 *) entity) + 0x3C)))) + 0x14))))))
    {
        sub_0806E114(*((s32 *) (((s8 *) source) + 0x28)), 8, *((s32 *) (((s8 *) position) + 0)), *((s32 *) (((s8 *) position) + 4)));
    }
    *((u16 *) (((s8 *) (*((void **) (((s8 *) entity) + 0x3C)))) + 0x14)) = 0U;
}
