void sub_080C31E4(void *, void *, s32);

/* Decrease the sprite's fade level at +4 by 0x1C; once it reaches 0x100, clamp
 * it and end this script step. Mirror the level into +6 each frame. */
void sub_0809FE54(void *self) {
    void *sprite = *(void **)((u8 *)self + 0x38);
    *(u16 *)((u8 *)sprite + 4) -= 0x1C;
    if ((s16)*(u16 *)((u8 *)sprite + 4) <= 0x100) {
        *(u16 *)((u8 *)sprite + 4) = 0x100;
        *((u8 *)self + (*(s16 *)((u8 *)self + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *stepTable = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *stepTable);
        }
    }
    *(u16 *)((u8 *)sprite + 6) = *(u16 *)((u8 *)sprite + 4);
}
