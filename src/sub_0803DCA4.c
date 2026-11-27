extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 getSpriteFacingSign(void *);
extern u32 D_0866E028[];

void sub_0803DCA4(u8 *arg0)
{
    u8 *sprite = *(u8 **)(arg0 + 0x38);
    u8 *work = *(u8 **)(arg0 + 0x3c);
    s32 sign;
    s16 slot;
    u8 state;
    u32 val;

    setAnimationFrame(sprite, work + 0x34, 0, 1);

    sign = getSpriteFacingSign(sprite);
    if (sign > 0)
        *(u32 *)(work + 0x10) = 0xFFFF0000;
    else
        *(u32 *)(work + 0x10) = 0x10000;
    *(u32 *)(arg0 + 0x14) = (u32)D_0866E028;

    *(u16 *)(arg0 + 0x22) += 1;

    slot = *(s16 *)(arg0 + 0x22);
    *(u8 *)(arg0 + 0x19 + slot * 2) += 1;

    slot = *(s16 *)(arg0 + 0x22);
    {
        s32 off = slot * 2;
        u8 *p = arg0;
        p += 0x18;
        p = p + off;
        state = *p;
    }

    ((void (**)(void *))*(u32 *)(arg0 + 0x14))[state](arg0);

    *(u16 *)(arg0 + 0x22) -= 1;
}
