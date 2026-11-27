extern void sub_080C31E4(void *a, void *b, s32 c);
extern s32 gScriptStepCallbackTable[];

/* Lower the sprite's +6 halfword attribute by 0x80; once it reaches 0x80, arm
 * the 0x60-frame delay on the motion state, clear the script counter and
 * advance the command script. */
void sub_080721D8(void *entity) {
    u8 *obj = (u8 *)entity;
    u8 *state = *(u8 **)(obj + 0x6C) + 4;
    u16 *sprite = *(u16 **)(obj + 0x38);
    sprite[3] -= 0x80;
    if ((s16)sprite[3] == 0x80) {
        *(u32 *)(state + 0x2C) = 0x60;
        *(u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *scriptTable = gScriptStepCallbackTable;
            sub_080C31E4(obj + 0x18, obj + 0x22, *scriptTable);
        }
    }
}
