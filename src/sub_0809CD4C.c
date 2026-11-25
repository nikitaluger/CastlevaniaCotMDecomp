extern void sub_080C31E8(void *a, void *b, s32 c, void *d);
extern void sub_080C31E0(void *a, void *b);

/* Start an effect once a timer passes its limit, then run one step of the
 * effect's callback table for the current animation frame. */
void sub_0809CD4C(u8 *self)
{
    u8 *entity = *(u8 **)(self + 0x3C);
    u8 *state = entity + 0x48;
    u8 *started = entity + 0x8A;
    u8 startedValue = *started;

    if (startedValue == 0) {
        s16 limit = *(s16 *)(state + 0x2C);
        if (*(s32 *)(entity + 0x18) <= limit) {
            s16 animIndex;
            *started = 1;
            animIndex = *(s16 *)(self + 0x22);
            *(u8 *)(self + animIndex * 2 + 0x1B) = startedValue;
            {
                s32 *pEffectFunc = (s32 *)0x08671BDC;
                sub_080C31E8(self + 0x18, self + 0x22, 8, (void *)*pEffectFunc);
            }
        }
    }

    *(u32 *)(self + 0x14) = 0x0866FCAC;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;

    {
        s16 animIndex = *(s16 *)(self + 0x22);
        *(u8 *)(self + animIndex * 2 + 0x19) = *(u8 *)(self + animIndex * 2 + 0x19) + 1;
    }
    {
        s16 animIndex = *(s16 *)(self + 0x22);
        s32 off = animIndex * 2;
        u8 *base = self + 0x18;
        sub_080C31E0(self, *(void **)(*(u8 **)(self + 0x14) + *(u8 *)(base + off) * 4));
    }

    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
}
