/* Run an entity's AI step: when flagged, aim the actor at the player with a
 * jittered angle and take its immediate script branch; otherwise advance the
 * animation and project the actor's motion into the world. */
extern s32 sub_0800583C(s32);
extern s32 sub_08005910(s32, s32);
extern void stepAnimationTrack(void *, void *);
extern void setSpriteFlipForDirection(void *, s32);
extern void sub_080146D0(void *, s32, s32);
extern void sub_080BC73C(void *, void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *gMainObjTimerCallbacks;

struct S_02025FF0 {
    u8 pad[0x174C];
    s32 field174C;
    s32 field1750;
};
extern struct S_02025FF0 gMainWorkspace;

void sub_080BC628(void *arg0) {
    void *script;
    u8 *actor;
    u8 *actorMotion;
    s16 stepIndex;
    u8 *entity;

    entity = (u8 *)arg0;
    script = *(void **)(entity + 0x38);
    actor = *(u8 **)(entity + 0x3C);
    actorMotion = actor + 0x34;

    if (*(s32 *)(entity + 0x9C) != 0) {
        s32 targetDx, targetDy, angle;
        u8 *stepPtr;
        void **scriptTable;

        targetDx = gMainWorkspace.field1750 - *(s32 *)(actor + 0x0C);
        targetDy = gMainWorkspace.field174C - *(s32 *)(actor + 0x08);
        angle = sub_08005910(targetDx, targetDy);
        angle += sub_0800583C(0x1800);
        sub_080146D0(actor, angle, 0x20000);
        setSpriteFlipForDirection(script, *(s32 *)(actor + 0x10));

        stepIndex = *(s16 *)(entity + 0x22);
        *(u8 *)(entity + stepIndex * 2 + 0x19) = 0;

        scriptTable = &gMainObjTimerCallbacks;
        stepPtr = entity + 0x18;
        sub_080C31E4(stepPtr, entity + 0x22, *scriptTable);

        stepIndex = *(s16 *)(entity + 0x22);
        {
            s32 b;
            b = *(u8 *)(entity + stepIndex * 2 + 0x19) + 1;
            *(u8 *)(entity + stepIndex * 2 + 0x19) = b;
        }

        stepIndex = *(s16 *)(entity + 0x22);
        stepPtr += stepIndex * 2;
        {
            u8 stepByte = *stepPtr;
            u32 *table = *(u32 **)(entity + 0x14);
            sub_080C31E0(arg0, (void *)table[stepByte]);
        }
    } else {
        (void)actorMotion;
        stepAnimationTrack(script, actorMotion);
        *(s32 *)(entity + 0x5C) += 0x600;
        *(s32 *)(entity + 0x7C) += *(s32 *)(entity + 0x8C);
        sub_080BC73C(arg0, script, actor);
    }
}
