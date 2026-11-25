extern s32 sub_08014938(s32);
extern s32 sub_08014990(void *);
extern void sub_080C31E4(void *, void *, u32);

struct SpriteAttrs { u8 pad[2]; u16 flags; };

/* Script step: face the sprite toward the player at step 3, set a movement
 * speed from the facing, then count the step down and reset it on expiry. */
void sub_0801ACFC(void *actor) {
    u8 *self = (u8 *)actor;
    u8 *sprite = *(u8 **)(self + 0x38);
    int zeroWord;
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animState = work + 0x48;
    u8 zeroByte;
    s32 remaining;
    s32 *scriptTable;
    if (*(s16 *)(animState + 0x16) == 3) {
        {
            struct SpriteAttrs *attrs = (struct SpriteAttrs *)sprite;
            if (sub_08014938(*(s32 *)(work + 8)) > 0)
                attrs->flags |= 0x10;
            else
                attrs->flags &= 0xFFEF;
        }
    }
    zeroWord = 0;
    if (sub_08014990(sprite) > zeroWord)
        *(s32 *)(work + 0x10) = 0xC0 << 11;
    else
        *(s32 *)(work + 0x10) = (s32)0xFFFA0000;
    remaining = *(u16 *)(animState + 0x16) - 1;
    zeroByte = zeroWord;
    *(u16 *)(animState + 0x16) = remaining;
    if ((remaining << 16) < 0) {
        *(u16 *)(animState + 0x16) = 5;
        *(s32 *)(work + 0x14) = zeroByte;
        *(s32 *)(work + 0x10) = zeroByte;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, (u32)*scriptTable);
    }
}
