s32 sub_0806D450(void *, void *, void *);
void sub_0806D588(void *, void *);
void sub_0806D2F8(void *, void *);
void sub_0806E114(void *, s32, s32, s32);
void sub_080722E0(void *, u32);
void sub_08072334(void *, s32, s32, void *);
void sub_08003740(void *, void *);
void sub_080C31E4(void *, void *, void *);
void sub_080C31E0(void *, void *);

extern void *gMainObjTimerCallback;

struct GameState {
    u8 _0[0x10];
    u32 field10;
    u8 _1[0x14ED - 0x14];
    u8 field14ED;
    u8 _1b[0x14FC - 0x14EE];
    u32 field14FC;
    u8 _2[0x173A - 0x1500];
    u8 field173A;
};
extern struct GameState gMainWorkspace;

/* One frame of a scripted walking actor: check camera/movement state, advance the
 * script frame counter and timer (re-dispatching the script when either expires),
 * integrate velocity toward the computed direction, snap to the grid, then choose
 * between aborting, the off-screen check, and continuing. */
void sub_0807041C(void *arg0)
{
    u8 *script = (u8 *)arg0;
    u8 *actor = *(u8 **)(script + 0x6C);
    u8 *mover = actor + 4;
    void *world = *(void **)(script + 0x38);
    u8 *body = mover;
    u32 frameCount;

    if (sub_0806D450(script, world, mover) > 0) goto L594;

    frameCount = *(u32 *)(mover + 0x10) + 1;
    *(u32 *)(mover + 0x10) = frameCount;

    if (*(u8 *)(*(u8 **)(mover + 0x40) + 1) != *(u8 *)(actor + 0x48))
    {
        *(u8 *)(script + *(s16 *)(script + 0x22) * 2 + 0x19) = 0;
        {
            void **cmdTable = &gMainObjTimerCallback;
            u8 *scriptPc = script + 0x18;
            sub_080C31E4(scriptPc, script + 0x22, *cmdTable);
            {
                u8 *statePtr = (u8 *)(*(s16 *)(script + 0x22) * 2);
                u8 *scriptState = scriptPc;
                u8 opcode;
                void *handler;
                statePtr += (u32)script;
                statePtr[0x19]++;
                scriptState += *(s16 *)(script + 0x22) * 2;
                opcode = *scriptState;
                handler = ((void **)*(void **)(script + 0x14))[opcode];
                sub_080C31E0(script, handler);
            }
        }
        return;
    }

    {
        s32 timer = *(s32 *)(mover + 0x24) - 1;
        *(s32 *)(mover + 0x24) = timer;
        if (timer == 0)
        {
            *(u8 *)(script + *(s16 *)(script + 0x22) * 2 + 0x19) = 0;
            {
                void **cmdTable = &gMainObjTimerCallback;
                u8 *scriptPc = script + 0x18;
                sub_080C31E4(scriptPc, script + 0x22, *cmdTable);
                {
                    u8 *statePtr = (u8 *)(*(s16 *)(script + 0x22) * 2);
                    u8 *scriptState = scriptPc;
                    u8 opcode;
                    void *handler;
                    statePtr += (u32)script;
                    statePtr[0x19]++;
                    scriptState += *(s16 *)(script + 0x22) * 2;
                    opcode = *scriptState;
                    handler = ((void **)*(void **)(script + 0x14))[opcode];
                    sub_080C31E0(script, handler);
                }
            }
            return;
        }
    }

    if ((frameCount & 7) == 0)
    {
        u8 *dir = actor + 0x25;
        if (*dir <= 0x0F)
            *dir += 4;
    }

    sub_08072334(body, *(s32 *)(*(u8 **)(mover + 0x40) + 0x0C), *(s32 *)(*(u8 **)(mover + 0x40) + 0x10), mover + 0x1C);
    sub_080722E0(body, *(u8 *)(mover + 0x20));

    {
        s32 scale = *(s32 *)(mover + 0x1C) >> 8;
        s32 delta = *(s32 *)(body + 0x08) * scale;
        if (delta < 0) delta += 0xFF;
        *(s32 *)(body + 0x00) += delta >> 8;
        delta = *(s32 *)(body + 0x0C) * (*(s32 *)(mover + 0x1C) >> 8);
        if (delta < 0) delta += 0xFF;
        *(s32 *)(body + 0x04) += delta >> 8;
    }

    sub_0806D588(world, body);

    if (*(u16 *)(*(u8 **)(mover + 0x3C) + 0x14) & 1)
    {
        sub_0806E114(*(void **)(script + 0x28), 8, *(s32 *)(body + 0x00), *(s32 *)(body + 0x04));
        goto L594;
    }

    sub_08003740(mover + 0x2C, world);

    if (gMainWorkspace.field14FC != 0) goto L594;
    if (gMainWorkspace.field173A == 0x1C) goto L594;
    if (gMainWorkspace.field14ED != 0) goto L5B0;
    if (gMainWorkspace.field10 != 0) goto L594;
    goto L5B0;

L594:
    sub_080C31E0(script, *(void **)(script + 0x24));
    return;

L5B0:
    sub_0806D2F8(script, world);
}
