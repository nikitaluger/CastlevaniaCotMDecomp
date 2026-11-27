extern s32 isOutsideCameraBounds(s32, s32);
extern s32 absXFromFocus(s32);
extern s32 absYFromFocus(s32);
extern void *allocMotionTracker(void);
extern void freeMotionTracker(void *);
extern s32 sub_080C31E0(s32, s32);
extern void advanceMotion(void *, s32);
extern void stepAnimationTrack(void *, void *);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/* Updates a tracked-behaviour weapon sprite: hide or show it from the camera-bounds
 * check, create or free its motion tracker by distance from the focus point, dispatch
 * the current script step through the state-handler table, then copy the animation
 * and camera-corrected world position back onto the sprite. */
void updateTrackedBehaviorSprite(u8 *entity) {
    u8 *renderSprite;
    u8 *work;
    void *animTrack;
    struct TrackedBehaviorWork *behavior;
    s32 outsideView;
    u8 *stepSlot;
    u8 *scrollTable;
    u8 *scrollXRow;
    u8 *frameCounter;
    u32 scrollRow;
    u32 scrollX;
    u32 scrollY;
    u8 *stepStream;
    s32 stepOffset;
    u8 stepOpcode;
    void *oldTracker;
    u32 fracMask;
    u8 *trackerYField;

    renderSprite = *(u8 **)(entity + 0x38);
    work = *(u8 **)(entity + 0x3C);
    animTrack = (void *)(work + 0x34);
    behavior = (struct TrackedBehaviorWork *)(work + 0x48);

    outsideView = isOutsideCameraBounds(*(s32 *)(work + 0x08), *(s32 *)(work + 0x0C));
    if (outsideView == 1) {
        behavior->tracker->state = TRACKER_STATE_HIDDEN;
        ((struct AttackSpriteFlags *)(renderSprite + 0x2A))->flag &= ATTACK_SPRITE_SHOW_MASK;
    } else {
        behavior->tracker->state = TRACKER_STATE_ACTIVE;
        ((struct AttackSpriteFlags *)(renderSprite + 0x2A))->flag |= ATTACK_SPRITE_HIDE_FLAG;
    }

    if (absXFromFocus(*(s32 *)(work + 0x08)) <= TRACKER_ACTIVE_DISTANCE &&
        absYFromFocus(*(s32 *)(work + 0x0C)) <= TRACKER_ACTIVE_DISTANCE) {
        oldTracker = behavior->tracker;
        if (oldTracker == 0) {
            void *tracker = allocMotionTracker();
            behavior->tracker = tracker;
            if (tracker == 0) {
                sub_080C31E0((s32)entity, *(s32 *)(entity + 0x24));
                return;
            }
            {
                u8 *trackerBytes = (u8 *)tracker;
                trackerBytes[1] = TRACKER_STATE_ACTIVE;
                behavior->tracker->previous = (u16)(u32)oldTracker;
                behavior->tracker->kind = 0x10;
                behavior->tracker->layer = 0x10;
                behavior->tracker->owner = entity;
            }
        }
    } else {
        void *tracker = behavior->tracker;
        if (tracker != 0) {
            freeMotionTracker(tracker);
            behavior->tracker = 0;
        }
    }

    *(u32 *)(entity + SCRIPT_STEP_TABLE_OFFSET) = (u32)TRACKER_STATE_HANDLERS;
    *(u16 *)(entity + BEHAVIOR_STEP_INDEX_OFFSET) = *(u16 *)(entity + BEHAVIOR_STEP_INDEX_OFFSET) + 1;
    stepSlot = (u8 *)((u32)(*(s16 *)(entity + BEHAVIOR_STEP_INDEX_OFFSET)) * 2 + (u32)entity);
    *(u8 *)(stepSlot + BEHAVIOR_STEP_TIME_OFFSET) = *(u8 *)(stepSlot + BEHAVIOR_STEP_TIME_OFFSET) + 1;
    stepOffset = *(s16 *)(entity + BEHAVIOR_STEP_INDEX_OFFSET) * 2;
    stepStream = entity;
    stepStream += BEHAVIOR_STEP_BASE_OFFSET;
    stepOpcode = *(u8 *)((u32)stepStream + (u32)stepOffset);
    sub_080C31E0((s32)entity, *(u32 *)(*(u32 *)(entity + SCRIPT_STEP_TABLE_OFFSET) + stepOpcode * 4));
    *(u16 *)(entity + BEHAVIOR_STEP_INDEX_OFFSET) = *(u16 *)(entity + BEHAVIOR_STEP_INDEX_OFFSET) - 1;

    if ((*(u16 *)(entity + 2) & SCRIPT_OBJ_FLAG_SKIP_ANIM) == 0) {
        advanceMotion(work, 0);
        if (*(s16 *)((u8 *)behavior + 0x10) == 1) {
            stepAnimationTrack(renderSprite, animTrack);
        }
        behavior->tracker->animX = *(u16 *)(work + 0x0A);
        trackerYField = (u8 *)behavior->tracker + 6;
        fracMask = BEHAVIOR_FRAC_MASK;
        *(u16 *)trackerYField = *(u16 *)(work + 0x0E) + 1;
        scrollTable = gCameraState;
        frameCounter = gMainWorkspace;
        frameCounter += BEHAVIOR_WORKSPACE_COUNTER;
        scrollRow = ((u32)*frameCounter + 1) * BEHAVIOR_SCROLL_STEP;
        scrollXRow = scrollTable + BEHAVIOR_SCROLL_X_OFFSET;
        scrollX = *(u32 *)(scrollXRow + scrollRow);
        *(u32 *)(renderSprite + 0x14) = *(u32 *)(work + 0x08) - ((scrollX + BEHAVIOR_SCROLL_BIAS_X) & fracMask);
        scrollRow = ((u32)*frameCounter + 1) * BEHAVIOR_SCROLL_STEP;
        scrollTable += BEHAVIOR_SCROLL_Y_OFFSET;
        scrollY = *(u32 *)(scrollTable + scrollRow);
        *(u32 *)(renderSprite + 0x18) = *(u32 *)(work + 0x0C) - ((scrollY + BEHAVIOR_SCROLL_BIAS_Y) & fracMask);
    }
}
