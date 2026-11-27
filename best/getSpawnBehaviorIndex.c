s32 getSpawnBehaviorIndex(void) {
    if (*(s16 *)0x020279E8 == 6) {
        return -1;
    }
    return 0;
}
