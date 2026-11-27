struct S_02025FF0 { u8 _0x000[0x18C2]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;
struct T { u16 w; u16 pad[1]; u16 a; u16 b; u16 c; };
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void *allocSpriteObject(void);
extern s32 isGameStatusFlagSet(s32);
extern void _call_via_r1(void *, s32);
extern void _call_via_r2(void *, void *, u32);

/* Loads graphics slot 3 and allocates an animation object for the entity,
 * initializes its fields from the global state word at gMainWorkspace+0x18C2, then
 * runs the animation-slot callback at 0x08671BB0 and dispatches the entity's
 * current action through the callback at entity+0x24. On any failure of the
 * load, the 0xBC flag check or the allocation, only that callback is invoked. */
void sub_0808ABDC(void *arg0) {
    u8 *entity = (u8 *)arg0;
    void *obj;
    s32 flags;

    if (allocWorkSlot(arg0, 0, 0x3C, 3) == 0) {
        _call_via_r1(arg0, *(s32 *)(entity + 0x24));
        return;
    }
    flags = isGameStatusFlagSet(0xBC);
    if (flags != 0) {
        _call_via_r1(arg0, *(s32 *)(entity + 0x24));
        return;
    }
    obj = allocSpriteObject();
    if (obj == 0) {
        _call_via_r1(arg0, *(s32 *)(entity + 0x24));
        return;
    }

    *(void **)(entity + 0x38) = obj;
    *(u32 *)((u8 *)obj + 0x1C) = 0x80000003;
    {
        u32 zero = 0;
        u16 globalW = gMainWorkspace.w;
        struct T *objData = (struct T *)obj;
        objData->w = globalW;
        objData->a = 0x1000;
        objData->b = 0x0100;
        objData->c = (u16)flags;
        {
            s32 slotIndex = *(s16 *)(entity + 0x22);
            *(u8 *)(entity + slotIndex * 2 + 0x19) = zero;
        }
    }

    {
        const u32 *callbackTable = (const u32 *)0x08671BB0;
        void *slot = entity + 0x18;
        _call_via_r2(slot, entity + 0x22, *callbackTable);
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) += 1;
        slot = (u8 *)slot + *(s16 *)(entity + 0x22) * 2;
        _call_via_r1(arg0, *(u32 *)(*(u32 *)(entity + 0x14) + *(u8 *)slot * 4));
    }
}
