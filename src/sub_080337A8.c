void sub_08011344(void *, void *, s16, s32);
void stepAnimationTrack(void *, void *);
void sub_08033950(void *, void *);
void copyBytes(void *, void *, u32);
void sub_080C31E4(void *, void *, s32);
extern s32 D_080CECBC[];

struct PathSpriteFlags { u8 pad[0x2A]; u8 flags; };

/* Per-frame update for an entity following a movement path: enable its
 * animation, drive its velocity from the path tables, step its animation
 * tracks, and dispatch the script callback when the path step wraps. */
void sub_080337A8(void *entity) {
    s16 frameSeq[0x2A / 2];
    void *state;
    void *sprite;
    void *animTrack;
    u8 *step;
    s32 *velTable;
    s32 *velTableNext;
    s32 *scriptFunc;
    u8 active;
    u32 nextStep;
    s32 newVel;
    u32 zero;
    s32 index;
    s32 offset;

    sprite = *(void **)((u8 *)entity + 0x38);
    state = *(void **)((u8 *)entity + 0x3C);
    animTrack = (u8 *)state + 0x34;
    step = (u8 *)state + 0x48;
    copyBytes(frameSeq, (void *)0x080CED8A, 0x2A);
    active = *(u8 *)((u8 *)entity + 0x7C);
    if (active == 0) {
        *(u8 *)(*(void **)((u8 *)state + 0x28) + 1) = active;
        *(u8 *)((u8 *)sprite + 0x2A) = (u8)(*(u8 *)((u8 *)sprite + 0x2A) & 0xBF);
        return;
    }
    *(u8 *)(*(void **)((u8 *)state + 0x28) + 1) = 1;
    ((struct PathSpriteFlags *)sprite)->flags |= 0x40;
    *(u16 *)sprite = *(u16 *)((u8 *)entity + 0x6C);
    *(u16 *)((u8 *)sprite + 0x02) = *(u16 *)((u8 *)entity + 0x74);
    if (*(u8 *)((u8 *)entity + 0x84) == 0) {
        newVel = *(s32 *)((u8 *)entity + 0x4C) + D_080CECBC[*step * 2];
    } else {
        newVel = *(s32 *)((u8 *)entity + 0x4C) - D_080CECBC[*step * 2];
    }
    *(s32 *)((u8 *)state + 0x08) = newVel;
    velTable = D_080CECBC;
    index = *step * 2;
    offset = index * 4;
    velTableNext = velTable + 1;
    *(s32 *)((u8 *)state + 0x0C) = *(s32 *)((u8 *)entity + 0x5C) + *(s32 *)((u8 *)velTableNext + offset);
    sub_08011344(sprite, animTrack, frameSeq[*step], 0);
    stepAnimationTrack(sprite, animTrack);
    sub_08033950(sprite, state);
    nextStep = *step + 1;
    zero = 0;
    *step = nextStep;
    if ((u8)nextStep == 0x15) {
        *(u8 *)(*(void **)((u8 *)state + 0x28) + 1) = zero;
        *step = zero;
        *(u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity + 0x19) = zero;
        scriptFunc = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *scriptFunc);
    }
}
