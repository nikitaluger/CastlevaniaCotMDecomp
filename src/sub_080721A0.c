extern void sub_080C31E4(void *a, void *b, s32 c);
extern s32 D_08671BB0[];

/*
 * Lowers the sprite's +4 halfword attribute by 0x80; once it reaches 0x80,
 * clears the script counter and advances the command script.
 */
void sub_080721A0(void *entity) {
    u8 *obj = (u8 *)entity;
    u16 *sprite = *(u16 **)(obj + 0x38);

    sprite[2] -= 0x80;
    if ((s16)sprite[2] == 0x80) {
        *(u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *scriptTable = D_08671BB0;
            sub_080C31E4(obj + 0x18, obj + 0x22, *scriptTable);
        }
    }
}
