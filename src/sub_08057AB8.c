void sub_0808DBB4(s32, s32, s32);
void sub_08005E80(s32);
void sub_080C31E0(void *, s32);
extern u32 D_080CFD48[];

/* Trail step: spawn a variant-0 falling effect at the work object's position
 * with the vertical offset selected by the index at +0x7C; the first step also
 * plays sound 0x88, then the object's update callback runs. */
void sub_08057AB8(void *entity)
{
    u8 *obj = (u8 *)entity;
    u8 *work = *(u8 **)(obj + 0x3C);

    sub_0808DBB4(*(s32 *)work, *(s32 *)(work + 4) + D_080CFD48[*(u8 *)(obj + 0x7C)], 8);

    if (*(u8 *)(obj + 0x7C) == 0)
        sub_08005E80(0x88);

    sub_080C31E0(entity, *(s32 *)(obj + 0x24));
}
