void setObjectAnimation(void *, void *, s32, s32);
void sub_08011528(void *, void *);

/* Appearance switch on the entity's form (entity+0x5C): forms 1 and 2 set the
 * sprite's highlight bit (0x40 in sprite+0x2A) and start the matching animation
 * (0x11 or 0x13), any other form clears the highlight. */
void sub_080BBF9C(void *entity)
{
    u8 *sprite = *(u8 **)((u8 *)entity + 0x38);
    u8 *animator = (u8 *)*(u8 **)((u8 *)entity + 0x3C) + 0x34;
    s32 form = *(s32 *)((u8 *)entity + 0x5C);
    s32 highlight;

    switch (form) {
    case 1:
        highlight = 0x40 | *(u8 *)(sprite + 0x2A);
        *(u8 *)(sprite + 0x2A) = (u8)highlight;
        setObjectAnimation(sprite, animator, 0x11, 1);
        sub_08011528(sprite, animator);
        break;
    case 2:
        highlight = 0x40 | *(u8 *)(sprite + 0x2A);
        *(u8 *)(sprite + 0x2A) = (u8)highlight;
        setObjectAnimation(sprite, animator, 0x13, 1);
        sub_08011528(sprite, animator);
        break;
    default:
        *(u8 *)(sprite + 0x2A) = 0xBF & *(u8 *)(sprite + 0x2A);
        break;
    }
}
