extern s32 isOutsideCameraBounds(s32, s32);
extern s32 updateObjectDisplayState(void *, void *);
extern s32 sub_080C31E0(s32, s32);
extern void stepAnimationTrack(void *, void *);
extern void sub_080507E0(void *, void *);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gObjectKindEffectStepTable[];

struct SubFlag { u8 a; u8 flag; };
struct MainFlag { u8 flag; };
struct StateFlag { u16 flag; };

/* Update a camera-driven effect: refresh its visibility and animation state,
   advance the script when the animation helper allows it, and copy the state
   coordinates into the main object. */
/* Per-frame update of a spawned object-kind effect: refresh hit/visibility flags from the camera bounds, dispatch one script step (unless display handling consumed the frame), advance its animation, restore the render-layer attributes and place the sprite at the work state's world coords minus camera scroll. */ void updateObjectKindEffectSteps(u8 *object) {
    u8 *sprite;
    u8 *work;
    u8 *animTrack;
    struct SubFlag *target;
    u8 *stepSlot;
    u8 *scrollTable;
    u8 *frameCounter;
    u8 *scrollXBase;
    u32 scrollOffset;
    u32 scrollX;
    u32 scrollY;
    u32 stepOpcode;
    u8 *stepStream;
    s32 stepOffset;

    sprite = *(u8 **)(object + 0x38);
    work = *(u8 **)(object + 0x3C);
    animTrack = work + 0x34;
    target = *(struct SubFlag **)(work + 0x28);
    target->flag |= 1;
    {
        u8 zero = 0;
        if (isOutsideCameraBounds(*(s32 *)(work + 8), *(s32 *)(work + 0xC)) == 1) {
            ((struct MainFlag *)(sprite + 0x2A))->flag &= 0xBF;
            ((struct SubFlag *)(*(u8 **)(work + 0x28)))->flag = zero;
        } else {
            ((struct MainFlag *)(sprite + 0x2A))->flag |= 0x40;
            ((struct SubFlag *)(*(u8 **)(work + 0x28)))->flag = 1;
        }
    }

    if (*(u16 *)(*(u8 **)(work + 0x28) + 0x14) & 1) {
        ((struct StateFlag *)work)->flag |= 1;
    }

    if (updateObjectDisplayState(sprite, work) != 0) goto common;

    *(u32 *)(object + 0x14) = (u32)gObjectKindEffectStepTable;
    *(u16 *)(object + 0x22) = *(u16 *)(object + 0x22) + 1;
    stepSlot = (u8 *)((u32)(*(s16 *)(object + 0x22)) * 2 + (u32)object);
    *(u8 *)(stepSlot + 0x19) = *(u8 *)(stepSlot + 0x19) + 1;
    stepOffset = *(s16 *)(object + 0x22) * 2;
    stepStream = object;
    stepStream += 0x18;
    stepOpcode = *(u8 *)((u32)stepStream + (u32)stepOffset);
    sub_080C31E0((s32)object, *(u32 *)(*(u32 *)(object + 0x14) + stepOpcode * 4));
    *(u16 *)(object + 0x22) = *(u16 *)(object + 0x22) - 1;
    if ((*(u16 *)(object + 2) & 0x8000) != 0) return;
    stepAnimationTrack(sprite, animTrack);

common:
    sub_080507E0(sprite, work);

    scrollTable = gCameraState;
    frameCounter = gMainWorkspace;
    frameCounter += 0x18A8;
    scrollOffset = ((u32)*frameCounter + 1) * 0x40;
    scrollXBase = scrollTable + 0x1278;
    scrollX = *(u32 *)(scrollXBase + scrollOffset);
    *(u32 *)(sprite + 0x14) = *(u32 *)(work + 8) - ((scrollX + 0x8000) & 0xFFFF0000);
    scrollOffset = ((u32)*frameCounter + 1) * 0x40;
    scrollTable += 0x127C;
    scrollY = *(u32 *)(scrollTable + scrollOffset);
    *(u32 *)(sprite + 0x18) = *(u32 *)(work + 0xC) - ((scrollY + 0xFFFF8000) & 0xFFFF0000);
}
