extern s32 sub_08014990(void *);
extern void sub_0808DBB4(s32, s32, s32);
extern void setAnimationFrame(s32, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void *spawnBudgetedEffect(s32, s32);

struct S_02025FF0_1874 { u8 _p[0x1874]; u32 v; };
extern struct S_02025FF0_1874 gMainWorkspace;

/* Spawn effect sprite 8 at this actor's position plus a facing-adjusted (x, y)
 * offset taken from the per-kind offset table at 0x080CEB78. */
void sub_08030F90(void *arg0, void *arg1, s32 arg2) {
    u8 *table;
    s32 idx;
    s32 offX;
    s32 offY;
    table = (u8*)0x080CEB78;
    idx = arg2 * 8;
    offX = *(s32 *)(table + idx);
    table += 4;
    offY = *(s32 *)(table + idx);
    if (sub_08014990(arg0) > 0) {
        offX = -offX;
    }
    sub_0808DBB4(((s32 *)arg1)[2] + offX, ((s32 *)arg1)[3] + offY, 8);
}

/* Return this actor to idle: clear its sub-object's motion fields, play
 * animation 5 and, once it finishes, clear the step progress byte and run the
 * step's script handler. */
void sub_08030E88(void *arg0) {
    u8 *self = (u8*)arg0;
    s32 sprite = *(s32*)(self + 0x38);
    u8 *work = *(u8**)(self + 0x3C);
    u8 *anim = work + 0x34;
    s32 zero = 0;
    *(s32*)(work + 0x14) = zero;
    *(s32*)(work + 0x10) = zero;
    setAnimationFrame(sprite, anim, 5, 0);
    if (*(u8*)anim & 2) {
        *(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) = 0;
        sub_080C31E8(self + 0x18, self + 0x22, 0, *(s32*)0x08671BD0);
    }
}

/* Spawn a type-0xD4 entity at fixed-point world position (x, y): store the
 * integer part of each coordinate (0x4C/0x54). Returns the entity, or NULL. */
void *sub_0802F89C(s32 arg0, s32 arg1) {
    void *entity;
    s32 fixedX, fixedY;
    s32 tileX, tileY;
    entity = spawnBudgetedEffect(gMainWorkspace.v, 0xD4);
    if (entity == 0) return 0;
    fixedX = arg0;
    if (fixedX < 0) fixedX += 0xFFFF;
    tileX = fixedX >> 16;
    *(s16 *)((u8 *)entity + 0x4C) = tileX;
    fixedY = arg1;
    if (fixedY < 0) fixedY += 0xFFFF;
    tileY = fixedY >> 16;
    *(s16 *)((u8 *)entity + 0x54) = tileY;
    return entity;
}
