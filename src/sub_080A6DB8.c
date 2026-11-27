extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

struct WorkByte { u8 pad[0x138]; u8 f138; };
struct WorkWord0 { u8 pad[0x13C]; u32 f13C; };
struct WorkWord1 { u8 pad[0x140]; u32 f140; };

/* Actor step: clear three fields of the actor's work state, then reset the
 * current script slot, dispatch the script handler through the gMainObjTimerCallbacks
 * table, and tail-call the next handler from the actor's function table. */
void sub_080A6DB8(void *actor) {
    u8 *self = (u8 *)actor;
    u8 *base = *(u8 **)(self + 0x3C);
    u8 *base18;
    s32 *handlerTable;

    ((struct WorkByte *)base)->f138 = 0;
    ((struct WorkWord0 *)base)->f13C = 0;
    ((struct WorkWord1 *)base)->f140 = 0x0C;

    {
        u8 zero = 0;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    }
    handlerTable = (s32 *)0x08671BB0;
    base18 = self + 0x18;
    sub_080C31E4(base18, self + 0x22, *handlerTable);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    base18 = base18 + *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)base18 * 4));
}
