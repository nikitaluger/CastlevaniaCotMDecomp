extern void sub_080C31E4(void *, void *, s32);

/* Ease the sprite's 8.8 scale at +6 back toward 1.0 by a quarter of its
 * current value; once it reaches 0x100, clear the current script step and
 * advance the script. */
void sub_0808C728(void *arg0)
{
    u8 *sprite;
    s32 cur;
    s32 rounded;
    s32 newval;
    s16 scale;
    sprite = *(u8 **)((u8 *)arg0 + 0x38);
    cur = *(s16 *)(sprite + 6);
    rounded = cur;
    if (rounded < 0) rounded += 3;
    rounded = rounded >> 2;
    newval = *(u16 *)(sprite + 6) - rounded;
    *(u16 *)(sprite + 6) = newval;
    scale = (s16)newval;
    if (scale <= 0x100) {
        *(u16 *)(sprite + 6) = 0x100;
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = 0;
        {
            s32 *stepTable = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *stepTable);
        }
    }
}
