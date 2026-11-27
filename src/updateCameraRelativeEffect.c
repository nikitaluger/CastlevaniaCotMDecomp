extern s32 checkActorViewBounds(void *, void *);
extern void uploadPendingSpriteGraphic(s32, s32);
extern void sub_08014314(void *, s32);
extern s32 sub_08014328(s32, void *, void *);
extern void _call_via_r1(void *, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/* Update a scripted effect: sync the owner's coordinates and sprite flags,
 * refresh its graphics, advance the script or clear part flags, then place the
 * sprite relative to the camera scroll. */
void updateCameraRelativeEffect(u8 *object)
{
    u8 *sprite;
    u8 *state;
    u8 *partState;
    u8 *scriptStep;
    u8 *camera;
    u8 *workspace;
    u8 *scrollXTable;
    u32 index;
    u32 scrollX;
    u32 scrollY;
    u8 stepOpcode;
    u8 *scriptStream;
    s32 stepOffset;

    sprite = *(u8 **)(object + 0x38);
    state = *(u8 **)(object + 0x3C);
    partState = state + 0x48;
    *(u32 *)(state + 8) = *(u32 *)(object + 0x4C);
    *(u32 *)(state + 0xC) = *(u32 *)(object + 0x5C);

    if (*(u8 *)(object + 0x6C) != 0)
        ((struct EffectSpriteAttrs *)sprite)->attr1 |= 0x10;
    else
        ((struct EffectSpriteAttrs *)sprite)->attr1 &= 0xFFEF;
    *(u16 *)sprite = (*(u16 *)sprite & 0xFFF) | ((*(u16 *)(state + 0x22) + 8) << 12);

    if (checkActorViewBounds(sprite, state) == 1) {
        _call_via_r1((void *)object, *(s32 *)(object + 0x24));
        return;
    }
    uploadPendingSpriteGraphic(*(s32 *)(object + 0x28), *(s32 *)partState);
    uploadPendingSpriteGraphic(*(s32 *)(object + 0x28), *(s32 *)(partState + 4));
    if (sub_08014328(*(s32 *)(object + 0x28), sprite, state) == 0) {
        *(u32 *)(object + 0x14) = EFFECT_VIEW_STEP_TABLE;
        *(u16 *)(object + 0x22) = *(u16 *)(object + 0x22) + 1;
        scriptStep = (u8 *)((u32)(*(s16 *)(object + 0x22)) * 2 + (u32)object);
        *(u8 *)(scriptStep + 0x19) = *(u8 *)(scriptStep + 0x19) + 1;
        stepOffset = *(s16 *)(object + 0x22) * 2;
        scriptStream = object;
        scriptStream += 0x18;
        stepOpcode = *(u8 *)((u32)scriptStream + (u32)stepOffset);
        _call_via_r1((void *)object, *(u32 *)(*(u32 *)(object + 0x14) + stepOpcode * 4));
        *(u16 *)(object + 0x22) = *(u16 *)(object + 0x22) - 1;
    } else {
        sub_08014314(state, *(s32 *)partState);
        sub_08014314(state, *(s32 *)(partState + 4));
    }

    camera = gCameraState;
    workspace = gMainWorkspace;
    workspace += 0x18A8;
    index = ((u32)*workspace + 1) * 0x40;
    scrollXTable = camera + 0x1278;
    scrollX = *(u32 *)(scrollXTable + index);
    *(u32 *)(sprite + 0x14) = *(u32 *)(state + 8) - ((scrollX + 0x8000) & 0xFFFF0000);
    index = ((u32)*workspace + 1) * 0x40;
    camera += 0x127C;
    scrollY = *(u32 *)(camera + index);
    *(u32 *)(sprite + 0x18) = *(u32 *)(state + 0xC) - ((scrollY + 0xFFFF8000) & 0xFFFF0000);
}
