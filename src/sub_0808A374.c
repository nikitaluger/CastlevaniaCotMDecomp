extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08003A6C(void *, s32, void *);

/* Actor effect step: bind an animation to the work state, flag the sprite,
 * clear then advance the current script byte, dispatch the script handler,
 * and tail-call the next handler from the actor's function table. */
void sub_0808A374(void *actor)
{
    u8 *self = (u8 *)actor;
    void *work = *(void **)(self + 0x6C);
    void *workState = (u8 *)work + 4;
    u8 *gfx = *(u8 **)(self + 0x38);
    u8 zero;

    *(u32 *)(gfx + 0x24) = 0x08502C40;
    sub_08003A6C((u8 *)work + 0x20, 0, (void *)0x08502D50);

    {
        u32 flags = *(u16 *)(gfx + 2);
        u32 newFlags = 0x10;
        zero = 0;
        newFlags |= flags;
        *(u16 *)(gfx + 2) = newFlags;
    }

    *(u32 *)((u8 *)work + 4) = 0x01400000;
    *(u32 *)((u8 *)workState + 4) = 0x01E70000;

    *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) = zero;

    {
        const u32 *handlerTable;
        void *entry;
        handlerTable = (const u32 *)0x08671BB0;
        entry = self + 0x18;
        sub_080C31E4(entry, self + 0x22, *handlerTable);
        *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        entry = (u8 *)entry + (s32)*(s16 *)(self + 0x22) * 2;
        sub_080C31E0(actor, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)entry * 4));
    }
}
