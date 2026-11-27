/* Alternate controlled-entity script update: refresh contact/link state, run
 * the next script opcode from the shared handler table, then resync the sprite. */
extern void applySpritePaletteVariant(void *, s32);
extern s32 checkActorViewBounds(s32, void *);
extern s32 detectActorHit(s32, void *, void *);
extern void spawnContactEffectOnHit(void *, void *);
extern void uploadPendingSpriteGraphic(void *, void *);
extern void updateActorWorldPosition(void *);
extern s32 updateObjectDisplayState(s32, void *);
extern void stepAnimationTrack(s32, void *);
extern void moveObjectHorizontally(void *, s32, s32);
extern void syncSpriteToWorldPosition(void *, s32);
extern void freeMotionTracker(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void *gScriptEventCallbacks;
struct EntityFlagBits { u16 lo; u16 hi; };

void updateControlledEntityAlt(u8 *self) {
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *control = *(u8 **)(self + 0xAC);
    u8 *motion = *(u8 **)(self + 0x3C);
    u8 *animState = motion + 0x34;
    u8 *motionEx = motion + 0x48;

    if (checkActorViewBounds(sprite, motion) == 1) {
        *(u16 *)motionEx = 0;
        return;
    }

    applySpritePaletteVariant(self, sprite);
    if (detectActorHit(sprite, motion, *(void **)(motion + 0x28)) != 0) {
        spawnContactEffectOnHit(self, *(void **)(motion + 0x28));
    }
    if (*(u16 *)(*(u8 **)(control + 4) + 6) == 0) {
        uploadPendingSpriteGraphic(self, *(void **)(motion + 0x28));
    }
    if (*(u16 *)motion & ALT_CONTROLLED_MOTION_FLAG) {
        u8 *scriptStep = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        if (*(u8 *)(scriptStep + 0x1A) != ALT_CONTROLLED_HIT_STEP) {
            u8 *stepPtr;
            s32 *callbacks;
            if (*(u16 *)(*(u8 **)(control + 4) + 6) == 0) {
                updateActorWorldPosition(self);
            } else {
                if (control != NULL) {
                    ((struct EntityFlagBits *)control)->lo |= ALT_CONTROLLED_CONTROL_FLAG;
                }
                if (*(void **)(motion + 0x2C) != NULL) {
                    freeMotionTracker();
                    *(void **)(motion + 0x2C) = NULL;
                }
                {
                    u8 *linked = *(u8 **)(motion + 0x30);
                    if (linked != NULL) {
                        ((struct EntityFlagBits *)linked)->hi |= ALT_CONTROLLED_LINK_FLAG;
                    }
                }
            }
            stepPtr = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            *(u8 *)(stepPtr + 0x1B) = 0;
            callbacks = (s32 *)&gScriptEventCallbacks;
            sub_080C31E8(self + 0x18, self + 0x22, ALT_CONTROLLED_HIT_STEP, *callbacks);
        }
    }
    if (updateObjectDisplayState(sprite, motion) == 0) {
        u8 *stepPtr;
        s32 stepOffset;
        u8 *scriptSteps;
        u8 opcode;
        void **handlerTable;
        void *handler;
        *(void **)(self + 0x14) = (void *)ALT_CONTROLLED_STEP_HANDLERS;
        *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) + 1);
        stepPtr = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        *(u8 *)(stepPtr + 0x19) = (u8)(*(u8 *)(stepPtr + 0x19) + 1);
        stepOffset = (*(s16 *)(self + 0x22)) * 2;
        scriptSteps = self + 0x18;
        opcode = *(scriptSteps + stepOffset);
        handlerTable = *(void **)(self + 0x14);
        handler = handlerTable[opcode];
        sub_080C31E0(self, handler);
        *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) - 1);
        if ((*(u16 *)(self + 2) & ALT_CONTROLLED_READY_FLAG) == 0) {
            stepAnimationTrack(sprite, animState);
            moveObjectHorizontally(motion, ALT_CONTROLLED_MOVE_STEP, ALT_CONTROLLED_MOVE_STEP);
        } else {
            goto done;
        }
    }
    syncSpriteToWorldPosition(self, sprite);
done: ;
}
