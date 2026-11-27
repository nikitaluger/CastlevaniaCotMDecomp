void stepAnimationTrack(void *, void *);
void sub_08011EE8(void *, u32, u32);
s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_08013AC4(void *);
s32 updateObjectDisplayState(void *, void *);
void sub_08013C5C(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080141AC(void *, void *);
void sub_080142C0(void *, void *);
void sub_0803DDF0(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E8(void *, void *, u32, u32);

/*
 * Updates an entity's child sprite each frame: checks sprite visibility and
 * animation state, handles a flip request, advances the step script and
 * dispatches the sprite's current step handler.
 */
void sub_0803D588(void *obj) {
    void *sprite;
    void *owner;
    void *ownerWork;
    u8 *stepData;
    u32 *scriptTable;
    u8 *stepBase;
    u8 stepByte;
    u32 handlerTable;
    s32 handler;
    s32 stepOffset;

    sprite = *(void **)((u8 *)obj + 0x38);
    owner = *(void **)((u8 *)obj + 0x3C);
    ownerWork = (u8 *)owner + 0x34;
    if (sub_080141AC(sprite, owner) == 1) {
        if (*(u16 *)((u8 *)owner + 0x02) & 0x04) {
            return;
        }
    }
    sub_08013C5C(obj, sprite);
    if (sub_08013558(sprite, owner, *(void **)((u8 *)owner + 0x28)) != 0)
        sub_08013978(obj, *(void **)((u8 *)owner + 0x28));
    if (*(u16 *)owner & 1) {
        if (*(u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj + 0x1A) != 4) {
            sub_08013AC4(obj);
            *(u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj + 0x1B) = 0;
            scriptTable = (u32 *)0x08671BDC;
            sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, 4, *scriptTable);
        }
    }
    sub_080142C0(obj, *(void **)((u8 *)owner + 0x28));
    if (updateObjectDisplayState(sprite, owner) == 0) {
        *(u32 *)((u8 *)obj + 0x14) = 0x0866DFF8;
        *(u16 *)((u8 *)obj + 0x22) = *(u16 *)((u8 *)obj + 0x22) + 1;
        stepBase = (u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj);
        *(u8 *)(stepBase + 0x19) = *(u8 *)(stepBase + 0x19) + 1;
        stepOffset = (s32)(s16)(*(s16 *)((u8 *)obj + 0x22)) * 2;
        stepData = (u8 *)obj;
        stepData += 0x18;
        stepData += stepOffset;
        stepByte = *stepData;
        handlerTable = *(u32 *)((u8 *)obj + 0x14);
        handler = *(s32 *)((u32)(stepByte * 4) + handlerTable);
        sub_080C31E0((s32)obj, handler);
        *(u16 *)((u8 *)obj + 0x22) = *(u16 *)((u8 *)obj + 0x22) - 1;
        if (*(u16 *)((u8 *)obj + 2) & 0x8000) {
            return;
        }
        stepAnimationTrack(sprite, ownerWork);
        sub_08011EE8(owner, 0x16C1, 0);
    }
    sub_0803DDF0(sprite, owner);
    sub_08013C8C(obj, sprite);
}
