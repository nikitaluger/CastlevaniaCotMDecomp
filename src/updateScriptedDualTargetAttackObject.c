#define SCRIPT_DUAL_ATTACK_STEP_TABLE 0x0866E5A8
#define DUAL_ATTACK_DEATH_SFX         0x8A

extern void *sScriptStepCallbacks;
extern void _call_via_r1(void *, void *);
extern void _call_via_r3(void *, void *, s32, void *);

extern s32 checkActorViewBounds(s32, void *);
extern void applySpritePaletteVariant(void *, s32);
extern s32 sub_08013558(s32, void *, void *);
extern void spawnContactEffectOnHit(void *, void *);
extern void spawnChildPair(void *, void *, void *, void *, void *);
extern s32 sub_0804FFEC(s32, void *, void *, void *);
extern void uploadPendingSpriteGraphic(void *, void *);
extern void updateActorWorldPosition(void *);
extern void playSound(s32);
extern s32 sub_08050260(void *, s32);
extern void stepAnimationTrack(s32, void *);
extern void sub_080502D0(s32, void *);
extern void syncSpriteToWorldPosition(void *, s32);

/* One update tick of a scripted attack object with two hit targets: test the
 * targets and apply the damage/knockback response, handle the death/cancel step
 * (clear step state and issue callback 3), dispatch the current step handler
 * from the object's handler table while the attack is live, then clear the
 * targets and sync the sprite to the world. */
void updateScriptedDualTargetAttackObject(u8 *self) {
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animTrack = work + 0x34;
    u8 *stepState = work + 0x48;
    u8 *stepSlot;

    if (checkActorViewBounds(sprite, work) == 1) {
        u8 *targetA = *(u8 **)(stepState + 0x20);
        u8 zero = 0;
        *(u8 *)(targetA + 1) = zero;
        *(u8 *)(*(u8 **)(stepState + 0x24) + 1) = zero;
        stepSlot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        if (stepSlot[0x1A] != 0) goto doHits;
        goto end;
    }

doHits:
    *(u8 *)(*(u8 **)(stepState + 0x20) + 1) = 5;
    *(u8 *)(*(u8 **)(stepState + 0x24) + 1) = 5;
    applySpritePaletteVariant(self, sprite);
    if (sub_08013558(sprite, work, *(void **)(work + 0x28)) != 0) {
        spawnContactEffectOnHit(self, *(void **)(work + 0x28));
        spawnChildPair(self, *(void **)(stepState + 0x20), *(void **)(stepState + 0x24), work + 0x70, work + 0x74);
    } else {
        if (sub_0804FFEC(sprite, work, *(void **)(stepState + 0x20), *(void **)(stepState + 0x24)) != 0) {
            spawnContactEffectOnHit(self, *(void **)(work + 0x28));
            spawnChildPair(self, *(void **)(stepState + 0x20), *(void **)(stepState + 0x24), work + 0x70, work + 0x74);
        }
    }

    uploadPendingSpriteGraphic(self, *(void **)(work + 0x28));
    if (*(u16 *)work & 1) {
        u8 *targetA = *(u8 **)(stepState + 0x20);
        u8 zero = 0;
        *(u8 *)(targetA + 1) = zero;
        *(u8 *)(*(u8 **)(stepState + 0x24) + 1) = zero;
        stepSlot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        if (stepSlot[0x1A] != 3) {
            *(u16 *)stepState = zero;
            updateActorWorldPosition(self);
            playSound(DUAL_ATTACK_DEATH_SFX);
            stepSlot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            *(u8 *)(stepSlot + 0x1B) = 0;
            { void **eventCallbacks = &sScriptStepCallbacks;
              _call_via_r3(self + 0x18, self + 0x22, 3, *eventCallbacks); }
        }
    }

    if (sub_08050260(self, sprite) != 0) goto finish;

    *(u32 *)(self + 0x14) = SCRIPT_DUAL_ATTACK_STEP_TABLE;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
    {
        u8 *stepSlot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        stepSlot[0x19] = (u8)(stepSlot[0x19] + 1);
    }
    {
        s32 stepOffset = (*(s16 *)(self + 0x22)) * 2;
        u8 *scriptBase = self + 0x18;
        u8 opcode = *(scriptBase + stepOffset);
        void **stepHandlers = *(void **)(self + 0x14);
        void *stepHandler = stepHandlers[opcode];
        _call_via_r1(self, stepHandler);
    }
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    if ((*(u16 *)(self + 2) & SCRIPT_OBJ_FLAG_SKIP_ANIM) != 0) goto end;
    stepAnimationTrack(sprite, animTrack);

finish:
    sub_080502D0(sprite, work);
    syncSpriteToWorldPosition(self, sprite);

end:
    ;
}
