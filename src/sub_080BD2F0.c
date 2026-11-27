/* If an entity's trigger flag is set, flag its sprite, refresh its animation,
 * mark several sub-states active, and advance its script by firing the next
 * callback; otherwise just clear the sprite flag. */
extern s32 forceAnimationFrame(void *, void *, s32, s32);
extern void setSpriteFlipForDirection(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *gScriptStepCallbackTable;

struct P2A { u8 pad[0x2A]; u8 f2A; };
static inline u8 zero8(void) { return 0; }

void sub_080BD2F0(void *arg0)
{
    s16 scriptIndex;
    u8 *scriptData;
    u8 *sprite;
    u8 *motion;
    u8 *animState;
    u8 **steerPtr;
    s32 zero;

    sprite = *(u8 **)((u8 *)arg0 + 0x38);
    motion = *(u8 **)((u8 *)arg0 + 0x3C);
    animState = motion + 0x34;
    steerPtr = (u8 **)(motion + 0x48);

    if (*(u32 *)((u8 *)arg0 + 0x4C) != 0) {
        {
            struct P2A *spriteFlags = (struct P2A *)sprite;
            spriteFlags->f2A |= 0x40;
            zero = zero8();
        }
        forceAnimationFrame(sprite, animState, 0x1C, 0);
        *(u8 *)(*(u8 **)(motion + 0x28) + 1) = 1;
        *(u8 *)(*steerPtr + 1) = 1;
        *(u8 *)(steerPtr[1] + 1) = 1;
        setSpriteFlipForDirection(sprite, *(s32 *)((u8 *)arg0 + 0x6C));
        *(s32 *)(motion + 8) = *(s32 *)((u8 *)arg0 + 0x5C);
        scriptIndex = *(s16 *)((u8 *)arg0 + 0x22);
        ((u8 *)arg0)[scriptIndex * 2 + 0x19] = zero;
        {
            void **callbacks = &gScriptStepCallbackTable;
            scriptData = (u8 *)arg0 + 0x18;
            sub_080C31E4(scriptData, (u8 *)arg0 + 0x22, *callbacks);
        }
        scriptIndex = *(s16 *)((u8 *)arg0 + 0x22);
        ((u8 *)arg0)[scriptIndex * 2 + 0x19]++;
        scriptIndex = *(s16 *)((u8 *)arg0 + 0x22);
        scriptData = scriptData + scriptIndex * 2;
        sub_080C31E0(arg0, *(void **)(*(u32 *)((u8 *)arg0 + 0x14) + scriptData[0] * 4));
    } else {
        sprite[0x2A] &= 0xBF;
    }
}
