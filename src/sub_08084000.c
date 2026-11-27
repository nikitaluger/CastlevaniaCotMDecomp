/* Spawn a fresh child actor for this script step after a capacity check: inherit
 * the parent's sprite flip bit and a global display value, clear the current
 * script slot, then dispatch the next command in the table. */
struct S_02025FF0 { u8 _[0x18C2]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;
s32 allocWorkSlot(void *, s32, s32, s32);
void *allocSpriteObject(void);
void cleanupFailedEffectSpawn(void *);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);
void sub_08084000(void *arg0) {
    void *newActor;
    u8 zero;
    u16 spriteFlags;
    if (allocWorkSlot(arg0, 0, 0x68, 3) == 0) {
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    newActor = allocSpriteObject();
    if (newActor == NULL) {
        cleanupFailedEffectSpawn(arg0);
        return;
    }
    *(void **)((u8 *)arg0 + 0x38) = newActor;
    *(s32 *)((u8 *)newActor + 0x1C) = 0x80000004;
    spriteFlags = (u16)((*(u16 *)((u8 *)*(void **)((u8 *)*(void **)((u8 *)arg0 + 0x28) + 0x38) + 2) & 0x10) | *(u16 *)((u8 *)newActor + 2));
    zero = 0;
    *(u16 *)((u8 *)newActor + 2) = spriteFlags;
    *(u16 *)newActor = gMainWorkspace.w;
    *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = zero;
    {
        s32 *paramPtr = (s32 *)0x08671BB0;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *paramPtr);
    }
    {
        u8 *slotPtr = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        slotPtr[0x19] = (u8)(slotPtr[0x19] + 1);
    }
    {
        s32 cmdOffset = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
        u8 *cmdArray = (u8 *)arg0 + 0x18;
        u8 cmdIndex = *(cmdArray + cmdOffset);
        u8 **cmdTable = *(u8 **)((u8 *)arg0 + 0x14);
        sub_080C31E0(arg0, (s32)cmdTable[cmdIndex]);
    }
}
