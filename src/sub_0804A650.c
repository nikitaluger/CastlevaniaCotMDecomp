extern s32 sub_080C31E0(u16, s32);

/* Enemy attack helper: while the one-shot flag at self+0x7C is set, shift the
 * enemy's y coordinate back by 8 times the table lookup of the control angle,
 * then advance that angle by 0x200. */
void sub_0804A650(void *self, void *state, void *ctrl)
{
    s32 *table;
    if (*(u8 *)((s8 *)self + 0x7C) != 0)
    {
        table = (s32 *)0x08671BFC;
        *(s32 *)((s8 *)state + 0xC) = (s32)(*(s32 *)((s8 *)ctrl + 0) - (sub_080C31E0(*(u16 *)((s8 *)ctrl + 4), *table) * 8));
        *(u16 *)((s8 *)ctrl + 4) = (u16)(*(u16 *)((s8 *)ctrl + 4) + 0x200);
    }
}
