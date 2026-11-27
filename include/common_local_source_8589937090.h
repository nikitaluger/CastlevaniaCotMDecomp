/* context.h for DRACULA AGB1: shared by every function. Agents grow it with edit_context:
 * add a prototype or struct the moment you work one out, so the next function benefits. */

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;

/* struct layout used by sub_08005AB0 (offsets from m2c):
 * 0x13: u8 counter
 * 0x14: u32 pointer
 * 0x16: u16 index
 * 0x19: u32 pointer
 */
struct Foo {
    u8 unk_0x13;
    u32 unk_0x14;
    u16 unk_0x16;
    u32 unk_0x19;
};

extern vu32 D_0200A260;
extern vu32 D_0200A258;
typedef volatile s32 vs32;
typedef int s32_bool;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

extern void *sub_080015E0(s32 mask, s32 object);

/* Scaled main-object effect, shared by spawnScaledMainObjectEffect and
 * updateScaledMainObjectEffect. Offsets are from the effect's own base. */
struct ScaledFxHeader {          /* object+0x6C */
    u8 _00[0x04];
    s32 copy0;                   /* 0x04: eased X, mirrored from the source */
    u8 _08[0x4C];
    u8 kind;                     /* 0x54: copied from the spawning main object */
};

struct ScaledFxState {           /* ScaledFxHeader + 4 */
    s32 copy0;                   /* 0x00 */
    s32 copy1;                   /* 0x04: eased Y */
    u8 _08[0x24];
    void *gfx;                   /* 0x2C: graphics descriptor */
    u8 _30[0x1C];
    struct ScaledFxSource *source; /* 0x4C */
};

struct ScaledFxSource {
    u8 _00;
    u8 kind;                     /* 0x01: must match ScaledFxHeader.kind */
    u8 _02[0x0A];
    s32 goalX;                   /* 0x0C */
    s32 goalY;                   /* 0x10 */
};

struct ScaledFxTarget {          /* object+0x38 */
    u8 _00[0x04];
    u16 scaleX;                  /* 0x04 */
    u16 scaleY;                  /* 0x06 */
};

#define MAIN_OBJ_TIMER_CALLBACK_TABLE 0x08671BB0
#define SCRIPT_STEP_CALLBACK_TABLE    0x08671BD0
#define GWS_STATE_CHANGE_FIELD        0x14B8
#define GWS_PARITY_FIELD              0x1510
#define GWS_SCREEN_MODE_FIELD         0x173A
#define GWS_TIMER_FIELD               0x14ED
