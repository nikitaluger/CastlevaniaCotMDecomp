/* Runs one step of an entity's action script: updates the entity's AI and
 * animation state, optionally triggers its special action, then dispatches
 * the script handler selected by the current command byte (from the function
 * table stored at self+0x14). */
void stepAnimationTrack(void *, void *);
void moveEntityWithCollision(void *, u32);
s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_08013AC4(void *);
s32 updateObjectDisplayState(void *, void *);
void sub_08013C5C(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080141AC(void *, void *);
void sub_080142C0(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E8(void *, void *, u32, u32);

/* Flag words at the head of the entity block */
struct EntityFlags {
    u16 f0; /* +0x00 */
    u16 f2; /* +0x02 */
    u16 f4; /* +0x04 */
    u16 f6; /* +0x06 */
    u16 f8; /* +0x08 */
    u16 fA; /* +0x0A */
    u16 fC; /* +0x0C */
    u16 fE; /* +0x0E */
};

void sub_0804D3A0(void *self) {
    void *work;
    void *entity;
    u8 *cmd;
    u8 *body;
    u8 *cmdPtr;
    u32 *cbTable;
    u8 *slot;
    u8 cmdId;
    u32 handlerTable;
    s32 handler;
    s32 cmdOffset;

    work = *(void **)((u8 *)self + 0x38);
    entity = *(void **)((u8 *)self + 0x3C);
    cmd = (u8 *)entity + 0x34;
    body = (u8 *)entity + 0x48;
    if (sub_080141AC(work, entity) != 1) {
        u16 endFlag;

        sub_08013C5C(self, work);
        if (sub_08013558(work, entity, *(void **)((u8 *)entity + 0x28)) != 0)
            sub_08013978(self, *(void **)((u8 *)entity + 0x28));
        sub_080142C0(self, *(void **)((u8 *)entity + 0x28));
        if (((struct EntityFlags *)entity)->f0 & 1) {
            if (*(u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self + 0x1A) != 2) {
                sub_08013AC4(self);
                *(u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self + 0x1B) = 0;
                cbTable = (u32 *)0x08671BDC;
                sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 2, *cbTable);
            }
        }
        if (updateObjectDisplayState(work, entity) == 0) {
            *(u32 *)((u8 *)self + 0x14) = 0x0866E4F8;
            *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) + 1;
            slot = (u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self);
            *(u8 *)(slot + 0x19) = *(u8 *)(slot + 0x19) + 1;
            cmdOffset = (s32)(s16)(*(s16 *)((u8 *)self + 0x22)) * 2;
            cmdPtr = (u8 *)self;
            cmdPtr += 0x18;
            cmdPtr += cmdOffset;
            cmdId = *cmdPtr;
            handlerTable = *(u32 *)((u8 *)self + 0x14);
            handler = *(s32 *)((u32)(cmdId * 4) + handlerTable);
            sub_080C31E0((s32)self, handler);
            *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) - 1;
            endFlag = *(u16 *)((u8 *)self + 2) & 0x8000;
            if (endFlag != 0) {
                return;
            }
            stepAnimationTrack(work, cmd);
            if (*(s16 *)(body + 6) == 1) {
                moveEntityWithCollision(entity, 0xB60);
                if (((struct EntityFlags *)entity)->f2 & 4) {
                    *(s16 *)(body + 6) = endFlag;
                }
            }
        }
        if (((struct EntityFlags *)entity)->f2 & 0x100) {
            ((struct EntityFlags *)entity)->f4 |= 0x100;
        } else {
            ((struct EntityFlags *)entity)->f4 &= 0xFEFF;
        }
        *(u16 *)((u8 *)*(void * volatile *)body + 4) = ((struct EntityFlags *)entity)->fA;
        *(u16 *)((u8 *)*(void * volatile *)body + 6) = ((struct EntityFlags *)entity)->fE + 1;
        sub_08013C8C(self, work);
    }
}
