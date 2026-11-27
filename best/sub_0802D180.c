extern u8 gMainWorkspace[];
extern void *gMainObjTimerCallbacks;
extern void *spawnBudgetedEffect(u32, s32);
extern s32 getSpriteFacingSign(void *);
extern void _call_via_r2(void *, void *, void *);

void sub_0802D180(void *arg0)
{
    u8 *entity = (u8 *)arg0;
    u8 *sprite = *(u8 **)(entity + 0x38);
    u8 *state = *(u8 **)(entity + 0x3C);
    u8 *status = state + 0x34;
    u32 kindOffset = 0x1870;
    if (status[1] == 0xA) {
        u8 *result;
        s32 facing;
        s32 stepOffset;

        result = (u8 *)spawnBudgetedEffect(*(u32 *)((u8 *)gMainWorkspace + kindOffset), 0xCB);
        if (result != NULL) {
            facing = getSpriteFacingSign(sprite);
            if (facing > 0) {
                s32 p = *(s32 *)(state + 8);
                s32 q;
                if (p < 0) p += FIXED_TRUNC_BIAS;
                q = p >> 16;
                *(u16 *)(result + 0x4C) = q;
                *(u16 *)(result + 0x5C) = 1;
            } else {
                s32 p2 = *(s32 *)(state + 8);
                s32 q2;
                if (p2 < 0) p2 += FIXED_TRUNC_BIAS;
                q2 = p2 >> 16;
                { u16 zero = 0; *(u16 *)(result + 0x4C) = q2; *(u16 *)(result + 0x5C) = zero; }
            }
            {
                s32 p3 = *(s32 *)(state + 0xC);
                s32 q3;
                u16 v;
                if (p3 < 0) p3 += FIXED_TRUNC_BIAS;
                q3 = p3 >> 16;
                *(u16 *)(result + 0x54) = q3;
                v = *(u16 *)(state + 0x1C);
                *(u16 *)(result + 0x6C) = v;
            }
        }
        stepOffset = *(s16 *)(entity + 0x22) * 2;
        entity[stepOffset + 0x19] = 0;
        {
            void **cbp = &gMainObjTimerCallbacks;
            _call_via_r2(entity + 0x18, entity + 0x22, *cbp);
        }
    }
}
