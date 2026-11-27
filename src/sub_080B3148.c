extern s32 spawnBudgetedEffect(s32 parent, s32 type);

/* Spawn one budgeted object of kind 0x1BB (an effect) under the given
 * parent entity. */
void sub_080B3148(s32 parent) {
    spawnBudgetedEffect(parent, 0x1BB);
}
