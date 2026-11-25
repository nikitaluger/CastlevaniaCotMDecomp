void sub_080148D8(void *, s32);
s32 sub_080B9824(s32);
void sub_080C31E4(void *, void *, s32);

struct GameState10 {
    u8 _0[0x10];
    u32 state;
};
extern struct GameState10 D_02025FF0;

/* Action step: face the sprite using work+8; if entity+0x4C is set, also set
 * the sprite's highlight flag (0x40). When the object at work+0x48 reports
 * idle, enter global state 0xC, clear the script action byte and advance. */
void sub_080B8424(void *arg0) {
    u8 *entity = (u8 *)arg0;
    void *sprite = *(void **)(entity + 0x38);
    void *work = *(void **)(entity + 0x3C);
    sub_080148D8(sprite, *(s32 *)((u8 *)work + 8));
    if (*(u8 *)(entity + 0x4C) != 0) {
        u8 *flags = (u8 *)sprite + 0x2A;
        u8 newFlags = *flags | 0x40;
        *flags = newFlags;
    }
    if (sub_080B9824(*(s32 *)((u8 *)work + 0x48)) != 0) {
        s32 *scriptTable;
        D_02025FF0.state = 0xC;
        *(u8 *)(entity + (*(s16 *)(entity + 0x22) * 2) + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4(entity + 0x18, entity + 0x22, *scriptTable);
    }
}
