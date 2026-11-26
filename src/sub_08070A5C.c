/* Allocate an AI work buffer for an entity, fill its parameters from the global
 * tuning tables, install the update/destroy callbacks and advance its script. */
extern void sub_08003A6C(void *, s32, void *);
extern void *allocEffectPart(void);
extern void sub_0806D2D0(void *);
extern s16 sub_0806D62C(u16, s32);
extern void sub_080718F4(void);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u32 D_084737D4;
extern u32 D_08473814;
extern s32 gMainObjTimerCallback;

struct S_08070A5C { u8 _0[0x3C]; u8 * volatile work; };
struct S_08070A5C_R7 { u16 f00; };

void sub_08070A5C(u8 *entity) {
    u32 zero;
    u32 two;
    u32 eight;
    u8 *brain = *(u8 **)(entity + 0x6C);
    u8 *brainCtx = brain + 4;
    u8 *aux = *(u8 **)(entity + 0x38);
    u8 *cfg = gGameStatus;
    u8 *base;
    void *work;
    s32 percent;
    s32 tableVal;
    u16 baseRate;
    u8 mode;
    struct S_08070A5C *ctx = (struct S_08070A5C *)brainCtx;
    struct S_08070A5C_R7 *auxHdr = (struct S_08070A5C_R7 *)aux;

    work = allocEffectPart();
    ctx->work = work;
    if (work == NULL) {
        sub_0806D2D0(entity);
        return;
    }
    base = gMainWorkspace;
    mode = 5 & *(u8 *)(base + 0x1510);
    zero = 0;
    *(u8 *)(work + 1) = mode;
    {
        u8 *wp = ctx->work;
        two = 2;
        *(u8 *)(wp + 2) = two;
    }
    {
        u8 *wp = ctx->work;
        eight = 8;
        *(u8 *)(wp + 3) = eight;
    }
    *(u16 *)(ctx->work + 4) = zero;
    *(u16 *)(ctx->work + 6) = eight;
    *(u16 *)(ctx->work + 8) = eight;
    *(u16 *)(ctx->work + 0xA) = zero;
    *(u16 *)(ctx->work + 0xC) = zero;
    baseRate = *(u16 *)(cfg + 0x2DE);
    percent = (*(s16 *)(cfg + 0x8C) == 1) ? 0x7E : 0x59;
    *(u16 *)(ctx->work + 0xE) = sub_0806D62C(baseRate, percent);
    {
        u8 *wp = ctx->work;
        *(void **)(wp + 0x10) = aux;
        *(u16 *)(wp + 0x16) = 0xF;
    }
    *(u16 *)(ctx->work + 0x18) = 0x7C;
    *(u32 *)(brainCtx + 0x18) = *(u32 *)(entity + 0x24);
    *(u32 *)(entity + 0x24) = (u32)&sub_080718F4;
    *(u32 *)(aux + 0x24) = (u32)&D_084737D4;
    sub_08003A6C(brain + 0x30, 0, &D_08473814);
    *(s32 *)(brain + 4) = *(s32 *)(base + 0x174C);
    tableVal = *(s32 *)(base + 0x1750);
    *(s32 *)(brainCtx + 4) = tableVal;
    *(s32 *)(brainCtx + 0x4C) = *(s32 *)(brain + 4);
    *(s32 *)(brainCtx + 0x50) = tableVal;
    *(s32 *)(brainCtx + 0x54) = *(s32 *)(entity + 0x7C);
    *(s32 *)(brainCtx + 0x58) = 0x80 << 11;
    *(s32 *)(brainCtx + 0x5C) = *(s32 *)(entity + 0x8C) + 1;
    *(s32 *)(brainCtx + 0x60) = zero;
    *(s32 *)(aux + 0x1C) = 0x80000004;
    auxHdr->f00 = *(u16 *)(base + 0x18C2);
    if (*(s32 *)(brainCtx + 0x5C) != 1) {
        auxHdr->f00 |= 0x4000;
    }
    *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = zero;
    {
        s32 *scriptTable = &gMainObjTimerCallback;
        u8 *scriptPtr = entity + 0x18;
        sub_080C31E4(scriptPtr, entity + 0x22, *scriptTable);
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) + 1;
        scriptPtr += *(s16 *)(entity + 0x22) * 2;
        {
            u8 scriptId = *scriptPtr;
            sub_080C31E0(entity, *(s32 *)(scriptId * 4 + *(u32 *)(entity + 0x14)));
        }
    }
}
