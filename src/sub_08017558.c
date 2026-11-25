extern s32 sub_08014938(s32);
extern s32 sub_08014990(void *);
extern void _call_via_r2(void *, void *, u32);

struct SpriteAttrs { u8 pad[2]; u16 flags; };

/* Script step: face the sprite by direction and count down a timer; on expiry
 * reset it and advance this actor's script. */
void sub_08017558(void *actor) {
    u8 *self = (u8 *)actor;
    u8 *sprite = *(u8 **)(self + 0x38);
    int zeroWord;
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animState = work + 0x48;
    u8 zeroByte;
    s32 countdown;
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
    countdown = *(u16 *)(animState + 0x16) - 1;
    zeroByte = zeroWord;
    *(u16 *)(animState + 0x16) = countdown;
    if ((countdown << 16) < 0) {
        *(u16 *)(animState + 0x16) = 5;
        *(s32 *)(work + 0x14) = zeroByte;
        *(s32 *)(work + 0x10) = zeroByte;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        _call_via_r2(self + 0x18, self + 0x22, (u32)*scriptTable);
    }
}
