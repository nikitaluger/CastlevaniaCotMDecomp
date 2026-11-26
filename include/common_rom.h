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

/* Flags in a spawn-state word (offset 0 of SpawnState). */
#define SPAWN_STATE_ACTIVE          1       /* state has been initialised */
#define SPAWN_STATE_CHILD_A         4       /* pending spawn uses the type-A helper */
#define SPAWN_STATE_CHILD_B         8       /* pending spawn uses the type-B helper */
#define SPAWN_STATE_CLEAR_CHILDREN  0xFFF3  /* mask clearing both pending-spawn bits */

/* Flags in an entity-origin word (offset 2 of OriginFlags). */
#define ORIGIN_FLIP_X 0x10  /* mirror the child's X offset */
#define ORIGIN_FLIP_Y 0x20  /* mirror the child's Y offset */

/* Added to a negative fixed-point coordinate before >>16 so it truncates
 * toward zero instead of toward negative infinity. */
#define FIXED_TRUNC_BIAS 0xFFFF

/* Script-reference types handled by the spawn-sprite command and the sprite
 * kinds they map to in the kind table. */
#define SCRIPT_REF_SPRITE_A 0x94
#define SCRIPT_REF_SPRITE_B 0x95
#define SPRITE_KIND_A       0x16
#define SPRITE_KIND_B       0x76

/* Set on a script thread while it waits for the spawned sprite. */
#define THREAD_FLAG_WAIT_SPRITE 0x1000

/* Thumb entry (sub_0801E5C8 + 1) run when the spawn command finishes. */
#define SCRIPT_CALLBACK_SPAWN_DONE 0x0801E5C9

/* Script-reference types and kinds for the second spawn-sprite command. */
#define SCRIPT_CMD2_REF_A   0x9E
#define SCRIPT_CMD2_REF_B   0x9F
#define SCRIPT_CMD2_KIND_A  0x22
#define SCRIPT_CMD2_KIND_B  0x6E

/* Thumb entry (sub_08022148 + 1) run when the second spawn command finishes. */
#define SCRIPT_CMD2_DONE_CALLBACK 0x08022149

/* Script-reference types and kinds for the third spawn-sprite command. */
#define SCRIPT_CMD3_REF_A  0x136
#define SCRIPT_CMD3_REF_B  0x137
#define SCRIPT_CMD3_KIND_A 0x58
#define SCRIPT_CMD3_KIND_B 0x6D

/* Script-reference types and sprite kinds for the spawn-attack command. */
#define SCRIPT_CMD_ATTACK_REF_A  0x155
#define SCRIPT_CMD_ATTACK_REF_B  0x156
#define SCRIPT_CMD_ATTACK_KIND_A 0x39
#define SCRIPT_CMD_ATTACK_KIND_B 0x7D

/* Fixed sprite kind and horizontal directions for the random-direction attack. */
#define SPRITE_KIND_RANDOM_ATTACK 0x2F
#define ATTACK_DIR_RIGHT         0x2000
#define ATTACK_DIR_LEFT          0xFFFFE000

/* Fixed sprite kind spawned at the thread's scripted spawn coordinates. */
#define SPRITE_KIND_SCRIPTED_SPAWN 0x25

/* Fixed sprite kind spawned with a small random position jitter. */
#define SPRITE_KIND_JITTERED_SPAWN 0x34

/* Animation kind and rendering flags for the three-part sprite spawn command. */
#define THREE_PART_SPRITE_KIND 0x66

/* Fixed effect kind spawned by scriptCmdSpawnKind87Effect at the thread's position reference. */
#define SPRITE_KIND_KIND87_EFFECT 0x87

/* Fixed effect kind spawned by scriptCmdSpawnFixedEffect at the thread's position reference. */
#define SPRITE_KIND_FIXED_EFFECT 0x55

/* Base of the main-object timer callback table. Script commands read entry 0 as the
 * completion callback passed to their indirect dispatch helper. */
#define MAIN_OBJ_TIMER_CALLBACK_TABLE 0x08671BB0

/* Fixed effect kind spawned as a projectile by scriptCmdSpawnProjectile. */
#define SPRITE_KIND_PROJECTILE 0x20

/* Fixed kind of the script-spawned object made of one sprite and three render parts. */
#define SPRITE_KIND_MULTI_PART 0x68

/* Layout of the paired-pose tables: gPairedPoseAttrs holds one 16-byte record per
 * pose, split into two 8-byte halves (one per actor); gPairedPoseBytes holds one
 * byte per actor per variant. */
#define PAIRED_POSE_ENTRY_SIZE 16
#define PAIRED_POSE_HALF_SIZE 8

/* Layout of the state block at Entity+0x3C for the scripted multi-part object:
 * 0x1C kind, 0x22 active slot, 0x24 saved update handler, 0x28/0x48/0x4C pointers
 * to the three render parts, and a graphics-slot init block at 0x34. */

/* Sprite identifiers and entity flag used by the scripted multi-part object
 * constructor (initScriptedMultiPartGraphics). */
#define MULTI_PART_SPRITE_KIND 0x19       /* animation/graphics kind index */
#define MULTI_PART_SPRITE_GFX_ID 0x8000000A
#define MULTI_PART_SPRITE_READY 0x1000    /* set on the entity once layers are ready */

/* Kind and lifetime fields of the timed effect built by spawnKind2CEffect. */
#define EFFECT_KIND_TIMED        0x2C
#define EFFECT_TIMER_INITIAL     0x12C
#define EFFECT_TIMER_INTERVAL    5

/* Sprite kind spawned by spawnKind57ScriptSprite. */
#define SPRITE_KIND_SCRIPT_TIMER 0x57

/* Sprite kind built from the entity's spawn parameters. */
#define SPRITE_KIND_SPAWN_PARAM 0x5E

/* Layouts used by the fixed-effect sprite constructor (spawnFixedEffectSprite).
 * Unique tags avoid clashing with inline definitions in other matched sources. */
struct FixedEffectSpriteLayer {
    u8 mode;         /* 0x00: playback mode */
    u8 active;       /* 0x01: 0 while spawning */
    u8 param2;       /* 0x02: 8 */
    u8 param3;       /* 0x03: 1 */
    u16 gfxIndex;    /* 0x04: tile id from gEffectGfxTable */
    u16 anim0;       /* 0x06: affine/OAM params */
    u16 anim1;       /* 0x08 */
    u16 anim2;       /* 0x0A */
    u16 anim3;       /* 0x0C */
    u16 palette;     /* 0x0E */
    u32 object;      /* 0x10: owner sprite */
    u16 timer;       /* 0x14 */
};

struct FixedEffectState {
    u8 _0[8];
    s32 worldX;      /* 0x08: world X, 16.16, from the entity parameter */
    s32 worldY;      /* 0x0C: world Y, 16.16 */
    u32 f10;
    u32 f14;
    u32 f18;         /* 0x18: set to 1 when spawning */
    s16 kind;        /* 0x1C: SPRITE_KIND_FIXED_EFFECT here */
    u8 _1E[4];
    s16 animSlot;    /* 0x22 */
    u32 savedHandler;/* 0x24: previous update handler */
    struct FixedEffectSpriteLayer *spriteLayer; /* 0x28 */
};

struct FixedEffectEntity {
    u8 _0[2];
    u16 flags;       /* 0x02 */
    u8 _4[0x22 - 4];
    s16 scriptStep;  /* 0x22 */
    u8 _24[0x38 - 0x24];
    u8 *sprite;      /* 0x38 */
    struct FixedEffectState *state; /* 0x3C */
    u8 _40[0x4C - 0x40];
    s16 posX;        /* 0x4C */
    u8 _4E[6];
    s16 posY;        /* 0x54 */
    u8 _56[0x5C - 0x56];
    s16 effectParam; /* 0x5C: index into gFixedEffectParamTable */
};

/* Workspace fields read by the fixed-effect spawn path. */
struct FixedEffectWorkspace {
    u8 _0[0x18A8];
    u8 frameCounter; /* 0x18A8: video-frame counter */
    u8 _18A9[0x19];
    u16 gfxFlags;    /* 0x18C2: sprite priority/blend bits */
};

struct FixedEffectScroll {
    u8 _0[0x1278];
    u32 scrollX;     /* 0x1278: per-frame BG scroll rows */
    u32 scrollY;     /* 0x127C */
};

/* Per-kind effect table entry: tile/palette ids for the render part. */
struct FixedEffectKindEntry {
    u8 _0[4];
    u16 f4;
    u16 f6;
    u8 _8[4];
    u16 gfxIndex;    /* 0x0C */
    u16 palette;     /* 0x0E */
    u8 _10[0x18];
};
