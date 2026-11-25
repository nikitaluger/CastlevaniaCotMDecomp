extern s32 sub_08011368(s32, s32, s32, s32);
extern s32 sub_08014900(s32);
extern s32 sub_0801491C(s32);
extern s32 sub_08014938(s32);
extern s32 sub_08014990(s32);
extern void sub_080149A4(s32, void *, void *, s32, s32);
extern void _call_via_r3(void *, void *, s32, s32);

/*
 * Countdown entity update: run the actor's display step, tick a timer on the
 * enemy's state block, and when it expires with matching coordinates dispatch
 * a script command; otherwise set the enemy's direction value from the actor.
 */
void sub_0803E308(void *self) {
    s32 *actor;
    u8 *enemy;
    u8 *enemyData;
    u8 *enemyState;
    s32 timer;
    s32 coordX;

    actor = *(s32 **)((u8 *)self + 0x38);
    enemy = *(u8 **)((u8 *)self + 0x3C);
    enemyData = enemy + 0x34;
    enemyState = enemy + 0x48;
    sub_08011368((s32)actor, (s32)enemyData, 0, 1);
    sub_080149A4((s32)actor, enemy, enemyState, 0x78, 0xF0);
    timer = *(u16 *)(enemyState + 2) - 1;
    *(u16 *)(enemyState + 2) = timer;
    if ((s32)(timer << 16) <= 0) {
        *(u16 *)(enemyState + 2) = 0x3C;
        if (sub_08014900(*(s32 *)(enemy + 8)) <= 0x300000 &&
            sub_0801491C(*(s32 *)(enemy + 0xC)) <= 0x300000) {
            coordX = sub_08014938(*(s32 *)(enemy + 8));
            if (coordX == sub_08014990((s32)actor)) {
                s16 scriptIndex = *(s16 *)((u8 *)self + 0x22);
                *((u8 *)self + scriptIndex * 2 + 0x19) = 0;
                {
                    s32 *pScriptParam = (s32 *)0x08671BD0;
                    _call_via_r3((u8 *)self + 0x18, (u8 *)self + 0x22, 1, *pScriptParam);
                }
                return;
            }
        }
    }
    if (sub_08014990((s32)actor) > 0) {
        *(s32 *)(enemy + 0x10) = 0x4000;
    } else {
        *(s32 *)(enemy + 0x10) = (s32)0xFFFFC000;
    }
}
