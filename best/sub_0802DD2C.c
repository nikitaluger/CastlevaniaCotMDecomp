extern u8 gMainWorkspace[];
extern u8 gMainObjTimerCallbacks[];
extern void *spawnBudgetedEffect(void *, s32);
extern s32 getSpriteFacingSign(void *);
extern void sub_080C31E8(void *, void *, s32);

typedef struct { s32 v; } Field_s32;
typedef struct { u16 v; } Field_u16;
typedef struct { u32 v; } Field_u32;
void sub_0802DD2C(void *self)
{
    void *gfx;
    void *work;
    u8 *anim;
    void *effect;
    s32 w;
    s32 w_b2;
    s32 idx;
    u8 *stateEntry;
    u16 val1C;

    gfx = *(void **)((u8 *)self + 0x38);
    work = *(void **)((u8 *)self + 0x3C);
    anim = (u8 *)((u8 *)work + 0x34);
    if (anim[1] != 2) return;
    if (*(u32 *)(anim + 4) != (u32)(*(u16 *)(anim + 2) - 1)) return;

    effect = spawnBudgetedEffect(*(void **)(gMainWorkspace + 0x1870), 0xCE);
    if (effect == 0) return;

    if (getSpriteFacingSign(gfx) > 0) {
        w = *(s32 *)((u8 *)work + 8);
        if (w < 0) w += 0xFFFF;
        w >>= 16;
        w += 0x18;
        *(u16 *)((u8 *)effect + 0x4C) = w;
        *(s32 *)((u8 *)effect + 0x5C) = 0x30000;
        return;
    } else {
        w = *(s32 *)((u8 *)work + 8);
        if (w < 0) w += 0xFFFF;
        w >>= 16;
        w -= 0x18;
        *(u16 *)((u8 *)effect + 0x4C) = w;
        w_b2 = -0x30000;
    }
    *(s32 *)((u8 *)effect + 0x5C) = w_b2;

    if (*(s32 *)((u8 *)work + 0xC) < 0) {
        s32 tmp = *(s32 *)((u8 *)work + 0xC);
        if (tmp < 0) tmp += 0xFFFF;
        tmp >>= 16;
        tmp -= 0x1A;
        *(u16 *)((u8 *)effect + 0x54) = tmp;
        *(u32 *)((u8 *)effect + 0x6C) = 0;
    }

    val1C = *(u16 *)((u8 *)work + 0x1C);
    *(u16 *)((u8 *)effect + 0x7C) = val1C;

    idx = (s32)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2);
    stateEntry = (u8 *)((u32)idx + (u32)self);
    *(u8 *)(stateEntry + 0x19) = 0;
    sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, *(s32 *)gMainObjTimerCallbacks);
}
