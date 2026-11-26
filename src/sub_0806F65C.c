extern void sub_08003740(void *, s32);
extern void sub_08003A6C(void *, s32, s32);
extern void sub_08005E80(s32);
extern u16 sub_08007DD8(s32, s32, s32);
extern void sub_0806D2F8(void *, s32);
extern s32 sub_0806D518(void *, s32, void *);
extern void sub_0806D588(s32, void *);
extern void sub_0806E114(s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void *gMainObjTimerCallback;

struct TileState { u8 _0[0x18A8]; u8 tileIndex; };
extern struct TileState gMainWorkspace;
struct SceneState { u8 _0[4]; s32 coordX; u8 _8[0x2C]; u8 anim; };
struct BodyState { u8 _0[4]; s32 coordY; s32 offsetX; s32 offsetY; u8 _10[0x2C]; void *effect; u8 _40[8]; s32 aux48; };
struct EffectFlags { u8 _0[0x14]; u16 flags; };

/* Enemy tile-collision tick: if the shared guard allows it, test the body's
   projected position against the tile table; on a hit restart the animation,
   otherwise commit the motion offset and dispatch the action callback. */
void sub_0806F65C(u8 *arg0) {
    u8 *sceneState = *(u8 **)(arg0 + 0x6C);
    u8 *body = sceneState + 4;
    s32 sprite = *(s32 *)(arg0 + 0x38);
    u8 *bodyKeep = body;
    s32 busy = sub_0806D518(arg0, sprite, body);
    s32 collision;
    if (busy != 0) return;

    collision = (u16)sub_08007DD8(0x02023130 + (gMainWorkspace.tileIndex << 6),
                       ((struct SceneState *)sceneState)->coordX + ((struct BodyState *)body)->offsetX,
                       ((struct BodyState *)body)->coordY + ((struct BodyState *)body)->offsetY);
    if (collision != 0) {
        u8 *actionByte;
        s32 *callback;
        sub_08003A6C(sceneState + 0x30, 0, (void *)0x08472AB0);
        ((struct BodyState *)body)->offsetX = busy;
        ((struct BodyState *)body)->offsetY = busy;
        ((struct BodyState *)body)->aux48 = 0x4000;
        sub_08005E80(0x6F);
        actionByte = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
        *(u8 *)(actionByte + 0x19) = busy;
        callback = (s32 *)0x08671BB0;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *callback);
    } else {
        s32 zero;
        ((struct SceneState *)sceneState)->coordX = ((struct SceneState *)sceneState)->coordX + ((struct BodyState *)body)->offsetX;
        ((struct BodyState *)body)->coordY = ((struct BodyState *)body)->coordY + ((struct BodyState *)body)->offsetY;
        if (((struct EffectFlags *)((struct BodyState *)body)->effect)->flags & 1) {
            u8 *actionByte;
            s32 *callback;
            u8 *effect;
            sub_08003A6C(sceneState + 0x30, 0, (void *)0x08472AB0);
            ((struct BodyState *)body)->offsetX = collision;
            ((struct BodyState *)body)->offsetY = collision;
            ((struct BodyState *)body)->aux48 = 0x4000;
            sub_0806E114(*(s32 *)(arg0 + 0x28), 8, ((struct SceneState *)sceneState)->coordX, ((struct BodyState *)body)->coordY);
            effect = ((struct BodyState *)body)->effect;
            zero = 0;
            ((struct EffectFlags *)effect)->flags = collision;
            sub_08005E80(0x6F);
            actionByte = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
            *(u8 *)(actionByte + 0x19) = zero;
            callback = (s32 *)0x08671BB0;
            sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *callback);
        }
    }
    sub_0806D588(sprite, bodyKeep);
    sub_08003740(body + 0x2C, sprite);
    sub_0806D2F8(arg0, sprite);
}
