extern s32 sub_0808DBB4(s32 x, s32 y, s32 kind);
extern s32 sub_0808DBF8(s32 x, s32 y, s32 kind);
extern s32 spawnVariant2Effect(s32 x, s32 y, s32 kind);
extern void sub_080C31E0(void *actor, s32 handler);

/* Steps a falling projectile: optionally spawns a trail particle of the selected
 * kind, integrates gravity into its velocity/position, then clamps the fall limit
 * or switches state once it is halfway down to the target height. */
void sub_0808E6F4(void *arg0)
{
    s8 *pY;
    s32 fallLimit;
    s32 currentY;

    if (!(7 & (*((u16 *) (((s8 *) arg0) + 0x22)))))
    {
        switch (*((u8 *) (((s8 *) arg0) + 0x94)))
        {
          case 0:
            sub_0808DBB4(*((s32 *) (((s8 *) arg0) + 0x4C)), *((s32 *) (((s8 *) arg0) + 0x9C)), 8);
            break;
          case 1:
            sub_0808DBF8(*((s32 *) (((s8 *) arg0) + 0x4C)), *((s32 *) (((s8 *) arg0) + 0x9C)), 8);
            break;
          case 2:
            spawnVariant2Effect(*((s32 *) (((s8 *) arg0) + 0x4C)), *((s32 *) (((s8 *) arg0) + 0x9C)), 8);
            break;
        }
    }
    *((s32 *) (((s8 *) arg0) + 0x4C)) = (s32) ((*((s32 *) (((s8 *) arg0) + 0x4C))) + (*((s32 *) (((s8 *) arg0) + 0x6C))));
    *((s32 *) (((s8 *) arg0) + 0x9C)) = (s32) ((*((s32 *) (((s8 *) arg0) + 0x9C))) + (*((s32 *) (((s8 *) arg0) + 0x7C))));
    *((s32 *) (((s8 *) arg0) + 0x7C)) = (s32) ((*((s32 *) (((s8 *) arg0) + 0x7C))) + 0x16C1);
    fallLimit = *((s32 *) (((s8 *) arg0) + 0xAC));
    pY = ((s8 *) arg0) + 0x9C;
    currentY = *((s32 *) pY);
    if (fallLimit > currentY)
    {
        *((s32 *) (((s8 *) arg0) + 0xAC)) = currentY;
        return;
    }
    if (currentY > ((s32) (fallLimit + (((s32) ((*((s32 *) (((s8 *) arg0) + 0x5C))) - fallLimit)) >> 1))))
    {
        sub_080C31E0(arg0, *((s32 *) (((s8 *) arg0) + 0x24)));
    }
}
