void sub_080113A8(s32, s32);
void _call_via_r2(void *, void *, s32);
void sub_08011528(void *, void *);
void _call_via_r1(void *, void *);
void sub_08013C8C(void *, void *);
void sub_08016678(void *);

/* When the animation finishes, flag the linked object and restart the script. */
void sub_080ADFE8(void *arg0) {
    u8 *actor = (u8 *)arg0;
    s32 sprite = *(s32 *)(actor + 0x38);
    u8 *work = *(u8 **)(actor + 0x3C);
    u8 *anim = work + 0x34;
    sub_080113A8(sprite, (s32)anim);
    if (*anim & 2) {
        *(u8 *)(*(u8 **)(work + 0x28) + 1) = 5;
        {
            u8 zero = 0;
            *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = zero;
            {
                s32 *advanceCb = (s32 *)0x08671BB0;
                _call_via_r2(actor + 0x18, actor + 0x22, *advanceCb);
            }
        }
    }
}

/* Advance to the next script step: install its command table, bump the step
 * and sub-step, dispatch the command handler, then refresh the sprite. */
void sub_080AEF88(void *arg0) {
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    sub_08011528(sprite, *(u8 **)((u8 *)arg0 + 0x3C) + 0x34);
    *(void **)((u8 *)arg0 + 0x14) = (void *)0x08670224;
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) + 1);
    {
        u8 *slot = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        slot[0x19] = (u8)(slot[0x19] + 1);
        {
            s32 stepOffset = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
            u8 *steps = (u8 *)arg0 + 0x18;
            u8 command = *(steps + stepOffset);
            void **handlerTable = *(void **)((u8 *)arg0 + 0x14);
            void *handler = handlerTable[command];
            _call_via_r1(arg0, handler);
        }
    }
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) - 1);
    sub_08013C8C(arg0, sprite);
}

/* Flag the linked object per the actor's variant, finish the animation/position
 * cleanup and restart the script. */
void sub_080A8018(void *arg0) {
    u8 *actor = (u8 *)arg0;
    u8 *sprite = *(u8 **)(actor + 0x38);
    switch (*(u8 *)(actor + 0x4C)) {
    case 0:
        *(u8 *)(*(u8 **)(actor + 0x28) + 0x4C) = 1;
        break;
    case 1:
        *(u8 *)(*(u8 **)(actor + 0x28) + 0x50) = 1;
        break;
    }
    sub_08016678(actor);
    *(s32 *)(sprite + 0x1C) = 2;
    *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = 0;
    {
        s32 *advanceCb = (s32 *)0x08671BB0;
        _call_via_r2(actor + 0x18, actor + 0x22, *advanceCb);
    }
}
