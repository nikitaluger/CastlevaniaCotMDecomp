/*
 * Actor animation-frame action: switch the actor's animation to a fixed frame,
 * advance it one tick, play a sound effect when the new frame carries a trigger
 * marker, and dispatch the actor callback while the busy flag is set.
 */
typedef s32 M2C_UNK;
M2C_UNK sub_08005E80(s32);
M2C_UNK setObjectAnimation(s32, s32, s32, s32);
M2C_UNK sub_08011528(s32, s32);
M2C_UNK sub_080C31E4(void *, void *, s32);

/* A frame-table entry is 4 bytes; its property word lives at offset +2. */
struct FrameProp { u8 _pad[2]; u16 value; };
struct FramePropVol { u8 _pad[2]; volatile u16 value; };

/* The action's fixed frame, the property that fires the sound, and its SFX id. */
#define ACTION_FRAME    0x3B
#define TRIGGER_PROP    0x28
#define ACTION_SFX      0x18B
#define ANIM_BUSY_FLAG  2

#define FRAME_ADDR(anim, tbl) \
    ((((*(s16 *)((s8 *)(anim) + 0xE) + *(u8 *)((s8 *)(anim) + 1)) * 4) + *(tbl)) - 4)
#define FRAME_PROP(anim, tbl)     (((struct FrameProp *)FRAME_ADDR(anim, tbl))->value)
#define FRAME_PROP_NOW(anim, tbl) (((struct FramePropVol *)FRAME_ADDR(anim, tbl))->value)

void sub_080B3BDC(void *actor)
{
    s32 animOwner;
    u16 propBefore;
    s32 anim;
    u16 propAfter;
    s32 *frameTablePtr;
    int callbackTable;

    animOwner = *((s32 *)(((s8 *)actor) + 0x38));
    anim = *((s32 *)(((s8 *)actor) + 0x3C)) + 0x34;
    frameTablePtr = *(s32 **)((s8 *)anim + 8);
    propBefore = FRAME_PROP(anim, frameTablePtr);
    setObjectAnimation(animOwner, anim, ACTION_FRAME, 0);
    sub_08011528(animOwner, anim);
    frameTablePtr = *(s32 **)((s8 *)anim + 8);
    propAfter = FRAME_PROP_NOW(anim, frameTablePtr);
    if (propBefore != propAfter && propAfter == TRIGGER_PROP) {
        sub_08005E80(ACTION_SFX);
    }
    if (ANIM_BUSY_FLAG & *((u8 *)((s8 *)anim + 0))) {
        *((s8 *)(((s8 *)(((*((s16 *)(((s8 *)actor) + 0x22))) * 2) + actor)) + 0x19)) = 0;
        callbackTable = 0x08671BB0;
        sub_080C31E4(actor + 0x18, actor + ((unsigned int)0x22), *((s32 *)callbackTable));
    }
}
