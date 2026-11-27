struct S_02025FF0 { u8 _0[0x174C]; u32 v174C; u32 v1750; };
extern struct S_02025FF0 gMainWorkspace;
extern u32 gGameStatus[];
extern u8 D_02027500[];
extern void *gMainObjTimerCallbacks;
struct Obj { u8 _0, f1, f2, f3; u16 f4, f6, f8, fA, fC, fE; u32 f10; u8 _14[2]; u16 f16, f18; };
struct Base { u8 _0[0x18]; u32 f18; u8 _1C[0x10]; struct Obj *arr[5]; };
extern void *allocEffectPart(void);
extern void unlinkAndFreeObject(void);
extern void cleanupFailedEffectSpawn(void *);
extern void startEffectTimer(void *, s32, s32);
extern void stepDelayTimer(void *, void *);
extern void releaseActorEffectParts(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Allocates and initialises five sub-effect entities for the owner's sprite,
 * sets up their shared base state and visibility flags, then records the action. */
void initFivePartSpriteGroup(u8 *owner) {
    struct Base *base = (struct Base *)(*(u8 **)(owner + 0x6C) + 4);
    void *sprite = *(void **)(owner + 0x38);
    u8 *baseBytes = (u8 *)base;
    u32 *dataBase = gGameStatus;
    s32 i = 0;
    u16 zero = 0;
    for (; i < 5; i++) {
        base->arr[i] = allocEffectPart();
        if (base->arr[i] == NULL) {
            if (base->arr[0]) unlinkAndFreeObject();
            if (base->arr[1]) unlinkAndFreeObject();
            if (base->arr[2]) unlinkAndFreeObject();
            if (base->arr[3]) unlinkAndFreeObject();
            cleanupFailedEffectSpawn(owner);
            return;
        }
        base->arr[i]->f1 = 1 & D_02027500[0];
        base->arr[i]->f2 = 2;
        base->arr[i]->f3 = 8;
        base->arr[i]->f4 = *(u8 *)(dataBase + 0xC1);
        base->arr[i]->f6 = 4;
        base->arr[i]->f8 = 4;
        base->arr[i]->fA = zero;
        base->arr[i]->fC = zero;
        base->arr[i]->fE = 0xBB8;
        base->arr[i]->f16 = 0x1E;
        base->arr[i]->f18 = 0x81;
        base->arr[i]->f10 = (u32)sprite;
    }
    *(u32 *)(baseBytes + 0x18) = *(u32 *)(owner + 0x24);
    *(void **)(owner + 0x24) = releaseActorEffectParts;
    {
        u16 zero16 = 0;
        u16 initVal = 0x100;
        *(u16 *)((u8 *)sprite + 4) = initVal;
        *(u16 *)((u8 *)sprite + 6) = initVal;
        *(u16 *)((u8 *)sprite + 8) = zero16;
    }
    *(u32 *)((u8 *)sprite + 0x24) = 0x084A65BC;
    base = (struct Base *)((u8 *)base + 0x1C);
    startEffectTimer((u8 *)base, 0, 0x084A680C);
    stepDelayTimer((u8 *)base, sprite);
    *(u32 *)(baseBytes + 0) = gMainWorkspace.v174C;
    *(u32 *)(baseBytes + 4) = gMainWorkspace.v1750;
    {
        u32 cond = *(u16 *)((u8 *)sprite + 2) & 0x10;
        u32 mask = 0x20000;
        if (cond) mask = 0xFFFE0000;
        *(u32 *)(baseBytes + 8) = mask;
        *(u32 *)(baseBytes + 0xC) = 0xFFFB0000;
    }
    {
        u16 zeroVal = 0;
        *(u8 *)((u32)(*(s16 *)(owner + 0x22)) * 2 + (u32)owner + 0x19) = zeroVal;
        {
            u8 *attackLog;
            u32 *cmdTable = (u32 *)&gMainObjTimerCallbacks;
            attackLog = owner + 0x18;
            sub_080C31E4(attackLog, owner + 0x22, (s32)*cmdTable);
            *(u8 *)((u32)(*(s16 *)(owner + 0x22)) * 2 + (u32)owner + 0x19) += 1;
            attackLog += (*(s16 *)(owner + 0x22)) * 2;
            sub_080C31E0(owner, *(void **)(*(u8 **)(owner + 0x14) + *(u8 *)attackLog * 4));
        }
    }
}
