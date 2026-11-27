/* Copy the mover's world position and facing into its sprite descriptor,
 * change the animation frame when the requested pose changed, fire a queued
 * child spawn, then write camera-relative screen coordinates back. */

extern u8 gCameraState[];
extern struct MotionEntityWorkspace gMainWorkspace;
extern s16 gPoseFrameIndices[];
extern struct MotionSpawnOffset gSpawnOffsets[];
void setSpriteFlipForDirection(void *, u32);
void forceAnimationFrame(void *, u32, s16, u32);
void copyPoseOffsetForFrame(u32, u32);
void spawnPositionedEffect(u32, u32);
void spawnPositionedEffectWithParam(u32, u32, u16, s32);

void updateEntityMotionAndSpawn(void *arg) {
    struct MotionEntity *entity = arg;
    struct MotionEntitySprite *sprite = entity->sprite;
    struct MotionEntityMover *mover = entity->mover;
    u8 *scrollState;
    u8 *scrollXTable;
    u8 *scrollYTable;
    u32 animTrack = 0x34 + (u32)mover;
    u32 spawnX, spawnY, originX;
    u32 scrollIndex;

    mover->x = entity->worldX;
    mover->y = entity->worldY;
    mover->facing = entity->facing;
    sprite->pose = entity->pose;
    setSpriteFlipForDirection(sprite, mover->facing);
    if ((s8)entity->shownPose != (s8)entity->wantedPose) {
        entity->shownPose = entity->wantedPose;
        forceAnimationFrame(sprite, animTrack, gPoseFrameIndices[(s32)(s8)entity->wantedPose], 0);
    }
    if (entity->spawnRequest != MOTION_SPAWN_NONE) {
        originX = mover->x;
        if ((sprite->flags & ORIGIN_FLIP_X) != 0) {
            spawnX = originX + gSpawnOffsets[entity->spawnRequest - 1].dx;
        } else {
            spawnX = originX - gSpawnOffsets[entity->spawnRequest - 1].dx;
        }
        spawnY = mover->y + gSpawnOffsets[entity->spawnRequest - 1].dy;
        switch (entity->spawnRequest) {
        case MOTION_SPAWN_POSITION:
            spawnPositionedEffect(spawnX, spawnY);
            break;
        case MOTION_SPAWN_PARAM:
            spawnPositionedEffectWithParam(spawnX, spawnY, (u16)(0x1000 + entity->pose), (sprite->flags & ORIGIN_FLIP_X) ? MOTION_SPAWN_DIR_RIGHT : MOTION_SPAWN_DIR_LEFT);
            break;
        }
        entity->spawnRequest = MOTION_SPAWN_NONE;
    }
    copyPoseOffsetForFrame(animTrack, mover->linkData);
    scrollState = gCameraState;
    scrollIndex = (gMainWorkspace.frame + 1) * BEHAVIOR_SCROLL_STEP;
    scrollXTable = scrollState + BEHAVIOR_SCROLL_X_OFFSET;
    sprite->screenX = mover->x - ((*(u32 *)(scrollXTable + scrollIndex) + BEHAVIOR_SCROLL_BIAS_X) & BEHAVIOR_FRAC_MASK);
    scrollIndex = (gMainWorkspace.frame + 1) * BEHAVIOR_SCROLL_STEP;
    scrollYTable = scrollState + BEHAVIOR_SCROLL_Y_OFFSET;
    sprite->screenY = mover->y - ((*(u32 *)(scrollYTable + scrollIndex) + BEHAVIOR_SCROLL_BIAS_Y) & BEHAVIOR_FRAC_MASK);
}
