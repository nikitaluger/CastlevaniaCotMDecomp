/* Per-frame update for one actor: drop it when it leaves the camera's view,
 * sync a few animation/status flags, advance a scripted action dispatched
 * through D_0866D78C, then (on the common path) refresh the sprite's
 * camera-relative screen position. */
extern s32 isOutsideCameraBounds(s32, s32);
extern s32 updateObjectDisplayState(void *, void *);
extern void stepAnimationTrack(void *, void *);
extern void advanceMotion(void *, s32);
extern void sub_0801EF8C(void *, void *);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u32 sScriptStepCallbacks[];
extern u32 D_0866D78C[];

struct ActorBits { u8 unk0; u8 flags; };
struct AnimState { u16 flags; };
struct CoordTable { u8 _0[0x1278]; u32 camX; u32 camY; };
extern struct CoordTable gCameraState;
struct CameraInfo { u8 _0[0x18A8]; u8 index; };
extern struct CameraInfo gMainWorkspace;

void sub_0801ED28(u8 *entity) {
    u8 *anim;
    u8 *actor;
    u8 *actorTarget;
    u8 *countdown;
    u8 *child;
    s32 frameOffset;
    u8 *patternBase;
    u8 patternValue;
    u8 *coordBase;
    u32 coordField;
    u32 *actionData;
    s16 frameIndex;
    u16 *entityWords;

    anim = *(u8 **)(entity + 0x38);
    actor = *(u8 **)(entity + 0x3C);
    actorTarget = actor + 0x34;
    countdown = actor + 0x48;
    ((struct ActorBits *)*(u32 *)(actor + 0x28))->flags |= 1;

    if (*(s16 *)countdown <= 0) {
        if (isOutsideCameraBounds(*(s32 *)(actor + 0x08), *(s32 *)(actor + 0x0C)) == 1) {
            sub_080C31E0((s32)entity, *(u32 *)(entity + 0x24));
            return;
        }
    }

    if (*(u16 *)(entity + 0x5C) & 0x02)
        ((struct AnimState *)actor)->flags |= 0x01;

    if (*(u16 *)actor & 0x01) {
        ((struct ActorBits *)*(u32 *)(actor + 0x28))->flags &= 0xFB;
        child = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        if (child[0x1A] != 2) {
            child[0x1B] = 0;
            actionData = sScriptStepCallbacks;
            sub_080C31E8(entity + 0x18, entity + 0x22, 2, *actionData);
        }
    }

    if (updateObjectDisplayState(anim, actor) != 0)
        goto common;

    *(u32 *)(entity + 0x14) = (u32)D_0866D78C;
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
    frameIndex = *(s16 *)(entity + 0x22);
    entityWords = (u16 *)entity;
    ((u8 *)(&entityWords[frameIndex]))[0x19] = ((u8 *)(&entityWords[frameIndex]))[0x19] + 1;
    frameOffset = *(s16 *)(entity + 0x22) * 2;
    patternBase = entity + 0x18;
    patternValue = patternBase[frameOffset];
    sub_080C31E0((s32)entity, *(u32 *)(*(u32 *)(entity + 0x14) + patternValue * 4));
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
    if ((*(u16 *)(entity + 2) & 0x8000) != 0)
        goto end;
    stepAnimationTrack(anim, actorTarget);
    advanceMotion(actor, 0);

common:
    sub_0801EF8C(anim, actor);
    coordBase = (u8 *)&gCameraState;
    coordField = 0x1278;
    *(u32 *)(anim + 0x14) = *(u32 *)(actor + 8) - ((*(u32 *)(coordBase + coordField + ((gMainWorkspace.index + 1) << 6)) + 0x8000) & 0xFFFF0000);
    coordField = 0x127C;
    *(u32 *)(anim + 0x18) = *(u32 *)(actor + 0x0C) - ((*(u32 *)(coordBase + coordField + ((gMainWorkspace.index + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000);
end:
    ;
}
