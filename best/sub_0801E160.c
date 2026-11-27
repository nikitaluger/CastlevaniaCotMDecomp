extern void setAnimationFrame(s32, void *, u16, u8);
extern void sub_080C31E4(void *, void *, s32);
extern void *spawnBudgetedEffect(s32, s32);
extern s32 getSpriteFacingSign(s32);

extern u8 D_02025FF0[];
extern u32 *gMainObjTimerCallbacks;

void sub_0801E160(void *arg0) {
    u8 *script = (u8 *)arg0;
    s32 parent = *(s32 *)(script + 0x38);
    u8 *motion = *(u8 **)(script + 0x3C);
    u8 *anim = motion + 0x34;
    u8 *state = motion + 0x48;

    setAnimationFrame(parent, anim, 5, 0);

    if (*(s16 *)(state + 0x28) <= 0 && *(s16 *)(state + 8) <= 0) {
        void **slot = (void **)(motion + 0x58);
        s32 i;
        for (i = 5; i >= 0; i--) {
            if (*slot != 0) {
                u16 *p = (u16 *)((u8 *)*slot + 0x5C);
                *p |= 1;
                *slot = 0;
            }
            slot++;
        }
        {
            s16 step = *(s16 *)(script + 0x22);
            *(u8 *)(script + step * 2 + 0x19) = 0;
        }
        sub_080C31E4(script + 0x18, script + 0x22, (s32)*gMainObjTimerCallbacks);
        return;
    }

    {
        s32 v;
        void *obj;
        s32 r5;

        v = *(s32 *)(D_02025FF0 + 0x189C);
        if (((v + ((u32)v >> 31)) >> 1) & 1) {
            *(s32 *)state = 0x10000;
        }

        *(u16 *)(state + 8) = *(u16 *)(state + 8) - 1;
        if ((s16)*(u16 *)(state + 8) >= 0) {
            return;
        }

        r5 = 6 - *(s16 *)(state + 0x28);
        if (*(s16 *)(state + 0x2A) == 0) {
            obj = spawnBudgetedEffect(*(s32 *)(D_02025FF0 + 0x1870), 0x96);
        } else {
            obj = spawnBudgetedEffect(*(s32 *)(D_02025FF0 + 0x1870), 0x97);
        }
        *(void **)(state + 0x10 + r5 * 4) = obj;
        if (obj == 0) {
            goto fail;
        }

        if (*(s16 *)(state + 0x2A) == 0) {
            s32 sign = getSpriteFacingSign((s32)script);
            if (sign < 0) {
                s32 x = *(s16 *)((u8 *)D_02025FF0 + 0x2C + r5 * 2);
                s32 y = *(s16 *)((u8 *)D_02025FF0 + 0x1C + r5 * 2);
                s32 tmp = (x << 16) + 0x8000;
                s32 tmp2 = ((0xF0 - y) << 16) + 0x8000;
                if (tmp < 0) tmp += 0xFFFF;
                *(s16 *)((u8 *)obj + 0x4C) = (s16)(tmp >> 16);
                if (tmp2 < 0) tmp2 += 0xFFFF;
                *(s16 *)((u8 *)obj + 0x54) = (s16)(tmp2 >> 16);
            } else {
                s32 x = *(s16 *)((u8 *)D_02025FF0 + 0x1C + r5 * 2);
                s32 y = *(s16 *)((u8 *)D_02025FF0 + 0x2C + r5 * 2);
                s32 tmp = (x << 16) + 0x8000;
                s32 tmp2 = ((0xF0 - y) << 16) + 0x8000;
                if (tmp < 0) tmp += 0xFFFF;
                *(s16 *)((u8 *)obj + 0x4C) = (s16)(tmp >> 16);
                if (tmp2 < 0) tmp2 += 0xFFFF;
                *(s16 *)((u8 *)obj + 0x54) = (s16)(tmp2 >> 16);
            }
        } else {
            s32 sign = getSpriteFacingSign((s32)script);
            (void)sign;
        }

        *(u16 *)((u8 *)obj + 0x5C) = 0x10;
        *(s16 *)((u8 *)obj + 0x7C) = (s16)r5;
        *(s32 *)((u8 *)obj + 0x6C) = (s32)arg0;
        *(u16 *)(state + 8) = 10;
        *(s16 *)(state + 0x28) = *(s16 *)(state + 0x28) - 1;
        if (*(s16 *)(state + 0x28) == 0) {
            *(u16 *)(state + 8) = 20;
        }
        return;

    fail:
        {
            void **slot = (void **)(motion + 0x58);
            s32 i;
            for (i = 5; i >= 0; i--) {
                if (*slot != 0) {
                    u16 *p = (u16 *)((u8 *)*slot + 0x5C);
                    *p |= 1;
                    *slot = 0;
                }
                slot++;
            }
            {
                s16 step = *(s16 *)(script + 0x22);
                *(u8 *)(script + step * 2 + 0x19) = 0;
            }
            sub_080C31E4(script + 0x18, script + 0x22, (s32)*gMainObjTimerCallbacks);
        }
    }
}
