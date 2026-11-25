void sub_08016610(s32 type);

/* Release this key's registered objects, then clear the registry-data pointer
 * cached on its child state (key+0x3C field +0x30). */
void sub_08016678(void *key) {
    void *state;

    state = *(void **)((u8 *)key + 0x3C);
    sub_08016610((s32)key);
    *(s32 *)((u8 *)state + 0x30) = 0;
}
