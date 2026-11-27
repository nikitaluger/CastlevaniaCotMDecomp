/* Per-frame update for one actor: handle off-screen and sub-state changes,
 * run a scripted action from D_0866E804, then refresh the sprite's camera-
 * relative Y screen position. */
#define ACTION_STATE(e) (*(u8 *)((e) + (*(s16 *)((e) + 0x22)) * 2 + 0x1A))
#define ACTION_FLAG(e) (*(u8 *)((e) + (*(s16 *)((e) + 0x22)) * 2 + 0x1B))
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866E804[];
extern u32 sScriptStepCallbacks[];

s32 sub_080141AC(void*, void*);
void sub_08013C5C(void*, void*);
s32 sub_08013558(void*, void*, void*);
void sub_08013978(void*, void*);
void sub_080142C0(void*, void*);
void sub_08013AC4(void*);
void sub_08005E80(u32);
void sub_080C31E8(void*, void*, s32, u32);
s32 updateObjectDisplayState(void*, void*);
void sub_080C31E0(void*, s32);
void stepAnimationTrack(void*, void*);
void moveObjectHorizontally(void*, s32, s32);
void sub_08013C8C(void*, void*);

void sub_08057E94(u8 *entity) {
    u8 *anim;
    u8 *actor;
    u8 *actorTarget;
    u8 *actorEx;
    u8 *frameEntry;
    u8 *coordBase;
    u8 *camIndexPtr;
    u8 *patternBase;
    u32 *actionData;
    u8 patternValue;
    s32 frameOffset;
    u32 camYAdjusted;
    u32 coordOffset;
    u32 camIndex;

    anim = *(u8 **)(entity + 0x38);
    actor = *(u8 **)(entity + 0x3C);
    actorTarget = actor + 0x34;
    actorEx = actor + 0x48;

    if (sub_080141AC(anim, actor) == 1) {
        return;
    }

    sub_08013C5C(entity, anim);

    if (sub_08013558(anim, actor, *(void **)(actor + 0x28)) != 0) {
        sub_08013978(entity, *(void **)(actor + 0x28));
        if (((*(u16 *)actor) & 0x0D) == 0) {
            *(u16 *)(actorEx + 0x04) = 0x0A;
        }
    }

    sub_080142C0(entity, *(void **)(actor + 0x28));

    if ((*(u16 *)actor & 0x01)) {
        if (ACTION_STATE(entity) != 1) {
            sub_08013AC4(entity);
            sub_08005E80(0x85);
            ACTION_FLAG(entity) = 0;
            actionData = sScriptStepCallbacks;
            sub_080C31E8(entity + 0x18, entity + 0x22, 1, *actionData);
        }
    }

    if (updateObjectDisplayState(anim, actor) == 0) {
        *(u32 *)(entity + 0x14) = (u32)D_0866E804;
        *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
        frameEntry = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        *(u8 *)(frameEntry + 0x19) = *(u8 *)(frameEntry + 0x19) + 1;
        frameOffset = *(s16 *)(entity + 0x22);
        frameOffset = frameOffset * 2;
        patternBase = entity;
        patternBase += 0x18;
        patternValue = *(u8 *)((u32)patternBase + (u32)frameOffset);
        sub_080C31E0(entity, *(u32 *)(*(u32 *)(entity + 0x14) + patternValue * 4));
        *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
        if (!((*(u16 *)(entity + 0x02)) & 0x8000)) {
            stepAnimationTrack(anim, actorTarget);
            moveObjectHorizontally(actor, 0x100000, 0x100000);
        } else {
            return;
        }
    }

    sub_08013C8C(entity, anim);

    coordBase = gCameraState;
    camIndexPtr = gMainWorkspace;
    camIndexPtr += 0x18A8;
    camIndex = *(u8 *)camIndexPtr;
    camIndex = camIndex + 1;
    coordOffset = camIndex << 6;
    coordBase += 0x127C;
    camYAdjusted = *(u32 *)(coordBase + coordOffset);
    camYAdjusted = camYAdjusted + 0xFFFF8000;
    camYAdjusted = camYAdjusted & 0xFFFF0000;
    camYAdjusted = camYAdjusted + 0x10000;
    *(u32 *)(anim + 0x18) = *(s32 *)(actor + 0x0C) - camYAdjusted;
}
