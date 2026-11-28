extern void setAnimationFrame(s32, void *, u16, u8);
extern s32 getSpriteFacingSign(void *);
extern void _call_via_r2(void *, void *, s32);
extern void *gMainObjTimerCallbacks;

void sub_0802FEAC(u8 *arg0)
{
int __repair_literal;

    void *sprite = *(void **)(arg0 + 0x38);
    u8 *work = *(u8 **)(arg0 + 0x3C);
    u8 *status = work + 0x34;
    u8 *timer = work + 0x48;
    u8 kind;
    u32 check;
    u16 count;
    u8 *objA;
    u8 *objB;
    s32 q;
    u8 temp;

    setAnimationFrame((s32)sprite, status, 5, 0);
    temp = status[1];
    kind = temp;
    if (kind != 1)
        return;
    check = *(u32 *)(status + 4);
    count = *(u16 *)(status + 2);
    if (check != count)
        return;
    objB = *(u8 **)(work + 0x48);
    objA = *(u8 **)(timer + 4);
    if (getSpriteFacingSign(sprite) > 0) {
        q = *(s32 *)(work + 8);
        if (q < 0)
            q += FIXED_TRUNC_BIAS;
        q >>= 16;
        q += 0xC;
        *(u16 *)(objA + 0x4C) = q;
        *(u16 *)(objB + 0x4C) = q;
        *(u16 *)(objA + 0x5C) = kind;
        *(u16 *)(objB + 0x5C) = kind;
    } else {
        q = *(s32 *)(work + 8);
        if (q < 0)
            q += FIXED_TRUNC_BIAS;
        q >>= 16;
        q -= 0xC;
        *(u16 *)(objA + 0x4C) = q;
        *(u16 *)(objB + 0x4C) = 0;
        *(u16 *)(objA + 0x5C) = 0;
        *(u16 *)(objB + 0x5C) = 0;
    }
    q = *(s32 *)(work + 0xC);
__repair_literal = 0;

    if (q < __repair_literal)
        q += FIXED_TRUNC_BIAS;
    q >>= 16;
    q -= 0xC;
    *(u16 *)(objA + 0x54) = q;
    *(u16 *)(objB + 0x54) = q;
    *(u16 *)(objB + 0x6C) |= 4;
    *(u16 *)(objA + 0x6C) |= 4;
    *(u16 *)(timer + 0xC) = 0x28;
    {
        u8 zero = 0;
        void **cbp = &gMainObjTimerCallbacks;
        s16 step = *(s16 *)(arg0 + 0x22);
        *(u8 *)(arg0 + step * 2 + 0x19) = 0;
        _call_via_r2(arg0 + 0x18, arg0 + 0x22, *cbp);
    }
}
