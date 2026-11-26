extern void sub_080C31E0(void *, s32);
extern s32 signOf(s32);
extern void sub_08059DE0(s32, s32, s32);

/* Spawn the 0x166 object at the entity's position with variant 0 when the entity
 * is right of the map boundary and 1 when left of it, then switch the entity to
 * its next script state. */
void sub_08059A74(void *entity) {
    void *work;

    work = *(void **)((u8 *)entity + 0x3C);
    if (signOf(*(s32 *)((u8 *)work + 8)) < 0) {
        sub_08059DE0(*(s32 *)((u8 *)work + 8), *(s32 *)((u8 *)work + 0xC), 0);
    } else {
        sub_08059DE0(*(s32 *)((u8 *)work + 8), *(s32 *)((u8 *)work + 0xC), 1);
    }
    sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
}
