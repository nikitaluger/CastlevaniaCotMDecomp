struct Global18C2 { u8 pad[0x18C2]; u16 initialValue; };
extern struct Global18C2 gMainWorkspace;
extern void *gMainObjTimerCallback;
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void *allocSpriteObject(void);
extern void sub_0806D2D0(void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Allocate the actor's slot-3 resource and a fresh draw object, attach it to
 * the actor, seed its value and flag-derived attribute bit, then fire the
 * actor type's callbacks. */
void sub_0806DEB0(u8 *actor) {
    void *newObj;
    u32 flags;
    u8 *cbParam;

    if (allocWorkSlot(actor, 0, 0x34, 3) == 0) {
        sub_080C31E0(actor, *(s32 *)(actor + 0x24));
        return;
    }
    newObj = allocSpriteObject();
    if (newObj == 0) {
        sub_0806D2D0(actor);
        return;
    }
    *(void **)(actor + 0x38) = newObj;
    *(u16 *)newObj = gMainWorkspace.initialValue;
    flags = *(u32 *)(actor + 0x7C) & 0xF0000000;
    switch (flags) {
    case 0:
        *(u16 *)((u8 *)newObj + 2) = (*(u16 *)((u8 *)*(void **)(*(u8 **)(actor + 0x28) + 0x38) + 2) & 0x10) | *(u16 *)((u8 *)newObj + 2);
        break;
    case 0x10000000:
        *(u16 *)((u8 *)newObj + 2) = *(u16 *)((u8 *)newObj + 2) & 0xFFEF;
        break;
    case 0x20000000:
        *(u16 *)((u8 *)newObj + 2) = *(u16 *)((u8 *)newObj + 2) | 0x10;
        break;
    }
    (actor + *(s16 *)(actor + 0x22) * 2)[0x19] = 0;
    { void **callback = &gMainObjTimerCallback;
      cbParam = actor + 0x18;
      sub_080C31E4(cbParam, actor + 0x22, (s32)*callback); }
    (actor + *(s16 *)(actor + 0x22) * 2)[0x19]++;
    cbParam += *(s16 *)(actor + 0x22) * 2;
    sub_080C31E0(actor, *(s32 *)((cbParam[0] * 4) + *(u32 *)(actor + 0x14)));
}
