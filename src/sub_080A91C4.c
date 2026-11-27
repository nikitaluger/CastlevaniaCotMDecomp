/* Look up the current element of the actor's sequence, map its category to a
 * config entry, copy that config into the work struct, and fire the callback
 * at self+0x24 if the sequence's flag requests it. */
void setObjectAnimation(void *, void *, s32, s32);
void advanceAnimTrack(void *, void *);
void copyPoseAttrs(void *, void *);
void sub_080C31E0(void *, void *);

void sub_080A91C4(void *actor) {
    u8 *self = (u8 *)actor;
    s32 configIndex = 0;
    void *state = *(void **)(self + 0x38);
    void *work = *(void **)(self + 0x3C);
    u8 *seq = (u8 *)work + 0x34;
    void **tableRef;
    s32 elemIndex;
    u8 indexOffset;
    void *elemTable;
    u8 *elem;
    u32 category;
    setObjectAnimation(state, seq, 0x18, 0);
    advanceAnimTrack(state, seq);
    tableRef = *(void **)(seq + 0x08);
    elemIndex = *(s16 *)(seq + 0x0E);
    indexOffset = *(u8 *)(seq + 0x01);
    elemIndex = elemIndex + indexOffset;
    elemTable = *tableRef;
    elem = (u8 *)((s32)(elemIndex * 4) + (s32)elemTable - 4);
    category = *(u16 *)(elem + 2) - 0x21;
    if (category <= 9) {
        switch (category) {
            case 0: configIndex = 0; break;
            case 1: configIndex = 1; break;
            case 2: break;
            case 3: configIndex = 2; break;
            case 4: break;
            case 5: configIndex = 2; break;
            case 6: break;
            case 7: configIndex = 2; break;
            case 8: break;
            case 9: configIndex = 3; break;
        }
    }
    copyPoseAttrs(*(void **)((u8 *)work + 0x28), (void *)(0x081020FC + configIndex * 8));
    if (*(u8 *)(seq + 0x00) & 0x02) {
        void (*callback)(void *) = *(void (**)(void *))(self + 0x24);
        callback((void *)self);
    }
}
