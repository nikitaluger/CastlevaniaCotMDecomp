void sub_080161F0();
void sub_08015974();
void sub_08016678(void *);
void sub_08020E78(void *);
s32 sub_080C31E0(void *, s32);

/* Per-frame entity update: free the two optional attached objects
 * (scriptState+0x28 / +0x2C), release the three attached effect slots, refresh
 * them, then chain to the entity's previous update handler
 * (scriptState+0x24, saved when this updater was installed). */
void sub_08020E44(void *arg0) {
    void *obj = arg0;
    void *scriptState = *(void **)((u8 *)obj + 0x3C);
    if (*(s32 *)((u8 *)scriptState + 0x28) != 0) {
        sub_080161F0();
    }
    if (*(s32 *)((u8 *)scriptState + 0x2C) != 0) {
        sub_08015974();
    }
    sub_08020E78(obj);
    sub_08016678(obj);
    sub_080C31E0(obj, *(s32 *)((u8 *)scriptState + 0x24));
}
