extern s32 allocWorkSlot(void *, s32, s32, s32);
extern s32 allocSpriteObject(void);
extern void cleanupFailedEffectSpawn(void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

// Verifies the entity's spawn slot, allocates the object stored at +0x38 and
// clears one of its flags, resets then advances the slot counter byte, calls the
// indirect callback from the 0x08671BB0 table, and dispatches through the
// entity's own callback array using the resulting byte.
void sub_08083694(void *entity)
{
    s32 obj;
    s16 slot;
    u8 *flags;
    s32 *callbackTable;

    if (allocWorkSlot(entity, 0, 0x68, 3) == 0) {
        sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }

    obj = allocSpriteObject();
    if (obj == 0) {
        cleanupFailedEffectSpawn(entity);
        return;
    }

    *(s32 *)((u8 *)entity + 0x38) = obj;
    {
        u8 *flagPtr = (u8 *)obj + 0x2A;
        u8 maskedFlag = *flagPtr & 0xBF;
        s32 zero = 0;
        *flagPtr = maskedFlag;
        slot = *(s16 *)((u8 *)entity + 0x22);
        *(u8 *)((u8 *)entity + slot * 2 + 0x19) = zero;
    }

    callbackTable = (s32 *)0x08671BB0;
    flags = (u8 *)entity + 0x18;
    sub_080C31E4(flags, (u8 *)entity + 0x22, *callbackTable);

    slot = *(s16 *)((u8 *)entity + 0x22);
    *(u8 *)((u8 *)entity + slot * 2 + 0x19) += 1;

    slot = *(s16 *)((u8 *)entity + 0x22);
    flags += slot * 2;
    {
        u8 callbackIndex = *flags;
        s32 *callbackArray = *(s32 **)((u8 *)entity + 0x14);
        sub_080C31E0(entity, callbackArray[callbackIndex]);
    }
}
