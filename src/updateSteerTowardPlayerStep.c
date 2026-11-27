s32 getAngleFromDelta(s32 dy, s32 dx);
void setAnimationFrame(void *sprite, void *animTrack, s32 frame, s32 mode);
void stepAnimationTrack(void *sprite, void *animTrack);
void sub_080C31E4(void *, void *, void *);

extern u8 gMainWorkspace[];
extern void *gMainObjTimerCallbacks;

/* Step a scripted object's animation; on the keyframe flag, switch to the
 * steering frame and aim its heading at the player, offset by a per-state
 * angle table value whose sign follows the bearing quadrant. Then restore
 * the render layer's layer/priority bytes and dispatch the next script step. */
void updateSteerTowardPlayerStep(void *entity)
{
    u8 *self = (u8 *)entity;
    void *sprite = *(void **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animTrack = work + 0x34;
    u8 *steer = work + 0x48;
    void **handlerSlot;
    u8 *layerA;
    u8 *layerB;
    s32 zero;

    *(u8 *)(*(u8 **)(work + 0x28) + 2) = 0;
    *(u8 *)(*(u8 **)(work + 0x28) + 3) = 0;
    stepAnimationTrack(sprite, animTrack);
    if (*(u8 *)animTrack & STEER_KEYFRAME_FLAG) {
        u8 *player;
        s32 angle;
        s32 quadrant;
        setAnimationFrame(sprite, animTrack, STEER_ANIM_FRAME, 1);
        player = gMainWorkspace;
        angle = getAngleFromDelta(*(s32 *)(player + STEER_PLAYER_Y_OFFSET) - *(s32 *)(work + 0x0C), *(s32 *)(player += STEER_PLAYER_X_OFFSET) - *(s32 *)(work + 0x08));
        quadrant = angle & 0xC000;
        if (quadrant == 0x4000) goto case_sub;
        if (quadrant > 0x4000) goto upper;
        if (quadrant == 0) goto case_add;
        goto end_adj;
    upper:
        if (quadrant == 0x8000) goto case_add;
        if (quadrant == 0xC000) goto case_sub;
        goto end_adj;
    case_add:
        player = gMainWorkspace;
        *(s32 *)(steer + STEER_HEADING_OFFSET) = getAngleFromDelta(*(s32 *)(player + STEER_PLAYER_Y_OFFSET) - *(s32 *)(work + 0x0C), *(s32 *)(player += STEER_PLAYER_X_OFFSET) - *(s32 *)(work + 0x08)) + gSteerAngleOffsets[*steer];
        goto end_adj;
    case_sub:
        player = gMainWorkspace;
        *(s32 *)(steer + STEER_HEADING_OFFSET) = getAngleFromDelta(*(s32 *)(player + STEER_PLAYER_Y_OFFSET) - *(s32 *)(work + 0x0C), *(s32 *)(player += STEER_PLAYER_X_OFFSET) - *(s32 *)(work + 0x08)) - gSteerAngleOffsets[*steer];
    end_adj:
        layerA = *(u8 **)(work + 0x28);
        zero = 0;
        *(u8 *)(layerA + 2) = STEER_LAYER_VALUE;
        layerB = *(u8 **)(work + 0x28);
        *(u8 *)(layerB + 3) = STEER_PRIORITY_VALUE;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        handlerSlot = &gMainObjTimerCallbacks;
        sub_080C31E4(self + 0x18, self + 0x22, *handlerSlot);
    }
}
