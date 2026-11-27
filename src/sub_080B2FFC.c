extern s32 spawnBudgetedEffect(s32 parent, s32 type);

/* Spawn one budgeted object of kind 0x1B8 under the given parent entity. */
void sub_080B2FFC(s32 parent) {
    spawnBudgetedEffect(parent, 0x1B8);
}
