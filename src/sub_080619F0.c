extern void sub_08006210(void);
extern void sub_08061E60(void);
extern void sub_08061ED0(s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Screen overlay parameters kept in IWRAM. */
struct ScreenParams { u8 _0[4]; u16 param0; u16 param1; };
/* Global scroll/mode state. */
struct ScrollState {
  u8 _0[0x1278];
  u32 scrollX;
  u32 scrollY;
  u8 _1[0x146C - 0x1280];
  u16 mode;
  u16 inputBits;
};
/* Flags controlling scroll input. */
struct ScrollInput { u8 _0[0x10]; u8 scrollXEnabled; u8 scrollYEnabled; };
extern struct ScreenParams gCrossfadeGfxState;
extern struct ScrollState gCameraState;
extern struct ScrollInput D_02027A00;
extern s32 gScriptStepCallbackTable;

/* Sub-state byte at task + index*2 + 0x19. */
struct TaskSubState { u8 _0[0x19]; u8 subState; };
/* Screen task: handler table, state index and cursor sprite. */
struct ScreenTask {
  u8 _0[0x14];
  void *handlers;
  u8 _1[0xA];
  s16 stateIndex;
  u8 _2[0x14];
  void *sprite;
};

/* Updates the scrolling screen task: refreshes the cursor sprite, pans the
 * view with directional input, and dispatches the current state handler. */
void sub_080619F0(struct ScreenTask *task)
{
  u8 *stateArgs;
  u32 stateOffset;
  sub_08061ED0((s32)task->sprite);
  gCrossfadeGfxState.param0 = 0x140;
  gCrossfadeGfxState.param1 = 0x60A;
  if (gCameraState.mode & 6) {
    sub_08006210();
    ((struct TaskSubState *)((u8 *)task + task->stateIndex * 2))->subState = 0;
    {
      s32 *callback = &gScriptStepCallbackTable;
      stateArgs = (u8 *)task + 0x18;
      sub_080C31E4(stateArgs, (u8 *)task + 0x22, *callback);
    }
    ((struct TaskSubState *)((u8 *)task + task->stateIndex * 2))->subState++;
    stateOffset = task->stateIndex * 2;
    sub_080C31E0(task, *(s32 *)((u8 *)task->handlers + *(u8 *)((u32)stateArgs + stateOffset) * 4));
    return;
  }
  if (D_02027A00.scrollXEnabled) {
    if (gCameraState.inputBits & 0x10) gCameraState.scrollX += 0x10000;
    if (gCameraState.inputBits & 0x20) gCameraState.scrollX += (s32)0xFFFF0000;
    sub_08061E60();
  }
  if (D_02027A00.scrollYEnabled) {
    if (gCameraState.inputBits & 0x80) gCameraState.scrollY += 0x10000;
    if (gCameraState.inputBits & 0x40) gCameraState.scrollY += (s32)0xFFFF0000;
    sub_08061E60();
  }
}
