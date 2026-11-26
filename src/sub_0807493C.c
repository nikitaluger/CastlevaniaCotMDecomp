/* Spawn a fresh actor for this script step: after a capacity check, inherit the
 * parent's sprite flip bit plus the display value at self+0x7C, reset the current
 * script slot, then dispatch the next command in the table. */
struct S_02025FF0 { u8 _[0x18C2]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void *allocSpriteObject(void);
extern void sub_0806D2D0(void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

void sub_0807493C(void *actor) {
    u8 *self = (u8 *)actor;
    u8 *newActor;
    u32 zero;
    u16 spriteFlags;
    if (allocWorkSlot(actor, 0, 0x68, 3) == 0) {
        sub_080C31E0(actor, *(void **)(self + 0x24));
        return;
    }
    newActor = allocSpriteObject();
    if (newActor == 0) {
        sub_0806D2D0(actor);
        return;
    }
    *(u8 **)(self + 0x38) = newActor;
    spriteFlags = (0x10 & *(u16 *)(*(u8 **)(*(u8 **)(self + 0x28) + 0x38) + 2)) | *(u16 *)(newActor + 2);
    zero = 0;
    *(u16 *)(newActor + 2) = spriteFlags;
    *(u16 *)newActor = gMainWorkspace.w | *(u16 *)(self + 0x7C);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    {
        s32 *paramPtr = (s32 *)0x08671BB0;
        u8 *cmdArray = self + 0x18;
        sub_080C31E4(cmdArray, self + 0x22, *paramPtr);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        cmdArray = cmdArray + *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(actor, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)cmdArray * 4));
    }
}
