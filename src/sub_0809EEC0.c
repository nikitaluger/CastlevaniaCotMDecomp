/* Computes an entity's velocity from its angle and speed, dispatches the
   current behavior callback, then advances to the next behavior. */
extern s32 sub_080C31E0(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, void *c);

extern u32 D_08671BFC;
extern u32 D_08671BB0;

void sub_0809EEC0(void *arg0)
{
    u8 *object = (u8 *)arg0;
    u8 *work = *(u8 **)(object + 0x3C);
    u8 *child = *(u8 **)(work + 0x28);
    s32 zero = 0;
    u32 *sinFn;

    child[1] = zero;
    sinFn = &D_08671BFC;

    {
        s32 sine = sub_080C31E0((void *)(*(s32 *)(object + 0x7C) + 0x4000), (void *)*sinFn);
        s32 speed = *(s32 *)(object + 0x8C);
        *(s32 *)(work + 0x10) = (speed >> 8) * (sine >> 8);
    }
    {
        s32 sine = sub_080C31E0(*(void **)(object + 0x7C), (void *)*sinFn);
        s32 speed = *(s32 *)(object + 0x8C);
        *(s32 *)(work + 0x14) = (speed >> 8) * (sine >> 8);
    }

    *(object + *(s16 *)(object + 0x22) * 2 + 0x19) = 0;

    {
        u32 *behaviorFn = &D_08671BB0;
        u8 *args = object + 0x18;
        sub_080C31E4(args, object + 0x22, (void *)*behaviorFn);
        {
            s16 index = *(s16 *)(object + 0x22);
            (*(u8 *)(index * 2 + object + 0x19))++;
            index = *(s16 *)(object + 0x22);
            args += index * 2;
            {
                u8 behaviorId = *args;
                void **table = *(void ***)(object + 0x14);
                sub_080C31E0(object, table[behaviorId]);
            }
        }
    }
}
