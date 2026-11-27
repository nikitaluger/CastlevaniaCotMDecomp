extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern u32 scaleByRandom(u32);
extern void _call_via_r1(u8 *, s32);
extern void _call_via_r2(u8 *, u8 *, s32);
extern u8 gSpriteKindTable[];
extern u16 gSpriteAnimDataTable[];
extern u16 gSpriteAffineParams[];
extern u8 gMainWorkspace[];
extern u8 gCameraState[];

struct KindEnt20 { s16 f0; u8 _2[2]; s16 f4; u8 _6[0x14-6]; };

void sub_080308C0(u8 *thread)
{
    u8 *refHolder;
    u8 *sprite;
    u8 *work;
    u8 *anim;
    u8 *kindTable;
    u8 *layer;
    u8 *effect;
    u8 *animPos;
    u8 *camera;
    u8 *affine;
    s32 slot;
    s32 zero;
    u32 attrs;
    s16 kind;
    u32 addr;

    refHolder = *(u8 **)(thread + 0xAC);
    sprite = allocSpriteObject();
    if (sprite == 0) goto fail;
    *(u8 **)(thread + 0x38) = sprite;
    allocWorkSlot(thread, 0, 0x60, 0);
    work = *(u8 **)(thread + 0x3C);
    if (work == 0) goto fail;
    anim = work + 0x34;
    *(u32 *)(work + 0x24) = *(u32 *)(thread + 0x24);
    *(u32 *)(thread + 0x24) = 0x08030F55;
    switch (*(s16 *)(*(u8 **)(refHolder + 4) + 4)) {
    case 0xD7: kind = 0xB; break;
    case 0xD8: kind = 0xC; break;
    default: goto skip_kind;
    }
    *(s16 *)(work + 0x1C) = kind;
skip_kind:
    kindTable = gSpriteKindTable;
    *(s32 *)(work + 0x18) = ((struct KindEnt20 *)(kindTable + kind * 0x14))->f4;
    *(u32 *)(work + 8) = (u32)(*(s16 *)(*(u8 **)(refHolder + 4)) << 16);
    *(u32 *)(work + 0xC) = (u32)(*(s16 *)(*(u8 **)(refHolder + 4) + 2) << 16);
    slot = findKindIndex(*(s16 *)(work + 0x1C));
    zero = 0;
    *(s16 *)(work + 0x22) = (s16)slot;
    if ((slot << 16) < 0) goto fail;
    initSpriteGraphics(sprite, anim, (s32)gSpriteAnimDataTable + kind * 0xC);
    layer = allocEffectPart();
    *(u8 **)(work + 0x28) = layer;
    if (layer == 0) goto fail;
    layer[1] = 0;
    layer[2] = 8;
    layer[3] = 1;
    *(u16 *)(layer + 4) = ((struct KindEnt20 *)(kindTable + kind * 0x14))->f0;
    affine = gSpriteAffineParams;
    *(u16 *)(layer + 6) = *(u16 *)(affine + 0);
    *(u16 *)(layer + 8) = *(u16 *)(affine + 2);
    *(u16 *)(layer + 0xA) = *(u16 *)(affine + 4);
    *(u16 *)(layer + 0xC) = *(u16 *)(affine + 6);
    *(u16 *)(layer + 0xE) = ((struct KindEnt20 *)(kindTable + kind * 0x14))->f4;
    *(u32 *)(layer + 0x10) = (u32)sprite;
    *(u16 *)(layer + 0x14) = (u16)zero;
    attrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)(work + 0x22) << 6) + 0x200) |
           ((*(u16 *)(work + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | *(u16 *)(gMainWorkspace + 0x18C2);
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    camera = gCameraState;
    addr = (u32)camera + 0x1278 + ((u32)*(u8 *)(gMainWorkspace + 0x18A8) + 4) * 0x40;
    *(u32 *)(sprite + 0x14) = *(u32 *)(work + 8) - ((*(u32 *)addr + 0x8000) & 0xFFFF0000);
    addr = (u32)camera + 0x127C + ((u32)*(u8 *)(gMainWorkspace + 0x18A8) + 4) * 0x40;
    *(u32 *)(sprite + 0x18) = *(u32 *)(work + 0xC) - ((*(u32 *)addr + 0xFFFF8000) & 0xFFFF0000);

    animPos = anim + 0x14;
    {
        s32 t = *(s16 *)(work + 0x22) ^ 0xB;
        *(u16 *)(anim + 0x14) = (u16)((t | -t) >> 31);
    }
    *(u16 *)(animPos + 2) = zero;
    *(u16 *)(animPos + 8) = zero;
    *(u16 *)(animPos + 4) = (u16)(scaleByRandom(0x3D) + 0x78);
    *(u32 *)(animPos + 0xC) = *(u32 *)(work + 8);
    *(u32 *)(animPos + 0x10) = *(u32 *)(work + 0xC);
    effect = allocEffectPart();
    *(u8 **)(animPos + 0x14) = effect;
    if (effect == 0) goto fail;

    effect[1] = 0;
    effect[2] = 8;
    effect[3] = 1;
    *(u16 *)(effect + 4) = ((struct KindEnt20 *)((u8 *)0x080CBDD0 + kind * 0x14))->f0;
    *(u16 *)(effect + 6) = *(u16 *)(affine + 8);
    *(u16 *)(effect + 8) = *(u16 *)(affine + 0xA);
    *(u16 *)(effect + 0xA) = *(u16 *)(affine + 0xC);
    *(u16 *)(effect + 0xC) = *(u16 *)(affine + 0xE);
    *(u16 *)(effect + 0xE) = ((struct KindEnt20 *)((u8 *)0x080CBDD0 + kind * 0x14))->f4;
    *(u32 *)(effect + 0x10) = (u32)sprite;
    *(u16 *)(effect + 0x14) = zero;

    *(u32 *)(work + 0x14) = 0x08671BB0;
    *(u16 *)(work + 4) = 8;
    *(u16 *)(thread + 2) |= 0x1000;
    _call_via_r2(thread + 0x18, thread + 0x22, *(s32 *)0x08671BB0);
    *(u8 *)(thread + *(s16 *)(thread + 0x22) * 2 + 0x19) += 1;
    {
        u8 *stepByte = thread + 0x18 + *(s16 *)(thread + 0x22) * 2;
        _call_via_r1(thread, *(s32 *)(*(u32 *)(thread + 0x14) + *stepByte * 4));
    }
    return;

fail:
    _call_via_r1(thread, *(s32 *)(thread + 0x24));
}
