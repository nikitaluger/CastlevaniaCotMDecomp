extern void sub_08011528(void *, void *);
extern void setObjectAnimation(void *, void *, s32, s32);
extern void sub_0809C4E0(s32, s32);
extern void sub_080C31E4(void *, void *, void *);
extern void *gMainObjTimerCallbacks;

/* Enemy actor step: apply the current animation frame to the sprite, set a
 * behavior byte from an animation-indexed table, and on the animation's end
 * flag switch to frame 0xF, clear the script byte and dispatch the handler. */
void sub_0809A228(void *actor)
{
    u8 *self = (u8 *)actor;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *anim = work + 0x34;
    u8 *state = work + 0x48;
    s32 table;
    s32 entryIndex;
    s32 tableBase;
    s16 animIndex;
    u16 behavior;
    u16 *entry;

    sub_08011528(sprite, anim);
    table = *(s32 *)(anim + 0x08);
    animIndex = *(s16 *)(anim + 0x0E);
    entryIndex = (s32)animIndex + (s32)*(u8 *)(anim + 0x01);
    tableBase = *(s32 *)table;
    entry = (u16 *)(entryIndex * 4 + tableBase - 4);
    behavior = entry[1];
    if (behavior == 0x54) {
        sub_0809C4E0(*(s32 *)(state + 0x08), 3);
    } else if (behavior == 0x4B) {
        sub_0809C4E0(*(s32 *)(state + 0x08), 2);
    } else {
        sub_0809C4E0(*(s32 *)(state + 0x08), 0);
    }
    if ((*(u8 *)anim & 2) != 0) {
        setObjectAnimation(sprite, anim, 0xF, 0);
        sub_0809C4E0(*(s32 *)(state + 0x08), 0);
        animIndex = *(s16 *)(self + 0x22);
        self[animIndex * 2 + 0x19] = 0;
        {
            void **handlerTable = &gMainObjTimerCallbacks;
            sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
        }
    }
}
