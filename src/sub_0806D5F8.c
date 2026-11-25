extern s32 sub_080C364C(s32, u16);

/* Compute damage as attack^2 / defense / 10, clamped to the range 1..0xFFFF. */
u16 sub_0806D5F8(u16 attack, u16 defense) {
    s32 damage;
    u16 attackSq;

    attackSq = attack;
    damage = sub_080C364C(sub_080C364C(attackSq * attackSq, defense), 0xAU);
    if (damage <= 0) {
        damage = 1;
    }
    if (damage > 0xFFFF) {
        damage = 0xFFFF;
    }
    return (u16) damage;
}
