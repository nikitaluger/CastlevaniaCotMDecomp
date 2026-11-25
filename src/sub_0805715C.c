extern void sub_08013C5C(void *, s32);
extern s32 sub_080141AC(s32, void *);
extern s32 sub_08013558(s32, void *, void *);
extern void sub_08013978(void *, void *);
extern void sub_080142C0(void *, void *);
extern void sub_08013AC4(void *);
extern s32 sub_08013B5C(s32, void *);
extern void sub_08013C8C(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *D_08671BDC;

/* Runs the entity's periodic helpers, handles a pose transition, advances the
 * pose to select a script, then performs the post-update. */
void sub_0805715C(u8 *entity) {
    s32 ownerRef = *(s32 *)(entity + 0x38);
    u8 *data = *(u8 **)(entity + 0x3C);

    sub_08013C5C(entity, ownerRef);
    sub_080141AC(ownerRef, data);
    if (sub_08013558(ownerRef, data, *(void **)(data + 0x28)) != 0) {
        sub_08013978(entity, *(void **)(data + 0x28));
    }
    sub_080142C0(entity, *(void **)(data + 0x28));
    if (*(u16 *)data & 1) {
        u8 *posePtr = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        if (*(u8 *)(posePtr + 0x1A) != 6) {
            sub_08013AC4(entity);
            {
                u8 *posePtr = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
                u8 zero = 0;
                *(u8 *)(posePtr + 0x1B) = zero;
                { void **scriptTable = &D_08671BDC;
                  sub_080C31E8(entity + 0x18, entity + 0x22, 6, *scriptTable); }
            }
        }
    }
    if (sub_08013B5C(ownerRef, data) == 0) {
        *(u32 *)(entity + 0x14) = (u32)0x0866E7E0;
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
