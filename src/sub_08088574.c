extern void sub_08003740(s32, s32);
extern void sub_08003A6C(s32, s32, s32);
extern void sub_0806D588(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 gMainObjTimerCallback[];
extern u8 gMainWorkspace[];

/* Updates this object's sprite: in mode 1 it (re)initializes the sprite
 * animation from the table at 0x084FEC40, flips the actor's 0x10 flag, resets
 * the script step and runs the script handler; then it advances the sprite
 * timer and refreshes the actor's position from the global room data. */
void sub_08088574(void *arg0) {
    s32 zero;
    u16 flags;
    u8 *obj = (u8 *)arg0;
    u8 *base = *(u8 **)(obj + 0x6C);
    u8 *sprite = base + 4;
    s32 actor = *(s32 *)(obj + 0x38);
    u8 *statePtr = gMainWorkspace;
    s32 mode = *(s32 *)(statePtr + 0x1C);
    s32 *scriptHandlers;
    if (mode == 1) {
        sub_08003A6C((s32)(base + 0x20), 0, (s32)0x084FEC40);
        *(s32 *)(sprite + 8) = -(*(s32 *)(sprite + 8) * 2);
        flags = *(u16 *)(actor + 2);
        flags ^= 0x10;
        zero = 0;
        *(u16 *)(actor + 2) = flags;
        *(s32 *)(sprite + 0x14) = mode;
        *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = zero;
        scriptHandlers = (s32 *)0x08671BB0;
        sub_080C31E4(obj + 0x18, obj + 0x22, *scriptHandlers);
    }
    sub_08003740((s32)(base + 0x20), actor);
    sub_0806D588(actor, (s32)sprite);
}
