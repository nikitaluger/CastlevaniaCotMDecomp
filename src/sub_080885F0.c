struct S_02025FF0 {
    u8 _0x000[0x1C];
    s32 field1C;
    u8 _0x020[0x14D8 - 0x20];
    u16 field14D8;
    u16 field14DA;
};
extern struct S_02025FF0 gMainWorkspace;

void sub_08003740(void *, void *);
void sub_08005E80(s32);
void sub_0806D588(void *, void *);
void sub_080C31E0(void *, s32);

/* Update a moving object: integrate its position, tick its repeating sound
 * timer, and once it leaves the screen trigger the event and return. */
void sub_080885F0(void *arg0)
{
    void *work;
    void *pos;
    void *obj;
    s32 timer;

    work = *(void **)((s8 *)arg0 + 0x6C);
    pos = (s8 *)work + 4;
    obj = *(void **)((s8 *)arg0 + 0x38);
    *(s32 *)((s8 *)work + 4) = *(s32 *)((s8 *)work + 4) + *(s32 *)((s8 *)pos + 8);
    timer = *(s32 *)((s8 *)pos + 0x14) - 1;
    *(s32 *)((s8 *)pos + 0x14) = timer;
    if (timer == 0) {
        sub_08005E80(0x69);
        *(s32 *)((s8 *)pos + 0x14) = 0x10;
    }
    if ((u32)(*(s32 *)((s8 *)obj + 0x14) + 0x100000) > 0x1180000U) {
        gMainWorkspace.field1C = 2;
        gMainWorkspace.field14D8 = 0xFFF4;
        gMainWorkspace.field14DA = 9;
        sub_080C31E0(arg0, *(s32 *)((s8 *)arg0 + 0x24));
        return;
    }
    sub_08003740((s8 *)work + 0x20, obj);
    sub_0806D588(obj, pos);
}
