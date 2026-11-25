/* AI script step: pose the sprite at frame 0, set a flag on the effect and clear
 * one of its fields, reset this entity's sequence timer, then dispatch the next
 * script callback from the table at 0x08671BB0. */
extern void sub_080114A8(s32, void *, s32, s32);
extern void sub_0809C5F4(s32);
extern void sub_0809C4E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);

void sub_0809A3B8(void *entity)
{
    s32 sprite = *(s32 *)((u8 *)entity + 0x38);
    void *state = *(void **)((u8 *)entity + 0x3C);
    void *anim = (u8 *)state + 0x34;
    void *fx = (u8 *)state + 0x48;
    s32 *scriptCb;
    sub_080114A8(sprite, anim, 0, 0);
    sub_0809C5F4(*(s32 *)((u8 *)fx + 0x14));
    sub_0809C4E0(*(s32 *)((u8 *)fx + 0x08), 0);
    *(u8 *)((u8 *)entity + ((s32)*(s16 *)((u8 *)entity + 0x22) * 2) + 0x19) = 0;
    scriptCb = (s32 *)0x08671BB0;
    sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *scriptCb);
}
