/* Spawn a child actor for this script step after a capacity check: inherit the
 * parent's sprite flip bit and a global display value, clear the current script
 * slot, then dispatch the next command in the table. */
struct S_02025FF0 { u8 _[0x18C2]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void *allocSpriteObject(void);
extern void cleanupFailedEffectSpawn(void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

void sub_0807FDC8(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *newActor;
    u32 zero;
    u16 spriteFlags;
    if (allocWorkSlot(arg0, 0, 0x68, 3) == 0) {
        sub_080C31E0(arg0, *(void **)(self + 0x24));
        return;
    }
    newActor = allocSpriteObject();
    if (newActor == 0) {
        cleanupFailedEffectSpawn(arg0);
        return;
    }
    *(u8 **)(self + 0x38) = newActor;
    *(s32 *)(newActor + 0x1C) = 0x80000006;
    spriteFlags = (0x10 & *(u16 *)(self + 0x9C)) | *(u16 *)(newActor + 2);
    zero = 0;
    *(u16 *)(newActor + 2) = spriteFlags;
    *(u16 *)newActor = gMainWorkspace.w;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    {
        s32 *paramPtr = (s32 *)0x08671BB0;
        u8 *scriptData = self + 0x18;
        sub_080C31E4(scriptData, self + 0x22, *paramPtr);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        scriptData = scriptData + *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(arg0, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)scriptData * 4));
    }
}
