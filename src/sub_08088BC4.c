extern void stepDelayTimer(s32, s32);
extern void startEffectTimer(s32, s32, s32);
extern void sub_0806D588(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 gMainObjTimerCallbacks[];
extern u8 gMainWorkspace[];

struct F02 { u8 pad[2]; u16 f02; };
static inline s32 zero32(void) { return 0; }

/* Updates this object's sprite: in mode 1 it (re)initializes the sprite
 * animation from the table at 0x084FEBF8, sets the actor's 0x10 flag, resets
 * the script step and runs the script handler; then it advances the sprite
 * timer and refreshes the actor's position from the global room data. */
void sub_08088BC4(void *arg0) {
    s32 unused;
    u8 *obj = (u8 *)arg0;
    u8 *base = *(u8 **)(obj + 0x6C);
    u8 *sprite = base + 4;
    s32 actor = *(s32 *)(obj + 0x38);
    u8 *statePtr = gMainWorkspace;
    s32 mode = *(s32 *)(statePtr + 0x1C);
    s32 *scriptHandlers;
    if (mode == 1) {
        startEffectTimer((s32)(base + 0x20), 0, (s32)0x084FEBF8);
        {
            struct F02 *flags = (struct F02 *)actor;
            s32 zero;
            flags->f02 |= 0x10;
            zero = zero32();
            *(s32 *)(sprite + 8) = 0xFFFF0000;
            *(s32 *)(sprite + 0x14) = mode;
            *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = zero;
            scriptHandlers = (s32 *)0x08671BB0;
        }
        sub_080C31E4(obj + 0x18, obj + 0x22, *scriptHandlers);
    }
    stepDelayTimer((s32)(base + 0x20), actor);
    sub_0806D588(actor, (s32)sprite);
}
