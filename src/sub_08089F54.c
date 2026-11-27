extern s32 stepDelayTimer(s32, s32);
extern void createChildObject(s32, s32);
extern void sub_0806D588(s32, s32);
extern void sub_080C31E0(void *, s32);
extern u32 gMainWorkspace[];

/* Actor step: tick the timer at work+0x20. When it expires, set the game-state
 * word at 0x02025FF0+0x1C to 8, spawn effect 0x82 on the object at state+0x1864
 * and dispatch the actor's callback; otherwise re-tick and copy the object's
 * position into the sprite. */
void sub_08089F54(void *arg0)
{
    void *self;
    s32 *work;
    u8 *pos;
    s32 sprite;
    u8 *timer;
    u32 parentOff;
    s32 parent;
    self = arg0;
    work = *(s32 **)((u8 *)self + 0x6C);
    pos = (u8 *)work + 4;
    sprite = *(s32 *)((u8 *)self + 0x38);
    timer = (u8 *)work + 0x20;
    if (stepDelayTimer((s32)timer, sprite) == 0)
    {
        gMainWorkspace[7] = 8;
        parentOff = 0x1864;
        parent = *(s32 *)((u8 *)gMainWorkspace + parentOff);
        createChildObject(parent, 0x82);
        sub_080C31E0(self, *(s32 *)((u8 *)self + 0x24));
        return;
    }
    stepDelayTimer((s32)timer, sprite);
    sub_0806D588(sprite, (s32)pos);
}
