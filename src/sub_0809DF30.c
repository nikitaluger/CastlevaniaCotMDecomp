struct GameState { u8 _pad[0x10]; s32 flags; };
extern struct GameState gMainWorkspace;

extern void initCrossfadeGfxState(void);
extern void sub_08097EF4(s32, void *, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Handle the effect's colour state: when the work flags' bit 0 is set, apply
 * the screen-blend palette and switch the object to its next state handler;
 * otherwise clear the sprite's highlight bit, load the dark-blue palette, and
 * advance the script step. */
void sub_0809DF30(void *entity) {
    u8 *self = (u8 *)entity;
    void *sprite = *(void **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u16 flags = *(u16 *)work;
    s32 flag = 1;
    flag = flag & flags;
    if (flag != 0) {
        initCrossfadeGfxState();
        gMainWorkspace.flags = 3;
        sub_080C31E0(entity, *(s32 *)(self + 0x24));
        return;
    }
    *(u8 *)((u8 *)sprite + 0x2A) = (u8)(*(u8 *)((u8 *)sprite + 0x2A) & 0xBF);
    sub_08097EF4(0, (void *)0x083CEAAC, 0, 1);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = (u8)flag;
    {
        s32 *scriptCb = (s32 *)0x08671BB4;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptCb);
    }
}
