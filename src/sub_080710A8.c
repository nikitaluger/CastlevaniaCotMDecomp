extern void *allocEffectPart(void);
extern void sub_0806D2D0(void *);
extern u16 scalePercentSaturate16(u16, s32);
extern void releaseEffectGroup(void);
extern void sub_080C31E4(void *, void *, void *);
extern void sub_080C31E0(void *, void *);

extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u32 D_080E00C8[];
extern void *gMainObjTimerCallbacks;

struct Obj {
    u8 f0, f1, f2, f3;
    u16 f4, f6, f8, fA, fC, fE;
    u32 f10;
    u8 pad[2];
    u16 f16, f18;
};

/*
 * Allocates and initializes a companion object for the manager, installs its
 * update callback, seeds it with the current world position and a duration,
 * then dispatches the current pose's spawn and handler routines.
 */
void sub_080710A8(void *arg0)
{
    u8 *mgr = (u8 *)arg0;
    u8 *sub = *(u8 **)(mgr + 0x6C) + 4;
    void *owner = *(void **)(mgr + 0x38);
    u8 *dataTable = gGameStatus;
    void *obj;

    obj = allocEffectPart();
    *(void **)(sub + 0x3C) = obj;
    if (obj == 0) { sub_0806D2D0(arg0); return; }

    {
        u8 *gs = gMainWorkspace;
        ((struct Obj *)obj)->f1 = gs[0x1510] & 5;
    }
    ((struct Obj *)(u32)*(vu32 *)(sub + 0x3C))->f2 = 2;
    ((struct Obj *)(u32)*(vu32 *)(sub + 0x3C))->f3 = 8;
    ((struct Obj *)(u32)*(vu32 *)(sub + 0x3C))->f4 = 0;
    ((struct Obj *)(u32)*(vu32 *)(sub + 0x3C))->f6 = 8;
    ((struct Obj *)(u32)*(vu32 *)(sub + 0x3C))->f8 = 0x10;
    ((struct Obj *)(u32)*(vu32 *)(sub + 0x3C))->fA = 0;
    ((struct Obj *)(u32)*(vu32 *)(sub + 0x3C))->fC = 0;

    {
        u16 param = *(u16 *)(dataTable + 0x2DE);
        s32 cond = *(s16 *)(dataTable + 0x8C);
        s32 denom = 0x64;
        if (cond == 1) denom = 0x8D;
        ((struct Obj *)(u32)*(vu32 *)(sub + 0x3C))->fE = scalePercentSaturate16(param, denom);
    }

    {
        struct Obj *objPtr = (struct Obj *)(u32)*(vu32 *)(sub + 0x3C);
        objPtr->f10 = (u32)owner;
        objPtr->f16 = 0xF;
        ((struct Obj *)(u32)*(vu32 *)(sub + 0x3C))->f18 = 0x7E;
    }

    *(void **)(sub + 0x18) = *(void **)(mgr + 0x24);
    *(void **)(mgr + 0x24) = (void *)releaseEffectGroup;

    {
        u8 *gs = gMainWorkspace;
        u32 *pos = (u32 *)(gs + 0x1728);
        *(u32 *)(sub + 0x4C) = *pos;
        pos++;
        *(u32 *)(sub + 0x50) = *pos + 0x500000;
        *(u32 *)(sub + 0x54) = D_080E00C8[(*(s32 *)(mgr + 0x7C) >> 3) & 7];
        *(u16 *)owner = *(u16 *)(gs + 0x18C2);
    }

    {
        *(u8 *)(mgr + *(s16 *)(mgr + 0x22) * 2 + 0x19) = 0;
        {
            void **spawnFunc = &gMainObjTimerCallbacks;
            u8 *poseBase = mgr + 0x18;
            sub_080C31E4(poseBase, mgr + 0x22, *spawnFunc);
            {
                u8 *slot = (u8 *)(*(s16 *)(mgr + 0x22) * 2);
                u8 *poseSlot = poseBase;
                u8 handlerIndex;
                void *handler;
                slot += (u32)mgr;
                slot[0x19]++;
                poseSlot += *(s16 *)(mgr + 0x22) * 2;
                handlerIndex = *poseSlot;
                handler = ((void **)*(void **)(mgr + 0x14))[handlerIndex];
                sub_080C31E0(arg0, handler);
            }
        }
    }
}
