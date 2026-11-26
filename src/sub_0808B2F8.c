extern s32 allocWorkSlot(void *, s32, s32, s32);
extern s32 sub_080C31E0(void *, s32);
extern s32 sub_080C31E4(void *, void *, s32);

/* Script step: allocate a 0x14-byte work buffer in slot 3. On failure, call
 * the entity's callback at +0x24; on success, clear this step's flag and
 * advance the command script. */
void sub_0808B2F8(void *self)
{
    s32 *advanceTable;
    int bufSize;
    s16 *stepPtr;
    bufSize = 0x14;
    if (allocWorkSlot(self, 0, bufSize, 3) == 0) {
        self = (s8 *)self;
        sub_080C31E0(self, *((s32 *)(self + 0x24)));
        return;
    }
    do {
        stepPtr = (s16 *)(self + 0x22);
        *((s8 *)(((s8 *)(((*stepPtr) * 2) + self)) + 0x19)) = 0;
        advanceTable = (s32 *)0x08671BB0;
    } while (0);
    sub_080C31E4(self + 0x18, self + 0x22, *advanceTable);
}
