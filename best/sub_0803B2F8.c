extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern s32 signOf(s32);
extern void sub_0803BB10(u8 *, u8 *);
extern void registerScriptObject(u8 *, s32);
extern void _call_via_r1(u8 *, s32);
extern void _call_via_r2(u8 *, u8 *, s32);
extern void sub_0803BAC0(void);
extern u8 gSpriteKindTable[];
extern u16 D_080CF2A0[];
extern u16 D_080CBDD0[];
extern u32 gMainObjTimerCallbacks;
extern u8 gMainWorkspace[];
extern u8 gCameraState[];

void sub_0803B2F8(u8 *thread)
{
    u8 *__base_gCameraState;
    u8 *__base_gMainWorkspace;
    u8 *refHolder;
    u8 *sprite;
    u8 *work;
    u8 *gfxInit;
    u8 *layer1;
    
    u8 *extra;
    
    u8 *layer3;
    s32 slot;
    u32 attrs;

    refHolder = *(u8 **)(thread + 0xAC);
    { sprite = allocSpriteObject(); }
    if (sprite == 0)
        goto fail;
    *(u8 **)(thread + 0x38) = sprite;
    allocWorkSlot(thread, 0, 0x5C, 0);
    work = *(u8 **)(thread + 0x3C);
    if (work == 0)
        goto fail;
    gfxInit = work + 0x34;
    *(u32 *)(work + 0x24) = *(u32 *)(thread + 0x24);
    *(u32 *)(thread + 0x24) = (u32)sub_0803BAC0;
    *(s16 *)(work + 0x1C) = 0x63;
    *(s32 *)(work + 0x18) = *(s16 *)(gSpriteKindTable + 0x63 * 0x14 + 2);
    *(u32 *)(work + 8) = (u32)(*(s16 *)(*(u8 **)(refHolder + 4)) << 16);
    *(u32 *)(work + 0xC) = (u32)(*(s16 *)(*(u8 **)(refHolder + 4) + 2) << 16);
    slot = findKindIndex(0x63);
    *(s16 *)(work + 0x22) = slot;
    if ((slot << 16) < 0)
        goto fail;
    { u8 *__fence_gfxInit; do { __fence_gfxInit = gfxInit; } while (0); do { do { do { initSpriteGraphics(sprite, __fence_gfxInit, (s32)sub_0803BAC0 + 0x63 * 0xC); } while (0); } while (0); } while (0); }
    __base_gCameraState = allocEffectPart();
    *(u8 **)(work + 0x28) = __base_gCameraState;
    if (__base_gCameraState == 0)
        goto fail;
    __base_gCameraState[1] = 0;
    __base_gCameraState[2] = 8;
    do { __base_gCameraState[3] = 1; } while (0);
    *(u16 *)(__base_gCameraState + 4) = *(u16 *)(gSpriteKindTable + 0x63 * 0x14);
    *(u16 *)(__base_gCameraState + 8) = D_080CF2A0[1];
    *(u16 *)(__base_gCameraState + 0xA) = D_080CF2A0[2];
    *(u16 *)(__base_gCameraState + 6) = D_080CF2A0[0];
    *(u16 *)(__base_gCameraState + 0xC) = D_080CF2A0[3];
    *(u16 *)(__base_gCameraState + 0xE) = *(u16 *)(gSpriteKindTable + 0x63 * 0x14 + 4);
    *(u32 *)(__base_gCameraState + 0x10) = (u32)sprite;
    *(u16 *)(__base_gCameraState + 0x14) = 0;
    do { do { do { do { attrs = (*(u16 *)sprite & 0xC00) |
            (((*(s16 *)(work + 0x22) << 6) + 0x200) |
             ((*(u16 *)(work + 0x22) + 8) << 12)); } while (0); } while (0); } while (0); } while (0);
    *(u16 *)sprite = attrs;
    __base_gMainWorkspace = gMainWorkspace;
    *(u16 *)sprite = attrs | *(u16 *)(__base_gMainWorkspace + 0x18C2);
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    __base_gCameraState = gCameraState;
    *(u32 *)(sprite + 0x14) = *(u32 *)(work + 8) -
        ((*(u32 *)(gCameraState + 0x1278 + ((*(u8 *)(__base_gMainWorkspace + 0x18A8) + 1) << 6)) + 0x8000) & 0xFFFF0000);
    *(u32 *)(sprite + 0x18) = *(u32 *)(work + 0xC) -
        ((*(u32 *)(__base_gCameraState + 0x127C + ((*(u8 *)(__base_gMainWorkspace + 0x18A8) + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000);
    extra = work + 0x48;
    *(u32 *)(work + 0x48) = *(u32 *)(work + 8);
    *(u32 *)(extra + 4) = (u32)(*(u16 *)(*(u8 **)(refHolder + 4) + 6) << 16);
    layer1 = allocEffectPart();
    *(u8 **)(extra + 8) = layer1;
    if (layer1 == 0)
        goto fail;
    layer1[1] = 0;
    layer1[2] = 8;
    layer1[3] = 1;
    *(u16 *)(layer1 + 4) = *(u16 *)(D_080CBDD0 + 0x63 * 0x28 + 4);
    *(u16 *)(layer1 + 6) = D_080CF2A0[8];
    *(u16 *)(layer1 + 8) = D_080CF2A0[9];
    *(u16 *)(layer1 + 0xA) = D_080CF2A0[10];
    *(u16 *)(layer1 + 0xC) = D_080CF2A0[11];
    *(u16 *)(layer1 + 0xE) = *(u16 *)(D_080CBDD0 + 0x63 * 0x28 + 6);
    *(u32 *)(layer1 + 0x10) = (u32)sprite;
    *(u16 *)(layer1 + 0x14) = 0;
    layer3 = allocEffectPart();
    *(u8 **)(extra + 0xC) = layer3;
    if (layer3 == 0)
        goto fail;
    layer3[1] = 0;
    layer3[2] = 8;
    layer3[3] = 1;
    *(u16 *)(layer3 + 4) = *(u16 *)(gSpriteKindTable + 0x63 * 0x14);
    *(u16 *)(layer3 + 6) = D_080CF2A0[4];
    *(u16 *)(layer3 + 8) = D_080CF2A0[5];
    *(u16 *)(layer3 + 0xA) = D_080CF2A0[6];
    *(u16 *)(layer3 + 0xC) = D_080CF2A0[7];
    *(u16 *)(layer3 + 0xE) = *(u16 *)(gSpriteKindTable + 0x63 * 0x14 + 4);
    *(u32 *)(layer3 + 0x10) = (u32)sprite;
    *(u16 *)(layer3 + 0x14) = 0;
    do { do { do { do { setAnimationFrame(sprite, gfxInit, 0, 1); } while (0); } while (0); } while (0); } while (0);
    if (signOf(*(s32 *)(work + 8)) == 0)
        *(u16 *)(sprite + 2) |= 0x10;
    sub_0803BB10(thread, sprite);
    registerScriptObject(thread, 1);
    *(u16 *)(thread + 2) |= 0x1000;
    *(u8 *)(thread + *(s16 *)(thread + 0x22) * 2 + 0x19) = 0;
    _call_via_r2(thread + 0x18, thread + 0x22, *(s32 *)gMainObjTimerCallbacks);
    *(u8 *)(thread + *(s16 *)(thread + 0x22) * 2 + 0x19) += 1;
    {
        u8 *p;
        p = (thread + *(s16 *)(thread + 0x22) * 2) + 0x18;
        _call_via_r1(thread, *(s32 *)(*(u32 *)(thread + 0x14) + *p * 4));
    }
    return;
fail:
    _call_via_r1(thread, *(s32 *)(thread + 0x24));
}
