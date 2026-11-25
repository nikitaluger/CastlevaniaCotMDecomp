void sub_08011528(void *, void *);
void sub_080C31E0(void *, void *);
void sub_08013C8C(void *, void *);

/* Advance the actor's sprite animation, install action-script table 0x08670224,
 * bump the current sub-state's step counter, dispatch its handler and restore
 * the script pointer, then follow up on the actor (e.g. camera/edge check). */
void sub_080AEF88(void *arg0) {
    void *actor = *(void **)((u8 *)arg0 + 0x38);
    sub_08011528(actor, *(u8 **)((u8 *)arg0 + 0x3C) + 0x34);
    *(void **)((u8 *)arg0 + 0x14) = (void *)0x08670224;
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) + 1);
    {
        u8 *step = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        step[0x19] = (u8)(step[0x19] + 1);
        {
            s32 stepOffset = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
            u8 *script = (u8 *)arg0 + 0x18;
            u8 subState = *(script + stepOffset);
            void **table = *(void **)((u8 *)arg0 + 0x14);
            void *handler = table[subState];
            sub_080C31E0(arg0, handler);
        }
    }
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) - 1);
    sub_08013C8C(arg0, actor);
}
