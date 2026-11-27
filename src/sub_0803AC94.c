s32 sub_080141AC(void *, void *);
void sub_080C31E0(void *, void *);
s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080C31E8(void *, void *, s32, void *);
extern void *sScriptStepCallbacks;

/* Runs an early-exit script, handles a pose transition, advances the pose to
 * select another script, then performs the entity's post-update. */
void sub_0803AC94(u8 *entity) {
    void *ownerRef = *(void **)(entity + 0x38);
    u8 *data = *(u8 **)(entity + 0x3C);
    u8 flag84;
    if (sub_080141AC(ownerRef, data) == 1 || (flag84 = *(u8 *)(entity + 0x84)) != 0) {
        sub_080C31E0(entity, *(void **)(entity + 0x24));
        return;
    }
    if (*(u16 *)(*(u8 **)(data + 0x28) + 0x14) & 1) {
        u16 newFlags = *(u16 *)data | 1;
        *(u16 *)data = newFlags;
    }
    if (*(u16 *)data & 1) {
        u8 *posePtr = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        u8 poseByte = *(u8 *)(posePtr + 0x1A);
        poseByte = poseByte - 2;
        if (poseByte > 1) {
            *(u8 *)(posePtr + 0x1B) = flag84;
            { void **scriptTable = &sScriptStepCallbacks;
              sub_080C31E8(entity + 0x18, entity + 0x22, 2, *scriptTable); }
        }
    }
    if (updateObjectDisplayState(ownerRef, data) == 0) {
        *(u32 *)(entity + 0x14) = (u32)0x0866DF54;
        *(u16 *)(entity + 0x22) = (u16)(*(u16 *)(entity + 0x22) + 1);
        {
            u8 *posePtr = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            posePtr[0x19] = (u8)(posePtr[0x19] + 1);
        }
        {
            s32 poseOffset = (*(s16 *)(entity + 0x22)) * 2;
            u8 *poseBase = entity + 0x18;
            u8 poseValue = *(poseBase + poseOffset);
            void **scriptTable = *(void **)(entity + 0x14);
            void *script = scriptTable[poseValue];
            sub_080C31E0(entity, script);
        }
        *(u16 *)(entity + 0x22) = (u16)(*(u16 *)(entity + 0x22) - 1);
    }
    sub_08013C8C(entity, ownerRef);
}
