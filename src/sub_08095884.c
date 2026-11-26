extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08095CE4(void);

struct Sprite95884 {
    u8 _0;
    u8 f1;
    u8 f2;
    u8 f3;
    u16 f4;
    u16 f6;
    u16 f8;
    u16 fA;
    u16 fC;
    u16 fE;
    void *f10;
    u16 f14;
};

struct Ent95884 {
    u8 _0[8];
    s32 f8;
    s32 fC;
    u8 _10[8];
    s32 f18;
    u8 _1C[8];
    s32 f24;
    struct Sprite95884 *f28;
};

struct Arg95884 {
    u8 _0[2];
    u16 f2;
    u8 _4[0x10];
    u32 *f14;
    u8 _18[0xA];
    s16 f22;
    s32 f24;
    u8 _28[0x10];
    void *f38;
    struct Ent95884 *f3C;
    u8 _40[0x6C];
    void *fAC;
};

struct R8_95884 {
    u8 _0[4];
    s16 *f4;
};

extern u8 gCameraState[];
extern struct {
    u8 _0[0x18A8];
    u8 f18A8;
    u8 _18A9[0x19];
    u16 f18C2;
} gMainWorkspace;

extern u16 D_08100A6C[];
extern u8 D_08630B98[];
extern s32 gMainObjTimerCallback[];

/* Spawns a sprite and its logic/child entities from the owner's coordinate
 * config, sets world coordinates from the scroll table and records the action. */
void sub_08095884(struct Arg95884 *owner)
{
    void *config;
    void *sprite;
    struct Ent95884 *logic;
    s16 *coords;
    struct Sprite95884 *child;
    u32 zero;
    s32 *cmdTable;
    u8 *attackLog;

    config = owner->fAC;
    sprite = allocSpriteObject();
    if (sprite == 0)
        goto fail;

    owner->f38 = sprite;
    allocWorkSlot(owner, 0, 0x34, 0);
    logic = owner->f3C;
    if (logic == 0)
        goto fail;

    logic->f24 = owner->f24;
    owner->f24 = (s32)sub_08095CE4;
    logic->f18 = 1;

    coords = ((struct R8_95884 *)config)->f4;
    logic->f8 = (s32)coords[0] << 16;
    logic->fC = (s32)coords[1] << 16;

    child = allocEffectPart();
    logic->f28 = child;
    if (child != 0)
        goto cont;

fail:
    sub_080C31E0(owner, owner->f24);
    goto end;

cont:
    zero = 0;
    child->f1 = 4;
    logic->f28->f2 = 0x80;
    logic->f28->f3 = 0;
    logic->f28->f4 = zero;
    logic->f28->f6 = 6;
    logic->f28->f8 = 6;
    logic->f28->fA = zero;
    logic->f28->fC = zero;
    logic->f28->fE = zero;
    logic->f28->f10 = sprite;
    logic->f28->f14 = 0;

    *(u16 *)sprite |= gMainWorkspace.f18C2;
    *(u32 *)((u8 *)sprite + 0x1C) = 0x80000007;

    {
        u8 *scrollBase = (u8 *)&gCameraState;
        { u32 offset = 0x1278; *(u32 *)((u8 *)sprite + 0x14) = logic->f8 - ((*(u32 *)(scrollBase + offset + ((gMainWorkspace.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
        { u32 offset = 0x127C; *(u32 *)((u8 *)sprite + 0x18) = logic->fC - ((*(u32 *)(scrollBase + offset + ((gMainWorkspace.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    }

    *(u32 *)((u8 *)sprite + 0x24) = (u32)D_08630B98;
    *(u16 *)((u8 *)sprite + 0x28) = D_08100A6C[((struct R8_95884 *)config)->f4[3] & 0xF];

    owner->f2 |= 0x1000;

    *(u8 *)((u8 *)owner + owner->f22 * 2 + 0x19) = zero;

    cmdTable = gMainObjTimerCallback;
    attackLog = (u8 *)owner + 0x18;
    sub_080C31E4(attackLog, &owner->f22, *cmdTable);

    *(u8 *)((u8 *)owner + owner->f22 * 2 + 0x19) += 1;

    attackLog += owner->f22 * 2;
    sub_080C31E0(owner, owner->f14[*attackLog]);

end:
    return;
}
