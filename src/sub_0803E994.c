extern void sub_08011368(void *, void *, s32, s32);
extern s32 sub_08014990(void *);
extern void sub_080149A4(void *, void *, void *, s32, s32);

/*
 * Enemy step handler: play animation 2, apply the script's periodic flags
 * (bit 1 flips the actor's facing and adds 0x64 to the step timer, bit 2 runs
 * the countdown step), then set the enemy's direction/velocity word from which
 * way the actor is facing (0x3000 right, -0x3000 left).
 */
void sub_0803E994(void *self) {
    void *actor = *(void **)((u8 *)self + 0x38);
    void *enemy = *(void **)((u8 *)self + 0x3C);
    void *enemyData = (u8 *)enemy + 0x34;
    void *enemyState = (u8 *)enemy + 0x48;
    sub_08011368(actor, enemyData, 2, 1);
    if (*(u16 *)((u8 *)enemy + 2) & 1) {
        *(u16 *)enemyState = *(u16 *)enemyState + 0x64;
        *(u16 *)((u8 *)actor + 2) ^= 0x10;
    }
    if (*(u16 *)((u8 *)enemy + 2) & 4) {
        sub_080149A4(actor, enemy, enemyState, 0x64, 0xA0);
    }
    if (sub_08014990(actor) > 0) {
        *(s32 *)((u8 *)enemy + 0x10) = 0x3000;
    } else {
        *(s32 *)((u8 *)enemy + 0x10) = (s32)0xFFFFD000;
    }
}
