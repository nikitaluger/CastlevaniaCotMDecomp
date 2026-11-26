void sub_080C31E4(void *, void *, u32);
void setAnimationFrame(u32, void *, u32, u32);

/* Scripted object header: current command slot index (0x22), the callback run
 * by the command script (0x24), sprite object (0x38) and work/animation state
 * (0x3C). The per-slot frame counter sits at 0x19 + slot * 2. */
struct MainObj {
    u8 pad_0x00[0x22];
    s16 commandSlot;
    u32 updateCb;
    u8 pad_0x28[0x38 - 0x28];
    u32 sprite;
    u32 work;
};

/* Play animation frame 0x1B forward; after 80 frames on the current script
 * command, reset its timer and advance the command script using the script
 * pointer table at 0x08671BB0. */
void sub_0805066C(struct MainObj *entity) {
    u8 *slot;
    s16 slotIndex;
    void *cmdBuf;
    void *slotPtr;
    u32 *scriptTable;

    setAnimationFrame(entity->sprite, (u8 *)entity->work + 0x34, 0x1B, 1);
    slotIndex = entity->commandSlot;
    slot = (u8 *)((slotIndex << 1) + (u32)entity);
    if (slot[0x19] > 0x50) {
        slot[0x19] = 0;
        scriptTable = (u32 *)0x08671BB0;
        cmdBuf = (u8 *)entity + 0x18;
        slotPtr = (u8 *)entity + 0x22;
        sub_080C31E4(cmdBuf, slotPtr, *scriptTable);
    }
}
