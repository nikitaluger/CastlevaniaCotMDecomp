/* One tick of scripted-entity AI: check screen bounds and contact state, react
 * to the current script step's flags (state bits and sound), then dispatch the
 * step from the script callback table and integrate the actor. */
void sub_0802F0BC(u8 *entity) {
    s32 sprite = *(s32 *)(entity + 0x38);
    u8 *actor = *(u8 **)(entity + 0x3C);
    u32 anim = (u32)actor + 0x34;
    u8 *actor48 = actor + 0x48;
    s32 visible;

    applySpritePaletteVariant(entity, sprite);
    visible = sub_08014114(*(s32 *)(actor + 8), *(s32 *)(actor + 0xC), -0x10, 0x10, -0x30, 0x30);
    if (visible == 0) {
        *(u8 *)(*(u8 **)(actor + 0x28) + 1) = (u8)visible;
    }
    if (sub_08013558(sprite, actor, *(void **)(actor + 0x28)) != 0) {
        spawnContactEffectOnHit(entity, *(void **)(actor + 0x28));
    }
    {
        u8 *step = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        if (*(u8 *)(step + 0x1A) != 2 && (*(u16 *)(actor + 2) & 1)) {
            u8 *step2;
            s32 zero;
            u16 mask;
            s16 stateFlags;
            u16 newFlags;
            stateFlags = *(volatile s16 *)actor;
            mask = 0x21;
            zero = 0;
            newFlags = (u16)(stateFlags | mask);
            *(u16 *)actor = newFlags;
            sub_08005E80(0x8B);
            step2 = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(step2 + 0x1B) = (u8)zero;
            {
                s32 *sfxTable = (s32 *)0x08671BDC;
                sub_080C31E8(entity + 0x18, entity + 0x22, 2, *sfxTable);
            }
        }
    }
    uploadPendingSpriteGraphic(entity, *(void **)(actor + 0x28));
    if (*(u16 *)actor & 1) {
        u8 *step = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        if (*(u8 *)(step + 0x1A) != 2) {
            u8 *step2;
            s32 *sfxTable;
            updateActorWorldPosition(entity);
            sub_08005E80(0x8B);
            step2 = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(step2 + 0x1B) = 0;
            sfxTable = (s32 *)0x08671BDC;
            sub_080C31E8(entity + 0x18, entity + 0x22, 2, *sfxTable);
        }
    }
    if (updateObjectDisplayState(sprite, actor) != 0) goto label_else;
    {
        u8 *step;
        s32 stepOffset;
        u8 *opcodePtr;
        u8 opcode;
        void **scriptCallbacks;
        void *callback;
        *(void **)(entity + 0x14) = (void *)0x0866DBE8;
        *(u16 *)(entity + 0x22) = (u16)(*(u16 *)(entity + 0x22) + 1);
        step = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        *(u8 *)(step + 0x19) = (u8)(*(u8 *)(step + 0x19) + 1);
        stepOffset = (*(s16 *)(entity + 0x22)) * 2;
        opcodePtr = entity + 0x18;
        opcode = *(opcodePtr + stepOffset);
        scriptCallbacks = *(void **)(entity + 0x14);
        callback = scriptCallbacks[opcode];
        sub_080C31E0(entity, callback);
        *(u16 *)(entity + 0x22) = (u16)(*(u16 *)(entity + 0x22) - 1);
        if (*(u16 *)(entity + 2) & 0x8000) return;
        sub_08011460(sprite, anim, *(s32 *)actor48);
        sub_08011EE8(actor, 0x16C1, 0);
    }
label_else:
    *(u16 *)(*(void **)(actor + 0x28) + 0x14) = 0;
    sub_08013C8C(entity, sprite);
}
