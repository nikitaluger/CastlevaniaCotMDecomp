extern void applySpritePaletteVariant(void *, s32);
extern s32 checkActorViewBounds(s32, void *);
extern s32 sub_08013558(s32, void *, void *);
extern void spawnContactEffectOnHit(void *, void *);
extern void uploadPendingSpriteGraphic(void *, void *);
extern void updateActorWorldPosition(void *);
extern s32 updateObjectDisplayState(s32, void *);
extern void stepAnimationTrack(s32, void *);
extern void sub_08011EE8(void *, s32, s32);
extern void sub_08013C8C(void *, s32);
extern void sub_08059AD8(s32, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *sScriptStepCallbacks;
extern u8 gCameraState[];
extern struct { u8 _0[0x18A8]; u8 f18A8; } gMainWorkspace;

/* Entity script update: refresh contact/combat state, run one script command
 * from the command table, then apply the camera-relative Y correction. */
void sub_08059630(u8 *self) {
    s32 parent = *(s32 *)(self + 0x38);
    u8 *comp = *(u8 **)(self + 0x3C);
    u8 *body = comp + 0x34;
    u8 *fx = comp + 0x48;
    u32 coordBase;
    u32 coordOff;
    s32 worldY;
    u32 coordVal;

    if (checkActorViewBounds(parent, comp) == 1) return;

    applySpritePaletteVariant(self, parent);
    if (sub_08013558(parent, comp, *(void **)(comp + 0x28)) != 0) {
        spawnContactEffectOnHit(self, *(void **)(comp + 0x28));
    }
    uploadPendingSpriteGraphic(self, *(void **)(comp + 0x28));
    if (*(u16 *)comp & 1) {
        u8 *script = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        if (*(u8 *)(script + 0x1A) != 3) {
            updateActorWorldPosition(self);
            {
                u8 *scriptPtr = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
                *(u8 *)(scriptPtr + 0x1B) = 0;
                { void **sound = &sScriptStepCallbacks;
                  sub_080C31E8(self + 0x18, self + 0x22, 3, *sound); }
            }
        }
    }
    if (updateObjectDisplayState(parent, comp) != 0) goto cdc;
    *(u32 *)(self + 0x14) = 0x0866E854;
    *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) + 1);
    {
        u8 *scriptPtr = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        scriptPtr[0x19] = (u8)(scriptPtr[0x19] + 1);
    }
    {
        s32 scriptIdx = (*(s16 *)(self + 0x22)) * 2;
        u8 *scriptBase = self + 0x18;
        u8 cmd = *(scriptBase + scriptIdx);
        void **table = *(void **)(self + 0x14);
        void *func = table[cmd];
        sub_080C31E0(self, func);
    }
    *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) - 1);
    if ((*(u16 *)(self + 2) & 0x8000) != 0) goto done;
    stepAnimationTrack(parent, body);
    sub_08011EE8(comp, *(s32 *)(fx + 8), 0);
cdc:
    sub_08059AD8(parent, comp);
    sub_08013C8C(self, parent);
    worldY = *(s32 *)(comp + 0xC) + *(s32 *)(fx + 0xC);
    coordBase = (u32)gCameraState;
    coordOff = 0x127C;
    coordVal = *(u32 *)(coordBase + coordOff + ((gMainWorkspace.f18A8 + 1) << 6));
    coordVal = (coordVal + 0xFFFF8000) & 0xFFFF0000;
    *(s32 *)((u8 *)parent + 0x18) = worldY - coordVal;
done:
    ;
}
