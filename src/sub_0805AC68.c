extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 getSpriteFacingSign(void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *gScriptStepCallbacks;

/* Patrol AI: when the entity reaches either movement bound, flip its facing
 * (bit 0x10) and reset its velocity; otherwise tick a countdown timer and,
 * when it expires, stop the entity and fire its script callback. */
void sub_0805AC68(void *arg0)
{
    u8 *entity = (u8 *) arg0;
    u8 *mainObj;
    u8 *obj;
    u8 *bounds;
    u8 *anim;
    mainObj = *((u8 **) (entity + 0x38));
    obj = *((u8 **) (entity + 0x3C));
    anim = obj + 0x34;
    bounds = obj + 0x48;
    setAnimationFrame(mainObj, anim, 0, 1);
    if ((*((s32 *) (obj + 0x10))) < 0)
    {
        if ((*((s32 *) (obj + 0x08))) <= (*((s32 *) (bounds + 0x04))))
        {
            *((u16 *) (mainObj + 0x02)) ^= 0x10;
            if (getSpriteFacingSign(mainObj) > 0)
            {
                *((s32 *) (obj + 0x10)) = 0x6000;
            }
            else
            {
                *((s32 *) (obj + 0x10)) = 0xFFFFA000;
            }
        }
        else
        {
            goto dec;
        }
    }
    else
        if ((*((s32 *) (obj + 0x08))) >= (*((s32 *) (bounds + 0x08))))
        {
            *((u16 *) (mainObj + 0x02)) ^= 0x10;
            if (getSpriteFacingSign(mainObj) > 0)
            {
                *((s32 *) (obj + 0x10)) = 0x6000;
            }
            else
            {
                *((s32 *) (obj + 0x10)) = 0xFFFFA000;
            }
        }
        else
        {
            goto dec;
        }
    return;
    dec:
    *((u16 *) (bounds + 0x00)) = (*((u16 *) (bounds + 0x00))) - 1;

    if (((s16) (*((u16 *) (bounds + 0x00)))) < 0)
    {
        s32 z;
        z = 0;
        *((s32 *) (obj + 0x10)) = z;
        z = *((s16 *) (entity + 0x22));
        *((u8 *)(entity + z * 2 + 0x19)) = 0;
        {
            void **fn = &gScriptStepCallbacks;
            sub_080C31E8(entity + 0x18, entity + 0x22, 1, *fn);
        }
    }
}
