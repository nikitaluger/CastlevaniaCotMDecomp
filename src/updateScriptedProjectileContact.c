s32 checkActorViewBounds(void *, void *);
void applySpritePaletteVariant(void *, void *);
s32 sub_0801BD58(void *);
s32 sub_08013558(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
void sub_0801BB90(void *);
void sub_0801BBB4(void *);
void updateActorWorldPosition(void *);
void sub_080C31E8(void *, void *, s32, u32);
s32 updateObjectDisplayState(void *, void *);
s32 sub_080C31E0(s32, s32);
void stepAnimationTrack(void *, void *);
void advanceMotion(void *, s32);
void sub_08013C8C(void *, void *);

extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866D630[];
extern u32 gScriptEventCallbacks[];

/* Updates a projectile/weapon entity: runs the hit and damage responses for its
 * owner and sub-object, dispatches a slot callback, then copies the owner's
 * camera-corrected world position back through the coordinate table. */
void updateScriptedProjectileContact(u8 *self) {
    u8 *parent;
    u8 *obj;
    u8 *objSub;
    u8 *objState;
    s16 mode;
    u8 *pt;
    u8 *pb;
    u32 idx;
    u32 camOff;
    u32 slotByte;
    u8 *slots;
    s32 slotOff;

    parent = *(u8 **)(self + 0x38);
    obj = *(u8 **)(self + 0x3C);
    objSub = obj + 0x34;
    objState = obj + 0x48;

    if (checkActorViewBounds(parent, obj) == 1) {
        *(u16 *)(objState + 0x12) = 0;
    } else {
        *(u16 *)(objState + 0x12) = 1;
    }
    *(u32 *)(objState + 0x20) = 0;

    mode = *(s16 *)(objState + 0x12);
    if (mode == 1) {
        applySpritePaletteVariant(self, parent);
        if (sub_0801BD58(self) == 0) {
            if (sub_08013558(parent, obj, *(void **)(obj + 0x28)) != 0) {
                *(u16 *)(objState + 0x14) = 1;
                spawnContactEffectOnHit(self, *(void **)(obj + 0x28));
            }
        }
        uploadPendingSpriteGraphic(self, *(void **)(obj + 0x28));

        if ((*(u16 *)obj & 1) && *(u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self + 0x1A) != 9) {
            u32 *callbackArg;
            sub_0801BB90(self);
            sub_0801BBB4(self);
            updateActorWorldPosition(self);
            *(u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self + 0x1B) = 0;
            callbackArg = gScriptEventCallbacks;
            sub_080C31E8(self + 0x18, self + 0x22, 9, *callbackArg);
        }
    }

    if (updateObjectDisplayState(parent, obj) == 0) {
        u8 *slot;
        *(u32 *)(self + 0x14) = (u32)D_0866D630;
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
        slot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        *(u8 *)(slot + 0x19) = *(u8 *)(slot + 0x19) + 1;
        slotOff = *(s16 *)(self + 0x22) * 2;
        slots = self;
        slots += 0x18;
        slotByte = *(u8 *)((u32)slots + (u32)slotOff);
        sub_080C31E0((s32)self, *(u32 *)(*(u32 *)(self + 0x14) + slotByte * 4));
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
        if ((*(u16 *)(self + 2) & 0x8000) == 0) {
            stepAnimationTrack(parent, objSub);
            advanceMotion(obj, 0);
        } else {
            return;
        }
    }

    sub_08013C8C(self, parent);

    {
        s32 baseCoord = *(s32 *)(obj + 0x0C) + *(s32 *)(objState + 0x20);
        pt = gCameraState;
        pb = gMainWorkspace;
        pb += 0x18A8;
        idx = ((u32)*pb + 1) * 0x40;
        pt += 0x127C;
        camOff = *(u32 *)(pt + idx);
        *(u32 *)(parent + 0x18) = baseCoord - ((camOff + 0xFFFF8000) & 0xFFFF0000);
    }
}
