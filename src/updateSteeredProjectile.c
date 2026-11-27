s32 checkGlobalStateChange(void *, void *, void *);
void sub_0806D588(void *, void *);
void cullOffscreenEntity(void *, void *);
void spawnKind2CEntity(void *, s32, s32, s32);
void setDirectionVector(void *, u32);
void turnHeadingToward(void *, s32, s32, void *);
void sub_080C31E4(void *, void *, void *);
void sub_080C31E0(void *, void *);

extern void *gMainObjTimerCallbacks;

/*
 * Per-frame update for a projectile-like actor: run the common condition and
 * lifetime checks, steer/position it from its work state, refresh the sprite
 * relative to the camera, emit its trail and cull it once off screen.
 */
void updateSteeredProjectile(void *actor)
{
    u8 *a = (u8 *)actor;
    u8 *state = *(u8 **)(a + 0x6C);
    u8 *workTail = state + 4;
    u8 *sprite = *(u8 **)(a + 0x38);
    u8 *work = workTail;
    s32 check;

    *(s32 *)(work + 0x10) += 1;

    check = checkGlobalStateChange(a, sprite, work);
    if (check != 0)
        return;

    if (*(u8 *)(*(u8 **)(work + 0x40) + 1) != *(u8 *)(state + 0x48))
    {
        *(u8 *)(a + *(s16 *)(a + 0x22) * 2 + 0x19) = 0;
        {
            void **scriptTable = &gMainObjTimerCallbacks;
            u8 *scriptPtr = a + 0x18;
            sub_080C31E4(scriptPtr, a + 0x22, *scriptTable);
            {
                u8 *stateSlot = (u8 *)(*(s16 *)(a + 0x22) * 2);
                u8 *scriptEntry = scriptPtr;
                u8 command;
                void *callback;
                stateSlot += (u32)a;
                stateSlot[0x19]++;
                scriptEntry += *(s16 *)(a + 0x22) * 2;
                command = *scriptEntry;
                callback = ((void **)*(void **)(a + 0x14))[command];
                sub_080C31E0(a, callback);
            }
        }
        return;
    }

    {
        s32 remaining = *(s32 *)(work + 0x24) - 1;
        *(s32 *)(work + 0x24) = remaining;
        if (remaining == 0)
        {
            *(u8 *)(a + *(s16 *)(a + 0x22) * 2 + 0x19) = 0;
            {
                void **scriptTable = &gMainObjTimerCallbacks;
                u8 *scriptPtr = a + 0x18;
                sub_080C31E4(scriptPtr, a + 0x22, *scriptTable);
                {
                    u8 *stateSlot = (u8 *)(*(s16 *)(a + 0x22) * 2);
                    u8 *scriptEntry = scriptPtr;
                    u8 command;
                    void *callback;
                    stateSlot += (u32)a;
                    stateSlot[0x19]++;
                    scriptEntry += *(s16 *)(a + 0x22) * 2;
                    command = *scriptEntry;
                    callback = ((void **)*(void **)(a + 0x14))[command];
                    sub_080C31E0(a, callback);
                }
            }
            return;
        }
    }

    if ((*(s32 *)(work + 0x10) & 7) == 0)
    {
        u8 *anim = state + 0x25;
        if (*anim <= 0x0F)
            *anim += 4;
    }

    turnHeadingToward(work, *(s32 *)(*(u8 **)(workTail + 0x40) + 0x0C), *(s32 *)(*(u8 **)(workTail + 0x40) + 0x10), workTail + 0x1C);
    setDirectionVector(work, *(u8 *)(workTail + 0x20));

    {
        s32 speed = *(s32 *)(workTail + 0x1C) >> 8;
        s32 delta = *(s32 *)(work + 0x08) * speed;
        if (delta < 0) delta += 0xFF;
        *(s32 *)(work + 0x00) += delta >> 8;
        delta = *(s32 *)(work + 0x0C) * (*(s32 *)(workTail + 0x1C) >> 8);
        if (delta < 0) delta += 0xFF;
        *(s32 *)(work + 0x04) += delta >> 8;
    }

    {
        s32 scale = 0x100 - *(u8 *)(workTail + 0x20);
        *(u16 *)(sprite + 8) = scale << 8;
    }
    sub_0806D588(sprite, work);

    if (*(u16 *)(*(u8 **)(workTail + 0x3C) + 0x14) & 1)
    {
        spawnKind2CEntity(*(void **)(a + 0x28), 8, *(s32 *)(work + 0x00), *(s32 *)(work + 0x04));
        sub_080C31E0(a, *(void **)(a + 0x24));
        return;
    }

    if ((*(s32 *)(work + 0x10) & 3) == 0)
        spawnKind2CEntity(*(void **)(a + 0x28), 8, *(s32 *)(work + 0x00), *(s32 *)(work + 0x04));

    cullOffscreenEntity(a, sprite);
}
