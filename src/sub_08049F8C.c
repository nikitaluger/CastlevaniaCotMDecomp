extern s32 D_08671BD0;
extern u32 gMainWorkspace[];
extern s32 sub_0801165C(void *, s32);
extern void sub_0804A4D0(void *, s32, s32, s32);
extern u32 sub_0804A4F0(void *, s32, void *, s32);
extern void sub_0804A650(void *, void *, s32);
extern void *sub_0805FAEC(s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/*
 * Enemy decision handler. Advances the enemy's coordinates, asks sub_0804A4F0
 * which action to take, then either switches animation state and runs a script
 * callback (case 1) or spawns a projectile with a facing-dependent velocity
 * (case 2).
 */
void sub_08049F8C(u8 *self) {
    u8 *actor = *(u8 **)(self + 0x38);
    u8 *enemy = *(u8 **)(self + 0x3C);
    u8 *enemyData = enemy + 0x34;
    u8 *enemyExtra = enemy + 0x48;
    s32 decision;
    void *projectile;
    s32 baseX;
    s32 baseY;

    sub_0801165C(enemy, 0);
    sub_0804A650(self, enemy, enemyExtra);
    decision = sub_0804A4F0(actor, enemyData, enemy, enemyExtra);
    switch (decision) {
    case 1:
        sub_0804A4D0(actor, enemyData, enemyExtra, 7);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *callback = &D_08671BD0;
            sub_080C31E8(self + 0x18, self + 0x22, 2, *callback);
        }
        return;
    case 2:
        projectile = sub_0805FAEC(gMainWorkspace[0x1870 / 4], 0x12B);
        if (projectile != NULL) {
            baseX = *(s32 *)(enemy + 8);
            *(s32 *)(projectile + 0x4C) = baseX + (*(volatile u16 *)(actor + 2) & 0x10 ? 0xC0000 : (s32)0xFFF40000);
            baseY = *(s32 *)(enemy + 0xC) + 0x40000;
            *(s32 *)(projectile + 0x5C) = baseY;
            {
                s32 faceFlag = *(volatile u16 *)(actor + 2) & 0x10;
                s32 xVel = 0xFFFE0000;
                if (faceFlag) {
                    xVel = 0x20000;
                }
                *(s32 *)(projectile + 0x6C) = xVel;
            }
            {
                u8 kind = *(u8 *)(self + 0x7C);
                *(u8 *)(projectile + 0x7C) = kind;
            }
        }
        return;
    }
}
