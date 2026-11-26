extern s32 sub_0805FEC8(u16);
extern void sub_0805FCFC(void);
extern void sub_08061F38(void);
extern u8 gMainWorkspace[];

typedef void (*Fn)(void *);

/* Scene step: run one frame of the scene named by the actor's +0x44 field and
 * publish its result byte at 0x02025FF0+0x14A4. When the scene ends (result 0),
 * either restart it (clear the gfx state, set the +0x14 command handler) or
 * run the teardown and dispatch the actor's callback at +0x24. */
void sub_0805FC70(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 sceneResult = sub_0805FEC8(*(u16 *)((u8 *)arg0 + 0x44));
    u32 resultOff = 0x14A4;
    u8 *resultByte = gMainWorkspace + resultOff;
    *resultByte = sceneResult;
    if ((u8)sceneResult == 0) {
        if (self[0x3C] != 0) {
            u32 handler;
            sub_0805FCFC();
            handler = 0x0805FCC9;
            *(u32 *)(self + 0x14) = handler;
            *(u16 *)(self + 0x22) = 1;
            ((Fn)handler)(arg0);
        } else {
            u32 handler;
            sub_08061F38();
            handler = *(u32 *)(self + 0x24);
            ((Fn)handler)(arg0);
        }
    }
}
