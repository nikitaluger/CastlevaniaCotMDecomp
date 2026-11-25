void *sub_08016190(void);
void sub_0806D2D0(void *);
u16 sub_0806D62C(u16, s32);
void sub_080718F4(void);
void sub_080C31E4(void *, void *, void *);
void sub_080C31E0(void *, void *);

extern u8 D_02025368[];
extern u8 D_02025FF0[];
extern u32 D_080E0110[];
extern u32 D_084748AC;
extern void *D_08671BB0;

struct Obj {
    u8 f0, f1, f2, f3;
    u16 f4, f6, f8, fA, fC, fE;
    u32 f10;
    u8 pad[2];
    u16 f16, f18;
};

/*
 * Allocates and initializes a companion object for the manager, installs its
 * update callback, seeds the owner with animation/state data from the global
 * tables, then dispatches the current pose's spawn and handler routines.
 */
void sub_08070E34(void *arg0)
{
    u8 *mgr = (u8 *)arg0;
    u8 *sub = *(u8 **)(mgr + 0x6C) + 4;
    void *owner = *(void **)(mgr + 0x38);
    u8 *dataTable = D_02025368;
    void *obj;

    obj = sub_08016190();
    *(void **)(sub + 0x3C) = obj;
    if (obj == 0) {
        sub_0806D2D0(arg0);
        return;
    }

    {
        u8 *gs = D_02025FF0;
        ((struct Obj *)obj)->f1 = gs[0x1510] & 5;
    }
    ((struct Obj *)(u32)*(vu32 *)(sub + 0x3C))->f2 = 2;
    ((struct Obj *)(u32)*(vu32 *)(sub + 0x3C))->f3 = 8;
    ((struct Obj *)(u32)*(vu32 *)(sub + 0x3C))->f4 = 0;
    ((struct Obj *)(u32)*(vu32 *)(sub + 0x3C))->f6 = 0x1E;
    ((struct Obj *)(u32)*(vu32 *)(sub + 0x3C))->f8 = 0x1E;
    ((struct Obj *)(u32)*(vu32 *)(sub + 0x3C))->fA = 0;
    ((struct Obj *)(u32)*(vu32 *)(sub + 0x3C))->fC = 0;

    {
        u16 param = *(u16 *)(dataTable + 0x2DE);
        s32 cond = *(s16 *)(dataTable + 0x8C);
        s32 denom = 0x2D;
        if (cond == 1)
            denom = 0x3F;
        ((struct Obj *)(u32)*(vu32 *)(sub + 0x3C))->fE = sub_0806D62C(param, denom);
    }

    {
        struct Obj *objPtr = (struct Obj *)(u32)*(vu32 *)(sub + 0x3C);
        objPtr->f10 = (u32)owner;
        objPtr->f16 = 0xF;
        ((struct Obj *)(u32)*(vu32 *)(sub + 0x3C))->f18 = 0x7D;
    }

    *(void **)(sub + 0x18) = *(void **)(mgr + 0x24);
    *(void **)(mgr + 0x24) = (void *)sub_080718F4;

    {
        u8 *gs = D_02025FF0;
        *(u32 *)((u8 *)owner + 0x24) = (u32)&D_084748AC;
        *(u32 *)((u8 *)owner + 0x14) = D_080E0110[(*(u32 *)(gs + 0x14F4) & 0x3C) >> 2];
        *(u32 *)((u8 *)owner + 0x18) = 0xFFE00000;
        *(u32 *)((u8 *)owner + 0x1C) = 0x80000004;
        *(u16 *)owner = *(u16 *)(gs + 0x18C2);
    }

    {
        *(u8 *)(mgr + *(s16 *)(mgr + 0x22) * 2 + 0x19) = 0;
        {
            void **spawnFunc = &D_08671BB0;
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
