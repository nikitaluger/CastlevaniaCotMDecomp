extern s32 spawnBudgetedEffect(s32 parent, s32 type);

/* Spawn one budgeted object of kind 0x1A5 (an ambient effect) under the given
 * parent entity. */
void sub_080AACF8(s32 parent) {
    spawnBudgetedEffect(parent, 0x1A5);
}
