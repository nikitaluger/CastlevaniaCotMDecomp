extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern s32 D_081020E4[];
extern s32 D_081020EC[];

struct WorkFields { u8 pad[0x110]; u32 f110; u8 pad2[0xC]; u8 f120; };

/* Actor step: load per-index movement parameters into the work state, clear
 * two work fields, then reset and dispatch the script handler and tail-call
 * the next handler from the actor's function table. */
void sub_080A7E10(void *actor) {
    u8 *self = (u8 *)actor;
    u8 *base = *(u8 **)(self + 0x3C);
    s32 *handlerTable;

    *(s32 *)(base + 0x10C) = D_081020E4[*(u8 *)(self + 0x4C)];
    *(s32 *)(base + 0x118) = D_081020EC[*(u8 *)(self + 0x4C)];
    ((struct WorkFields *)base)->f110 = 0;
    ((struct WorkFields *)base)->f120 = 0;

    {
        u8 zero = 0;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    }
    handlerTable = (s32 *)0x08671BB0;
    base = self + 0x18;
    sub_080C31E4(base, self + 0x22, *handlerTable);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    base = base + *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)base * 4));
}
