extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 getSpriteFacingSign(s32);
extern u32 scaleByRandom(u32);
extern void _call_via_r2(void *, void *, s32);

void sub_0803D8BC(void *arg0)
{
    u8 *self = (u8 *)arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *anim = work + 0x34;

    setAnimationFrame(sprite, anim, 5, 0);
    if (*(u8 *)anim & 2)
    {
        s16 kind = *(s16 *)(work + 0x1C);
        s32 tmp;
        if (kind == 0xE)
        {
            if (getSpriteFacingSign(sprite) > 0)
                *(s32 *)(work + 0x10) = 0x20000;
            else
                *(s32 *)(work + 0x10) = 0xFFFE8000;
            tmp = (s32)scaleByRandom(0x4000);
        }
        else
        {
            if (getSpriteFacingSign(sprite) > 0)
                *(s32 *)(work + 0x10) = 0x18000;
            else
                *(s32 *)(work + 0x10) = 0xFFFD0000;
            tmp = (s32)scaleByRandom(0x4000);
        }
        {
            s16 step;
            s32 *scriptTable;
            *(s32 *)(work + 0x14) = tmp - 0x30000;
            step = *(s16 *)(self + 0x22);
            *(u8 *)(self + step * 2 + 0x19) = 0;
            scriptTable = (s32 *)0x08671BB0;
            _call_via_r2(self + 0x18, self + 0x22, *scriptTable);
        }
    }
}
