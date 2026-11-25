extern u32 D_02025FF0[];
extern u32 D_08671BB0;

void sub_08003740(void *, void *);
void sub_0806D588(void *, void *);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, u32);

/* Refresh an entity's display: redraw it from its sprite in the normal mode,
 * or update only its render object's screen position in the special mode. */
void sub_0808A2EC(void *entity)
{
    void *pos = *(u8 **)((u8 *)entity + 0x6C) + 4;
    void *screenObj = *(void **)((u8 *)entity + 0x38);

    if (D_02025FF0[4] == 0)
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
    else
        sub_0806D588(screenObj, pos);
}
