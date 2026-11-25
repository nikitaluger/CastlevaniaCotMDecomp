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

/* Main update for a scripted entity: run the visibility/owner updates, perform
 * a one-time spawn action when flagged, then dispatch the current script step's
 * callback from the per-entity handler table. */
void sub_0805BA44(u8 *entity) {
    s32 owner = *(s32 *)(entity + 0x38);
    u8 *params = *(u8 **)(entity + 0x3C);

    sub_08013C5C(entity, owner);
    if (sub_080141AC(owner, params) == 1) {
        sub_080C31E0(entity, *(void **)(entity + 0x24));
        return;
    }
    if (sub_08013558(owner, params, *(void **)(params + 0x28)) != 0) {
        u8 *stepPtr = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        u8 zeroByte = 0;
        *(u8 *)(stepPtr + 0x1B) = zeroByte;
        { void **actionTable = &D_08671BDC;
          sub_080C31E8(entity + 0x18, entity + 0x22, 3, *actionTable); }
        sub_08013978(entity, *(void **)(params + 0x28));
    }
    sub_080142C0(entity, *(void **)(params + 0x28));
    if (*(u16 *)params & 1) {
        u8 *stepBase = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        if (*(u8 *)(stepBase + 0x1A) != 2) {
            sub_08013AC4(entity);
            {
                u8 *status = *(u8 **)(params + 0x28);
                u8 zeroByte = 0;
                *(status + 1) = zeroByte;
                {
                    u8 *stepPtr = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
                    *(u8 *)(stepPtr + 0x1B) = zeroByte;
                }
                { void **actionTable = &D_08671BDC;
                  sub_080C31E8(entity + 0x18, entity + 0x22, 2, *actionTable); }
            }
        }
    }
    if (sub_08013B5C(owner, params) == 0) {
        *(void **)(entity + 0x14) = (void *)0x0866E904;
        *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
        {
            u8 *stepPtr = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            stepPtr[0x19] = (u8)(stepPtr[0x19] + 1);
        }
        {
            s32 stepOffset = (*(s16 *)(entity + 0x22)) * 2;
            u8 *stepBase = entity + 0x18;
            u8 stepId = *(stepBase + stepOffset);
            void **callbackTable = *(void **)(entity + 0x14);
            void *callback = callbackTable[stepId];
            sub_080C31E0(entity, callback);
        }
        *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
    }
    sub_08013C8C(entity, owner);
}
