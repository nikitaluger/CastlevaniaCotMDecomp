extern void *gScriptEventCallbacks;
extern u8 gCameraState[];
struct GameState { u8 _0[0x18A8]; u8 frameCounter; u8 _1[0x13]; u16 activeCount; };
extern struct GameState gMainWorkspace;

struct SpawnFlags { u8 unused; u8 flags; };
struct HitFlags { u16 flags; };

extern s32 isOutsideCameraBounds(s32, s32);
extern s32 hitTestEntities(void *);
extern s32 updateObjectDisplayState(s32, void *);
extern void playSound(s32);
extern void _call_via_r1(void *, void *);
extern void _call_via_r3(void *, void *, s32, void *);
extern void stepAnimationTrack(s32, void *);
extern void advanceMotion(void *, s32);
extern void sub_08048030(s32, void *);

/* Per-frame update of a timed scripted attack: test camera bounds and hits,
 * handle the death/cancel path, dispatch one script command while the attack is
 * live, then apply gravity and place the sprite against the camera scroll. */
void updateScriptedTimedAttackObject(u8 *script)
{
    s32 sprite = *(s32 *)(script + 0x38);
    u8 *work = *(u8 **)(script + 0x3C);
    u8 *animTrack = work + 0x34;
    u8 *stepState = work + 0x48;
    u32 cameraTable, scrollXOffset, scrollYOffset;

    {
        u8 *spawnFlags = *(u8 **)(work + 0x28);
        ((struct SpawnFlags *)spawnFlags)->flags |= 5;
    }

    if (isOutsideCameraBounds(*(s32 *)(work + 8), *(s32 *)(work + 0xC)) == 1) {
        _call_via_r1(script, *(void **)(script + 0x24));
        goto done;
    }

    {
        s32 stepTimer = *(s16 *)(stepState + 0xA);
        u8 *target = *(u8 **)(work + 0x28);
        if (stepTimer == 0 || (*(u16 *)(target + 0x14) & 1) != 0) {
            if (hitTestEntities(target) != 0) {
                ((struct HitFlags *)work)->flags |= 1;
            }
        }
    }

    if (*(u16 *)work & 1) {
        u8 *stepSlot0 = (u8 *)((u32)(*(s16 *)(script + 0x22)) * 2 + (u32)script);
        if (*(u8 *)(stepSlot0 + 0x1A) != 2) {
            playSound(SCRIPT_ATTACK_DEATH_SFX);
            {
                u8 *stepSlot = (u8 *)((u32)(*(s16 *)(script + 0x22)) * 2 + (u32)script);
                *(u8 *)(stepSlot + 0x1B) = 0;
                { void **callback = &gScriptEventCallbacks;
                  _call_via_r3(script + 0x18, script + 0x22, 2, *callback); }
            }
        }
    }

    if (updateObjectDisplayState(sprite, work) != 0) goto db0;

    *(u32 *)(script + 0x14) = SCRIPT_TIMED_ATTACK_STEP_TABLE;
    *(u16 *)(script + 0x22) = *(u16 *)(script + 0x22) + 1;
    {
        u8 *stepSlot = (u8 *)((u32)(*(s16 *)(script + 0x22)) * 2 + (u32)script);
        stepSlot[0x19] = (u8)(stepSlot[0x19] + 1);
    }
    {
        s32 stepOffset = (*(s16 *)(script + 0x22)) * 2;
        u8 *scriptBase = script + 0x18;
        u8 opcode = *(scriptBase + stepOffset);
        void **stepHandlers = *(void **)(script + 0x14);
        void *stepHandler = stepHandlers[opcode];
        _call_via_r1(script, stepHandler);
    }
    *(u16 *)(script + 0x22) = *(u16 *)(script + 0x22) - 1;
    if ((*(u16 *)(script + 2) & SCRIPT_OBJ_FLAG_SKIP_ANIM) != 0) goto done;
    stepAnimationTrack(sprite, animTrack);
    advanceMotion(work, SCRIPT_TIMED_ATTACK_GRAVITY);
    goto dc8;

db0:
    if (*(s16 *)(stepState + 0xA) == 1) {
        *(s16 *)(stepState + 0xA) = 0;
        --gMainWorkspace.activeCount;
    }

dc8:
    sub_08048030(sprite, work);
    {
        u8 *target = *(u8 **)(work + 0x28);
        *(u16 *)(target + 0x14) = 0;
    }
    cameraTable = (u32)gCameraState;
    scrollXOffset = 0x1278;
    *(s32 *)((u8 *)sprite + 0x14) = *(s32 *)(work + 8) - (s32)(((*(u32 *)(cameraTable + scrollXOffset + ((gMainWorkspace.frameCounter + 1) << 6))) + 0x8000) & 0xFFFF0000);
    scrollYOffset = 0x127C;
    *(s32 *)((u8 *)sprite + 0x18) = *(s32 *)(work + 0xC) - (s32)(((*(u32 *)(cameraTable + scrollYOffset + ((gMainWorkspace.frameCounter + 1) << 6))) + 0xFFFF8000) & 0xFFFF0000);

done:
    ;
}
