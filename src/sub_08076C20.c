extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void releaseActorEffectParts(void);
extern u8 gMainWorkspace[];
extern s32 gMainObjTimerCallbacks;

struct T55 { u8 pad[0x55]; u8 f55; };

/* Initializes the child object stored at obj+0x6C from global game state: clears its
 * work fields, copies state bytes/values in, installs the cleanup callback on obj,
 * then advances the script step (obj+0x22) and dispatches the next handler from
 * obj's behavior table at +0x14.
 */
void sub_08076C20(u8 *obj) {
    u32 zero;
    u8 *child;
    u8 *childData;
    u8 *src;
    struct T55 *childFull;
    u8 *state;
    s32 vel;
    u16 flip;
    s32 *msgPtr;
    u8 *step;
    u8 handler;
    s16 stepIdx;

    child = *(u8 **)(obj + 0x6C);
    childData = child + 4;
    src = *(u8 **)(obj + 0x38);
    zero = 0;

    *(u32 *)(childData + 0x2C) = zero;
    *(u32 *)(childData + 0x30) = zero;
    *(u32 *)(childData + 0x34) = zero;
    *(u32 *)(childData + 0x38) = zero;
    *(u32 *)(childData + 0x3C) = zero;
    *(u32 *)(childData + 0x18) = *(u32 *)(obj + 0x24);
    *(u32 *)(obj + 0x24) = (u32)&releaseActorEffectParts;

    state = gMainWorkspace;
    childFull = (struct T55 *)child;
    childFull->f55 = *(state + 0x14EF);

    *(s32 *)(child + 4) = *(s32 *)(state + 0x1728);
    *(s32 *)(childData + 4) = *(s32 *)(state + 0x172C);

    flip = *(u16 *)(src + 2) & 0x10;
    vel = 0x80 << 11;
    if (flip) vel = (s32)0xFFFC0000;
    *(s32 *)(childData + 8) = vel;

    *(u32 *)(childData + 0x0C) = zero;
    *(u32 *)(childData + 0x54) = 5;

    stepIdx = *(s16 *)(obj + 0x22);
    *(u8 *)(obj + stepIdx * 2 + 0x19) = zero;

    msgPtr = &gMainObjTimerCallbacks;
    step = obj;
    step += 0x18;
    sub_080C31E4(step, obj + 0x22, *msgPtr);

    *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) + 1;

    step += *(s16 *)(obj + 0x22) * 2;
    handler = *step;
    sub_080C31E0(obj, *(s32 *)(handler * 4 + *(u32 *)(obj + 0x14)));
}
