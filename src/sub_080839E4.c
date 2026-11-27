/* Initialize an actor's sprite state and advance its action script: clear the
 * sprite's resource slots and install the cleanup callback, set its state table
 * and animation params, then clear and bump the script counter and dispatch the
 * handler selected by the script. */
extern void startEffectTimer(void *, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void releaseActorEffectParts(void);

void sub_080839E4(u8 *actor) {
    u8 *sprite = *(u8 **)(actor + 0x6C);
    u8 *spriteState = sprite + 4;
    u8 *state = *(u8 **)(actor + 0x38);
    u8 *script;
    s32 zero = 0;
    u8 *src;
    s32 *argTable;
    u32 clearOff, stepOff, dispatchOff;
    s32 spriteByte;

    *(s32 *)(spriteState + 0x2C) = zero;
    *(s32 *)(spriteState + 0x30) = zero;
    *(s32 *)(spriteState + 0x34) = zero;
    *(s32 *)(spriteState + 0x38) = zero;
    *(s32 *)(spriteState + 0x3C) = zero;
    *(void **)(spriteState + 0x18) = *(void **)(actor + 0x24);
    *(void **)(actor + 0x24) = &releaseActorEffectParts;
    *(u32 *)(state + 0x24) = 0x084FAC70;
    startEffectTimer(sprite + 0x20, 0, 0x084FACD8);
    *(void **)(spriteState + 0x4C) = *(void **)(actor + 0x7C);
    spriteByte = *(s32 *)(actor + 0x8C);
    *(u8 *)(sprite + 0x54) = spriteByte;
    src = *(u8 **)(spriteState + 0x4C);
    *(s32 *)(sprite + 4) = *(s32 *)(src + 0xC);
    *(s32 *)(spriteState + 4) = *(s32 *)(src + 0x10);
    clearOff = *(s16 *)(actor + 0x22);
    clearOff <<= 1;
    clearOff += (u32)actor;
    *(u8 *)(clearOff + 0x19) = zero;
    argTable = (s32 *)0x08671BB0;
    script = actor + 0x18;
    sub_080C31E4(script, actor + 0x22, *argTable);
    stepOff = *(s16 *)(actor + 0x22);
    stepOff <<= 1;
    stepOff += (u32)actor;
    *(u8 *)(stepOff + 0x19) += 1;
    dispatchOff = *(s16 *)(actor + 0x22);
    dispatchOff <<= 1;
    script += dispatchOff;
    sub_080C31E0(actor, *(void **)(*(u8 *)script * 4 + *(s32 *)(actor + 0x14)));
}
