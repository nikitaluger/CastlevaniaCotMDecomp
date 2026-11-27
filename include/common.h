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

/* Script/timer data tables and graphics image id used by the main-object effect spawner. */
#define MAIN_OBJ_EFFECT_SCRIPT_TABLE 0x084D99AC
#define MAIN_OBJ_EFFECT_TIMER_DATA   0x084D9A24
#define MAIN_OBJ_EFFECT_GFX_ID       0x56

/* Animation descriptor installed on the sprite spawned for a main object. */
#define MAIN_OBJ_SPRITE_EFFECT_ANIM_DESC 0x08100258

/* Kind and starting animation frame of the effect spawned from a main object. */
#define SPRITE_KIND_MAIN_OBJ_EFFECT 0x69
#define MAIN_OBJ_EFFECT_START_FRAME 0xC

/* Large scaled effect spawned from a main object's script (spawnScaledMainObjectEffect). */
#define SCALED_MAIN_OBJ_EFFECT_SCRIPT_TABLE 0x08499408
#define SCALED_MAIN_OBJ_EFFECT_TIMER_DATA   0x08499690
#define SCALED_MAIN_OBJ_EFFECT_GFX_ID       0x2B

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

/* Collision flags at offset 4 of a moving object. */
#define OBJ_CHECK_ENTITIES  0x10  /* probe other entities while moving */
#define OBJ_CHECK_FLOOR     0x08  /* probe the tile one step below */
#define OBJ_CHECK_CEILING   0x20  /* probe the tile one step above */

/* Touch flags written to offset 2 of a moving object. */
#define TOUCH_ENTITY_HIT    0x200 /* horizontal probe hit another entity */
#define TOUCH_WALL_LEFT     0x01  /* blocked to the left */
#define TOUCH_WALL_RIGHT    0x02  /* blocked to the right */
#define TOUCH_CEILING_HIT   0x10  /* blocked above */

/* Bits of the probe output word that mean a horizontal obstruction. */
#define PROBE_WALL_BITS     0x06

/* Bits of the per-tile terrain word that block horizontal movement. */
#define TERRAIN_BLOCK_MOVE  0x0A
#define TERRAIN_SOLID       0x01

/* Sprite kind and render-part constants used by the single-part scripted
 * effect constructor (initScriptedSinglePartGraphics). */
#define SPRITE_KIND_SCRIPTED_SINGLE_PART 0x31 /* animation/graphics kind index */
#define RENDER_PART_KIND                 5    /* kind byte of an allocated render part */

/* gScriptedEffectGfxDataA/B hold alternate 32-bit sprite graphics ids; the
 * constructor combines their first two entries into a four-way selection
 * indexed by the entity's variant byte. gScriptedEffectLayerAttrs holds the
 * per-layer animation attributes copied into the render part. */
extern u16 gScriptedEffectLayerAttrs[];
extern u32 gScriptedEffectGfxDataA[];
extern u32 gScriptedEffectGfxDataB[];

/* Single render part allocated by allocEffectPart. */
struct ScriptedEffectLayer {
    u8 mode;         /* 0x00 */
    u8 kind;         /* 0x01: RENDER_PART_KIND */
    u8 layer;        /* 0x02 */
    u8 priority;     /* 0x03 */
    u16 gfxIndex;    /* 0x04: tile id from gEffectGfxTable */
    u16 anim0;       /* 0x06 */
    u16 anim1;       /* 0x08 */
    u16 anim2;       /* 0x0A */
    u16 anim3;       /* 0x0C */
    u16 palette;     /* 0x0E */
    u32 object;      /* 0x10: owner sprite */
    u16 tail;        /* 0x14 */
};

/* Work state in the entity's slot at +0x3C. */
struct ScriptedEffectWork {
    u8 _0[8];
    s32 worldX;      /* 0x08: fixed-point X */
    s32 worldY;      /* 0x0C: fixed-point Y */
    u32 radiusA;     /* 0x10 */
    u32 radiusB;     /* 0x14 */
    u32 state;       /* 0x18 */
    s16 kind;        /* 0x1C: SPRITE_KIND_SCRIPTED_SINGLE_PART */
    u8 _1E[4];
    s16 animSlot;    /* 0x22 */
    u32 updateCb;    /* 0x24 */
    struct ScriptedEffectLayer *layer; /* 0x28 */
};

/* Scripted entity that owns the effect. */
struct ScriptedEffectEntity {
    u8 _0[2];
    u16 flags;       /* 0x02 */
    u8 _4[0x22 - 4];
    s16 scriptStep;  /* 0x22 */
    u8 _24[0x38 - 0x24];
    u8 *sprite;      /* 0x38 */
    struct ScriptedEffectWork *work; /* 0x3C */
    u8 _40[0x4C - 0x40];
    s32 worldX;      /* 0x4C */
    u8 _50[0x5C - 0x50];
    s32 worldY;      /* 0x5C */
    u8 _60[0x7C - 0x60];
    u8 variant;      /* 0x7C: selects a graphics id */
    u8 _7D[0x8C - 0x7D];
    u32 initialized; /* 0x8C */
};

/* Workspace fields read while placing the sprite. */
struct ScriptedEffectWorkspace {
    u8 _0[0x18A8];
    u8 frameCounter; /* 0x18A8 */
    u8 _18A9[0x19];
    u16 gfxFlags;    /* 0x18C2: sprite priority/blend bits */
};

/* Camera scroll rows, indexed by (frameCounter + 1) * 0x40. */
struct ScriptedEffectScroll {
    u8 _0[0x1278];
    u32 scrollX;     /* 0x1278 */
    u32 scrollY;     /* 0x127C */
};

/* Per-kind graphics entry pointed to by gEffectGfxTable. */
struct ScriptedEffectKindEntry {
    u8 _0[4];
    u16 gfxIndex;    /* 0x04 */
    u16 palette;     /* 0x06 */
    u8 _8[0x28 - 8];
};

/* Kind and graphics id used by the kind-0x4F attack-effect spawner. */
#define SPRITE_KIND_ATTACK_EFFECT 0x4F
#define ATTACK_EFFECT_GFX_ID      0x8000000B

/* Affine/OAM parameters copied into the kind-0x4F attack effect's render
 * descriptor; gSpriteKindTable carries its tile ids and effect parameter. */
extern u16 gAttackEffectAffineParams[];

/* Render descriptor allocated by allocEffectPart for the kind-0x4F attack. */
struct AttackEffectSpriteDef {
    u8 mode;           /* 0x00 */
    u8 active;         /* 0x01: 0 while spawning */
    u8 param2;         /* 0x02: 8 */
    u8 param3;         /* 0x03: 1 */
    u16 gfxA;          /* 0x04: tile id from gSpriteKindTable */
    u16 affine0;       /* 0x06 */
    u16 affine1;       /* 0x08 */
    u16 affine2;       /* 0x0A */
    u16 affine3;       /* 0x0C */
    u16 gfxB;          /* 0x0E: second tile id */
    u32 sprite;        /* 0x10: owner sprite */
    u16 timer;         /* 0x14 */
};

/* Work state held in the thread's +0x3C slot. */
struct AttackEffectWork {
    u8 _0[8];
    s32 x;             /* 0x08: world X, 16.16, from the position reference */
    s32 y;             /* 0x0C: world Y, 16.16 */
    u32 _10;
    u32 _14;
    u32 param;         /* 0x18: from gSpriteKindTable */
    s16 kind;          /* 0x1C: SPRITE_KIND_ATTACK_EFFECT */
    u8 _1E[4];
    s16 slot;          /* 0x22 */
    u32 updateFn;      /* 0x24: previous update handler, saved here */
    struct AttackEffectSpriteDef *spriteDef; /* 0x28 */
};

/* Position reference carried by a script thread. */
struct EffectPositionRef { s16 x; s16 y; };
struct EffectPositionHolder { u8 _0[4]; struct EffectPositionRef *position; };

/* Script thread that owns the spawned effect. */
struct AttackEffectThread {
    u8 _0[2];
    u16 flags;         /* 0x02 */
    u8 _4[0x22 - 4];
    s16 stateIndex;    /* 0x22 */
    u8 _24[0x38 - 0x24];
    u8 *sprite;        /* 0x38 */
    struct AttackEffectWork *state; /* 0x3C */
    u8 _40[0x4C - 0x40];
    s16 f4C;
    u8 _4E[6];
    s16 f54;
    u8 _56[0xAC - 0x56];
    struct EffectPositionHolder *refHolder; /* 0xAC */
};

/* 20-byte per-kind entry: gfxA, param, gfxB. */
struct AttackEffectKindEntry { u16 gfxA; s16 param; u16 gfxB; u8 _6[0x14 - 6]; };

/* Initial sprite state and horizontal-mirror bit used by the state-driven
 * effect spawner. sub_080322B0 picks per-state parameters from this state. */
#define EFFECT_SPRITE_STATE_INITIAL 0x2E
#define SPRITE_OAM_FLIP_X           0x10

/* Affine/OAM parameters copied into the state-driven effect's render
 * descriptor (analogous to gAttackEffectAffineParams). */
extern u16 gStateEffectAffineParams[];

/* Parent entity carrying the spawn kind, coordinates and facing direction. */
struct StateDrivenEffectEntity {
    u8 _0[2];
    u16 flags;                      /* 0x02 */
    u8 _4[0x22 - 4];
    s16 stateIndex;                 /* 0x22 */
    u8 _24[0x38 - 0x24];
    u8 *sprite;                     /* 0x38 */
    struct AttackEffectWork *state; /* 0x3C */
    u8 _40[0x4C - 0x40];
    s16 spawnX;                     /* 0x4C */
    u8 _4E[6];
    s16 spawnY;                     /* 0x54 */
    u8 _56[0x5C - 0x56];
    s16 direction;                  /* 0x5C: > 0 mirrors the sprite */
    u8 _5E[0x64 - 0x5E];
    s16 kind;                       /* 0x64: selects the sprite kind */
};

/* Per-kind graphics entry whose tile ids sit at +0x08 and +0x0A. */
struct StateDrivenEffectKindEntry { u8 _0[8]; u16 gfxA; u16 gfxB; u8 _c[0x28 - 0xC]; };

/* Render part of a paired scripted effect. */
struct PairedEffectPart {
    u8 mode;       /* 0x00 */
    u8 kind;       /* 0x01: RENDER_PART_KIND */
    u8 layer;      /* 0x02: 8 */
    u8 priority;   /* 0x03: 1 */
    u16 gfxIndex;  /* 0x04: tile id from gSpriteKindTable */
    u16 anim0;     /* 0x06 */
    u16 anim1;     /* 0x08 */
    u16 anim2;     /* 0x0A */
    u16 anim3;     /* 0x0C */
    u16 palette;   /* 0x0E */
    u32 object;    /* 0x10: owner sprite */
};

/* Work state in the paired effect entity's +0x3C slot. */
struct PairedEffectWork {
    u8 _0[8];
    s32 worldX;    /* 0x08 */
    s32 worldY;    /* 0x0C */
    u8 _10[0xC];
    s16 kind;      /* 0x1C */
    u8 _1E[0xA];   /* contains the active slot at 0x22 */
    struct PairedEffectPart *part; /* 0x28 */
};

/* Per-kind graphics entry used by the paired effect. */
struct PairedEffectKindEntry { u16 gfxIndex; u16 _2; u16 palette; u8 _6[0xE]; };

/* Kind-selected effect spawner (spawnKindSelectedEffect): shared layouts. */

/* Render layer allocated by allocEffectPart and installed at work+0x28. */
struct KindEffectLayer {
    u8 mode;         /* 0x00 */
    u8 active;       /* 0x01: 0 while spawning */
    u8 layer;        /* 0x02: 8 */
    u8 priority;     /* 0x03: 1 */
    u16 gfxA;        /* 0x04: tile id from gEffectGfxTable */
    u16 affine0;     /* 0x06 */
    u16 affine1;     /* 0x08 */
    u16 affine2;     /* 0x0A */
    u16 affine3;     /* 0x0C */
    u16 gfxB;        /* 0x0E: second tile id */
    u32 object;      /* 0x10: owner sprite */
    u16 timer;       /* 0x14 */
};

/* Work state in the parent entity's +0x3C slot. */
struct KindEffectWork {
    u8 _0[8];
    s32 x;           /* 0x08: world X, 16.16 */
    s32 y;           /* 0x0C: world Y, 16.16 */
    u32 _10;
    u32 _14;
    u32 param;       /* 0x18: set to 1 while spawning */
    s16 kind;        /* 0x1C: spawn kind */
    u8 _1E[4];
    s16 slot;        /* 0x22: graphics slot index */
    u32 updateFn;    /* 0x24: previous update handler */
    struct KindEffectLayer *layer; /* 0x28 */
};

/* Parent entity that requested the effect. */
struct KindEffectEntity {
    u8 _0[2];
    u16 flags;       /* 0x02: EFFECT_SPRITE_READY set on success */
    u8 _4[0x22 - 4];
    s16 stateIndex;  /* 0x22 */
    u8 _24[0x38 - 0x24];
    u8 *sprite;      /* 0x38 */
    struct KindEffectWork *work; /* 0x3C */
    u8 _40[0x4C - 0x40];
    s16 spawnX;      /* 0x4C */
    u8 _4E[6];
    s16 spawnY;      /* 0x54 */
    u8 _56[0x5C - 0x56];
    s16 effectParam; /* 0x5C: index into gKindEffectParamTable */
    u8 _5E[0x6C - 0x5E];
    s16 kind;        /* 0x6C: selects the effect kind */
};

/* 0x28-byte per-kind graphics entry: tile ids at +4 and +6. */
struct KindEffectGfxEntry { u8 _0[4]; u16 gfxA; u16 gfxB; u8 _8[0x28 - 8]; };

/* First four u16s are copied into the render layer's affine/OAM fields. */
extern u16 gKindEffectAffineParams[];
/* 8-byte-strided table indexed by the entity's effectParam. */
extern u32 gKindEffectParamTable[];

#define EFFECT_SPRITE_READY   0x1000      /* flags bit set on the parent after spawn */
#define EFFECT_SPRITE_GFX_ID  0x8000000A
#define EFFECT_LAYER_KIND     8
#define EFFECT_LAYER_PRIORITY 1
#define EFFECT_WORLD_SCALE    0x10000
#define EFFECT_SCROLL_STEP    0x40
#define EFFECT_WORK_SLOT_SIZE 0xAC
#define EFFECT_ANIM_FRAME     0x0F

/* Script-driven effect spawner (spawnScriptedEffectObject): shared layouts. */

/* Sprite object created by the scripted spawner. */
struct ScriptedObjectSprite {
    u16 attrs;       /* 0x00: OAM attribute 0 */
    u16 attrs2;      /* 0x02: OAM attribute 1 (flip bits) */
    u8 _4[0x14 - 4];
    u32 posX;        /* 0x14: screen-space X */
    u32 posY;        /* 0x18: screen-space Y */
    u32 gfxId;       /* 0x1C: graphics id */
};

/* Entity whose script drives the spawn. */
struct ScriptedSpawnEntity {
    u8 _0[2];
    u16 flags;       /* 0x02: EFFECT_SPRITE_READY set on success */
    u8 _4[0x10];
    u32 scriptTable; /* 0x14: table of script command handlers */
    u8 _18[0xA];
    s16 stateIndex;  /* 0x22 */
    u32 updateFn;    /* 0x24: previous update handler */
    u8 _28[0x10];
    u32 sprite;      /* 0x38 */
    struct KindEffectWork *work; /* 0x3C */
    u8 _40[0xC];
    u32 spawnX;      /* 0x4C */
    u8 _50[0xC];
    u32 spawnY;      /* 0x5C */
    u8 _60[0xC];
    u8 flip;         /* 0x6C: mirrors the sprite when set */
    u8 _6D[3];
    u8 variant;      /* 0x70: selects the starting animation frame */
};

/* Affine/OAM params table addressed by the scripted-effect spawner; declared
 * candidate-local because another function views the same bytes as u8. */

/* Graphics id installed at sprite+0x1C and kind installed in the work state. */
#define SCRIPT_OBJECT_GFX_ID      0x80000009
#define SCRIPT_OBJECT_KIND        0x1A
#define SCRIPT_OBJECT_WORK_SLOT   0x64
#define SCRIPT_OBJECT_ANIM_DATA   0x080CD538
#define SCRIPT_OBJECT_FRAME_FLIP  0x12
#define SCRIPT_OBJECT_FRAME_BASE  0x0D

/* Fixed-kind attack spawner (spawnFixedKindEffect): shared layouts. */

/* Work state in the parent entity's +0x3C slot. */
struct FixedAttackWork {
    u8 _0[8];
    s32 x;           /* 0x08: world X, 16.16 */
    s32 y;           /* 0x0C: world Y, 16.16 */
    u32 paramA;      /* 0x10: copied from the parent */
    u32 paramB;      /* 0x14: copied from the parent */
    u32 param;       /* 0x18 */
    s16 kind;        /* 0x1C: SPRITE_KIND_FIXED_ATTACK */
    u8 _1E[4];
    s16 slot;        /* 0x22 */
    u32 updateFn;    /* 0x24: previous update handler */
    struct KindEffectLayer *layer; /* 0x28 */
};

/* Parent entity requesting the fixed-kind attack. */
struct FixedAttackEntity {
    u8 _0[2];
    u16 flags;       /* 0x02 */
    u8 _4[0x22 - 4];
    s16 stateIndex;  /* 0x22 */
    u8 _24[0x38 - 0x24];
    u8 *sprite;      /* 0x38 */
    struct FixedAttackWork *work; /* 0x3C */
    u8 _40[0x4C - 0x40];
    s16 spawnX;      /* 0x4C */
    u8 _4E[6];
    s16 spawnY;      /* 0x54 */
    u8 _56[0x5C - 0x56];
    u16 animFlags;   /* 0x5C: selects the starting animation */
    u8 _5E[0x6C - 0x5E];
    u32 paramA;      /* 0x6C */
    u8 _70[0x7C - 0x70];
    u32 paramB;      /* 0x7C */
};

/* Per-kind graphics entry: tile ids at +8 and +0x0A. */
struct FixedAttackGfxEntry { u8 _0[8]; u16 gfxA; u16 gfxB; u8 _C[0x28 - 0xC]; };
extern u16 gFixedAttackAffineParams[];

#define SPRITE_KIND_FIXED_ATTACK  0x1E
#define FIXED_ATTACK_PARAM        2
#define FIXED_ATTACK_WORK_SLOT    0x48
#define FIXED_ATTACK_ANIM_FLAG_A  0x100
#define FIXED_ATTACK_ANIM_FLAG_B  0x200
#define FIXED_ATTACK_FRAME_A      0x13
#define FIXED_ATTACK_FRAME_B      0x15
#define FIXED_ATTACK_FRAME_C      0x17

/* ---------- Shared action-step layouts (runActionStep and its helpers) ---------- */

/* Actor owning the action. Its work state hangs off the pointer at +0x6C (extra + 4). */
struct ActionActor {
    u8 pad0[0x18];
    u8 kind;            /* 0x18: action/sprite kind */
    u8 pad19[9];
    s16 stateIndex;     /* 0x22: current script-step index */
    u8 pad24[0x14];
    u32 context;        /* 0x38: action-context handle */
    u8 pad3C[0x30];
    u32 extra;          /* 0x6C: pointer to the work state minus 4 */
};

/* Work state reached through actor->extra + 4. */
struct ActionWorkState {
    u8 pad0[8];
    u32 stateA;         /* 0x08 */
    u32 pad0C;
    u8 pad10[0x1A];
    u16 pad2A;
    u16 pad2C;
    u8 pad2E[0x12];
    u32 activeA;        /* 0x40 */
    u32 pad44;
    u8 pad48[4];
    u32 activeC;        /* 0x4C */
    u32 pad50;
    u8 pad54[0x64];
    u32 flagsB8;        /* 0xB8 */
    u8 padBC[8];
    u32 resultCode;     /* 0xC4 */
    u8 padC8[4];
    u16 actionFlags;    /* 0xCC: direction/animation flags */
};

/* Global fields read by the action step. */
struct ActionWorkspace {
    u8 pad0[0x24];
    u32 modeFlags;      /* 0x24 */
    u16 modeMask;       /* 0x28 */
    u8 pad2A[0x14C3];
    u8 actionState;     /* 0x14ED */
};

struct ActionCameraState {
    u8 pad0[0x146C];
    u16 faceFlags;      /* 0x146C */
};

/* Animation sequence tables and step-callback indices used on cancel/fail. */
#define ACTION_ANIM_CANCEL       0x084A67C0
#define ACTION_ANIM_NO_DIR       0x084A6814
#define ACTION_ANIM_FAIL         0x084A67F4
#define ACTION_STEP_CANCEL       0x26
#define ACTION_STEP_NO_DIR       0x24
#define ACTION_STEP_FAIL         0x23
#define ACTION_STEP_RESET        4
#define ACTION_STATE_FLAG_OFFSET 0x3BC
#define ACTION_KIND_RESET        0x25

/* Animation tables and step ids specific to the alternate action-step handler. */
#define ACTION_ALT_STEP_CANCEL   0x2B   /* cancel: directional animation was selected */
#define ACTION_ALT_STEP_NO_DIR   0x29   /* no facing direction resolved */
#define ACTION_ALT_STEP_FAIL     0x28   /* step failed / no active state left */
#define ACTION_ALT_KIND_RESET    0x2A   /* actor kind that resets the entity form */
#define ACTION_ALT_ANIM_NO_DIR   0x084FCA3C  /* sequence used when no direction resolves */
#define ACTION_ALT_ANIM_FAIL     0x084FCA84  /* sequence used when the step fails */

/* Graphics presets for the effect spawned by spawnActionEffect, keyed by the
 * kind byte in the workspace. The three kinds scale a stat by 71/100/141%. */
#define ACTION_EFFECT_KIND_SMALL   0x37
#define ACTION_EFFECT_KIND_MEDIUM  0x39
#define ACTION_EFFECT_KIND_LARGE   0x3A
#define ACTION_EFFECT_SCALE_SMALL  0x47
#define ACTION_EFFECT_SCALE_MEDIUM 0x64
#define ACTION_EFFECT_SCALE_LARGE  0x8D
#define ACTION_EFFECT_ANIM_SMALL   0x33
#define ACTION_EFFECT_ANIM_MEDIUM  0x34
#define ACTION_EFFECT_ANIM_LARGE   0x35
#define ACTION_EFFECT_GFX_STANDARD 0x80000004
#define ACTION_EFFECT_GFX_LARGE    0x80000006

/* Constants used while an entity creates its child sprite. */
#define CHILD_SPRITE_WORK_SLOT_SIZE 0x4C
#define CHILD_SPRITE_GFX_ID        0x8000000A
#define CHILD_SPRITE_ANIM_STEP     0x29
#define CHILD_SPRITE_READY         0x1000

/* Animation step installed by the alternate child-sprite constructor. */
#define CHILD_SPRITE_ANIM_STEP_ALT 0x30

/* Fixed animation kind and work-slot size used by createFixedKindEntitySprite. */
#define FIXED_KIND_SPRITE_ANIM_ID 0x1E
#define FIXED_KIND_WORK_SLOT_SIZE 0x54

/* Constants for createVariantEntitySprite. */
#define VARIANT_ENTITY_WORK_SLOT_SIZE 0x54
#define VARIANT_SPRITE_GFX_ID         0x80000009
#define VARIANT_ANIM_FRAME            0x12
#define VARIANT_ANIM_FRAME_FLAG       0x01
#define VARIANT_ANIM_ENTRY_SIZE       40

/* Script-step callback table and script steps dispatched by the boss update. */
#define SCRIPT_STEP_CALLBACK_TABLE 0x08671BD0
#define BOSS_STEP_RESET   4
#define BOSS_STEP_ATTACK  6
#define BOSS_STEP_FALLBACK 3

/* Companion/boss updaters (updateCompanionBoss and its sibling): the actor's
 * +0x6C pointer leads to a work block whose +4 is the state passed to the
 * helpers. In that state +0x40 is the active flag, +0x48/+0x4C hold the
 * interaction result, +0x28 is a delay timer and +0xC4 receives the next event
 * id. The actor's +0x22 step index selects a per-step byte at +0x19. */

/* Form indices passed to the entity-form reinitializer by the boss update. */
#define BOSS_FORM_ATTACK  9
#define BOSS_FORM_SECOND  0x1E
#define BOSS_FORM_FALLBACK 0x10

/* Script steps and per-enemy parameter table used by updateScriptedEnemy. */
#define ENEMY_STEP_DEATH     0xA
#define ENEMY_STEP_FALLBACK  3
#define ENEMY_PARAM_TABLE    0x080E03A0
#define ENEMY_PARAM_ENTRY_SIZE 0x58

/* Behaviour-driven sprite spawner (spawnTrackedBehaviorSprite). The parent
 * entity's state at +0x3C carries a work block at +0x48 holding the selected
 * motion preset and the allocated motion tracker. */
#define BEHAVIOR_WORK_EXT_OFFSET    0x48        /* state -> behaviour work block */
#define BEHAVIOR_WORK_SLOT_SIZE     0x6C        /* size passed to allocWorkSlot */
#define BEHAVIOR_SPRITE_GFX_ID      0x8000000C  /* sprite typeFlags installed on success */
#define BEHAVIOR_SPRITE_READY       0x1000      /* entity flags bit set on success */
#define BEHAVIOR_WORKSPACE_COUNTER  0x18A8      /* frame counter in gMainWorkspace */
#define BEHAVIOR_SCROLL_STEP        0x40        /* scroll-row stride */
#define BEHAVIOR_SCROLL_X_OFFSET    0x1278
#define BEHAVIOR_SCROLL_Y_OFFSET    0x127C
#define BEHAVIOR_SCROLL_BIAS_X      0x8000
#define BEHAVIOR_SCROLL_BIAS_Y      0xFFFF8000
#define BEHAVIOR_FRAC_MASK          0xFFFF0000

/* Motion-tracker states and table used by updateTrackedBehaviorSprite. The
 * tracker's +1 byte is 0 while the effect is hidden and 7 while it is active;
 * +0x14 of the entity is repointed at this step-handler table each frame. */
#define TRACKER_STATE_HIDDEN    0
#define TRACKER_STATE_ACTIVE    7
#define TRACKER_ACTIVE_DISTANCE 0x00400000
#define TRACKER_STATE_HANDLERS  0x0866F96C

/* Parent/script object that spawns the kind-0x65 directional effect. */
struct Kind65EffectParent {
    u16 f0;
    u16 flags;             /* 0x02: EFFECT_SPRITE_READY set on success */
    u8 _4[0x10];
    void *scriptTable;     /* 0x14: step-handler table */
    u8 stepTimer;          /* 0x18 */
    u8 stepTime;           /* 0x19 */
    u8 _1A[8];
    s16 stepIndex;         /* 0x22 */
    void *cleanup;         /* 0x24: callback run on allocation failure */
    u8 _28[0x10];
    void *sprite;          /* 0x38 */
    void *volatile work;   /* 0x3C: work block */
    u8 _40[0xC];
    s32 direction;         /* 0x4C: selects the sprite's horizontal flip */
};

/* Work block hung off the parent's +0x3C slot. */
struct Kind65EffectWork {
    u8 _0[8];
    s32 worldX;      /* 0x08 */
    s32 worldY;      /* 0x0C */
    u8 _10[0xC];
    s16 kind;        /* 0x1C: 0x65 */
    u8 _1E[4];
    s16 animSlot;    /* 0x22: index returned by findKindIndex */
    void *cleanup;   /* 0x24 */
    struct FixedEffectSpriteLayer *layer; /* 0x28 */
    u8 _2C[0xC];
};

/* gEffectGfxTable row as seen by the kind-0x65 directional effect: the tile
 * and palette pair sits at +0x04/+0x06 (kept candidate-local elsewhere). */
struct Kind65EffectGfxEntry { u8 _0[4]; u16 gfxIndex; u16 palette; u8 _8[0x20]; };
#define BEHAVIOR_STEP_BASE_OFFSET   0x18
#define BEHAVIOR_STEP_TIME_OFFSET   0x19
#define BEHAVIOR_STEP_INDEX_OFFSET  0x22

/* Button masks read by the two-option choice menu. 1/2 are the confirm and
 * cancel buttons; 0x10/0x20 are the previous/next directions. */
#define CHOICE_MENU_CONFIRM 1
#define CHOICE_MENU_CANCEL  2
#define CHOICE_MENU_PREV    0x10
#define CHOICE_MENU_NEXT    0x20

/* Input words used by the choice menu: inputSource != 0 selects the main
 * workspace's word, otherwise the camera's word is read. */
struct ChoiceMenuCameraInput { u8 pad0[0x146C]; u16 buttons; };
struct ChoiceMenuMainInput {
    u8 pad0[0x24];
    u32 inputSource; /* 0x24 */
    u16 buttons;     /* 0x28 */
    u8 pad2A[0x1486];
    u32 choice;      /* 0x14B0: currently highlighted option */
};

/* Entity owning a simple scripted projectile: the previous handler lives at
 * +0x24, the current script step at +0x22 and the work block at +0x3C. */
struct ProjectileSpawnEntity {
    u8 _0[2];
    u16 flags;                       /* 0x02 */
    u8 _4[0x22 - 4];
    s16 stateIndex;                  /* 0x22 */
    u8 _24[0x38 - 0x24];
    u8 *sprite;                      /* 0x38 */
    struct ScriptedEffectWork *work; /* 0x3C */
    u8 _40[0x4C - 0x40];
    s16 spawnX;                      /* 0x4C */
    u8 _4E[6];
    s16 spawnY;                      /* 0x54 */
    u8 _56[0x5C - 0x56];
    u32 radius;                      /* 0x5C */
    u8 _60[0x6C - 0x60];
    u32 data;                        /* 0x6C */
};

/* Constants for the scripted-attack sprite constructor (initScriptedAttackSprite). */
#define SCRIPTED_ATTACK_ANIM_ID        0x20        /* animation/kind index given to findKindIndex */
#define SCRIPTED_ATTACK_WORK_SLOT_SIZE 0x48        /* size passed to allocWorkSlot */
#define SCRIPTED_ATTACK_GFX_ID         0x8000000A  /* graphics id installed at sprite+0x1C */
#define SCRIPTED_ATTACK_ANIM_STEP      0x31        /* animation step written to sprite+0x28 */
#define SCRIPTED_ATTACK_READY          0x1000      /* bit set on the entity's flags on success */

/* Affine/OAM parameter words (u16[4]) shared by the scripted sprite constructors.
 * Copied into a render layer's tile0..tile3 fields. */
extern u16 gScriptedSpriteAffineParams[];

/* Constants for the animated entity-effect spawner (spawnAnimatedEntityEffect). */
#define ANIMATED_EFFECT_WORK_SLOT_SIZE 0x48   /* size passed to allocWorkSlot */
#define ANIMATED_EFFECT_ANIM_STEP      0x2C   /* animation step written to sprite+0x28 */

/* Affine/OAM parameter words (u16[4]) copied into the animated effect's layer. */
extern u16 gAnimatedEffectAffineParams[];

/* Starting animation frame passed to setAnimationFrame by spawnAnimatedFixedEffect. */
#define FIXED_EFFECT_ANIM_FRAME 0x1A

/* Kind and extra flag bits used by the two-layer effect spawner. */
#define TWO_LAYER_EFFECT_KIND     0x64
#define TWO_LAYER_EFFECT_FLAG_B   0x800   /* second flag set on the owner on success */

/* Work-slot size and starting animation frame for spawnObjectKindEffect. */
#define OBJECT_KIND_EFFECT_WORK_SLOT 0x48
#define OBJECT_KIND_EFFECT_ANIM_FRAME 0xE

/* Work-slot size and starting animation frame of the fixed kind-0x4F effect. */
#define KIND4F_EFFECT_WORK_SLOT 0x78
#define KIND4F_EFFECT_ANIM_FRAME 5

/* Kind, work slot, graphics id and starting frame of the kind-0x51 effect. */
#define SPRITE_KIND_51_EFFECT     0x51
#define KIND51_EFFECT_WORK_SLOT   0x48
#define KIND51_EFFECT_GFX_ID      0x80000009
#define KIND51_EFFECT_ANIM_FRAME  0xD

/* Fixed descriptor fields of the effect spawned from an entity's +0x4C params.
 * The parameter's low nibble selects a frame and the special variant uses an
 * alternate extension layout. */
#define PARAM_EFFECT_WORK_SLOT    0x54
#define PARAM_EFFECT_TYPE         4
#define PARAM_EFFECT_LAYER        0x80
#define PARAM_EFFECT_ANIM3        0xFFFA
#define PARAM_EFFECT_GFX_ID       0x80000007
#define PARAM_EFFECT_VARIANT_MASK 0xF
#define PARAM_EFFECT_SPECIAL      5
#define PARAM_EFFECT_FLAG_A       (0x80 << 10)
#define PARAM_EFFECT_FLAG_B       (0x80 << 7)
#define PARAM_EFFECT_ATTR         0x96
#define PARAM_EFFECT_EXT_ID       0x16C1

/* Work slot, graphics id and starting animation frame of the kind-0x55 effect. */
#define KIND55_EFFECT_WORK_SLOT   0x48
#define KIND55_EFFECT_GFX_ID      0x80000009
#define KIND55_EFFECT_ANIM_FRAME  0x24

/* Work slot, graphics id and starting animation frame of the kind-0x87 effect. */
#define KIND87_EFFECT_WORK_SLOT   0x48
#define KIND87_EFFECT_GFX_ID      0x80000009
#define KIND87_EFFECT_ANIM_FRAME  0x24

/* Attack-effect sprite constructor (spawnAttackEffectSprite). */
#define ATTACK_SPRITE_KIND       20      /* animation/effect kind installed in the work slot */
#define ATTACK_SPRITE_WORK_SLOT  0x50    /* size passed to allocWorkSlot */
#define ATTACK_SPRITE_ANIM_FRAME 0x19    /* starting animation frame */
extern u16 gAttackSpriteAffineParams[]; /* four u16s copied into the effect part */

/* Per-variant parameters consumed by updateTrackedBehaviorStep. All three
 * symbols are overlapping views of the table at 0x08102B62, indexed by the
 * variant byte at (state+0x48)+0x20:
 *   gBehaviorAnimKinds - s16 animation kind passed to setObjectAnimation
 *   gBehaviorSpeeds    - u32 movement speed, negated for an X-flipped sprite
 *   gBehaviorRanges    - u32 distance threshold for the step transition
 */
extern s16 gBehaviorAnimKinds[];
extern u32 gBehaviorSpeeds[];
extern u32 gBehaviorRanges[];

/* Work block reached at (entity work state)+0x48 for the tracked behaviour. */
/* Motion tracker allocated by allocMotionTracker and hung off the tracked
 * behaviour's work block at +0x04. The pointer is volatile: every field write
 * below re-reads it from memory. */
struct MotionTracker {
    u8 _0;            /* 0x00 */
    u8 state;         /* 0x01: TRACKER_STATE_HIDDEN / TRACKER_STATE_ACTIVE */
    u16 previous;     /* 0x02: low half of the prior tracker handle */
    u16 animX;        /* 0x04: integer part of the motion's world X */
    u16 animY;        /* 0x06: integer part of the motion's world Y, plus one */
    u16 kind;         /* 0x08: 0x10 */
    u16 layer;        /* 0x0A: 0x10 */
    void *owner;      /* 0x0C: entity that owns the tracker */
};

struct TrackedBehaviorWork {
    u8 _0[4];
    struct MotionTracker *volatile tracker; /* 0x04 */
    u8 _8[0x14];
    u32 stateCount; /* 0x18: bumped on every timer wrap */
    u16 timer;      /* 0x1C: countdown; wrap switches to the next step */
    u8 _1E[2];
    u8 variant;     /* 0x20: index into the per-variant tables above */
};

/* Sprite OAM attribute 1 bit 0x10 mirrors the behaviour's X motion. */
#define BEHAVIOR_SPEED_PARAM 0x4000   /* argument to the movement integrator */
#define BEHAVIOR_FAR_X       0x400000 /* absolute-X cutoff that resets the variant */
#define BEHAVIOR_FOCUS_RANGE 0x180000 /* radius passed to the focus-distance test */
#define BEHAVIOR_STEP_RESET  4
#define BEHAVIOR_STEP_ALT    5

/* Script-driven object update family (updateScriptedObject and its siblings).
 * Object fields: +0x02 flags (bit 0x8000 skips animation and repositioning),
 * +0x14 script-command handler table, +0x18 stream of 2-byte steps (opcode
 * byte, timer byte), +0x22 current step index (s16), +0x24 cleanup callback,
 * +0x38 sprite, +0x3C work state.
 * Work state: +0x00 hit flags (bit 0 = hit), +0x02 extra flags, +0x08/+0x0C
 * fixed-point world X/Y, +0x28 collision target, +0x34 animation track,
 * +0x48 per-step state word (0 normal, 1 special).
 * Collision target: +0x01 transient hit flags (bits 0 and 2), +0x14 status. */
#define SCRIPT_OBJ_FLAG_SKIP_ANIM 0x8000
#define SCRIPT_OBJ_HIT_FLAG       1
#define SCRIPT_TARGET_HIT_CLEAR   0xFB
#define SCRIPT_STEP_TABLE_OFFSET  0x14
#define SCRIPT_STEP_BASE_OFFSET   0x18
#define SCRIPT_STEP_INDEX_OFFSET  0x22
#define SCRIPT_OBJECT_DEATH_SFX   0x18A

/* Angle-driven scripted object (updateScriptedAngleObject). Its +0x3C work
 * state holds the animation track at +0x34 and a per-step block at +0x48:
 * +0x00 fixed-point X, +0x14 status, +0x1C countdown, +0x20 cached trig
 * result, +0x24 angle index. Step handlers live in gAngleObjectStepTable. */
#define ANGLE_OBJECT_FAR_LIMIT   0x1000000  /* |step X| past this picks the far event */
#define ANGLE_OBJECT_NEAR_LIMIT  0x7FFFFF   /* |work X| under this allows the chance roll */
#define ANGLE_OBJECT_CHANCE      0x1388     /* threshold passed to rollProbability */

/* The alternate angle-object updater (updateScriptedAngleObjectAlt) shares the
 * work-state layout above but dispatches through its own step table. */
extern u32 gAngleObjectAltStepTable[];

/* Angle index -> trig-table divisor, and the countdown reload range. */
#define ANGLE_TRIG_INDEX_DIVISOR 0x3C
#define ANGLE_TIMER_RANDOM_SPAN  0x3D
#define ANGLE_TIMER_RELOAD_BASE  0x3C


/* Scripted-attack sibling: its own step-handler table and death sound. */
#define SCRIPT_ATTACK_STEP_TABLE  0x0866DC30
#define SCRIPT_ATTACK_DEATH_SFX   0x189

/* Step handler table and motion gravity of the timed scripted-attack object. */
#define SCRIPT_TIMED_ATTACK_STEP_TABLE 0x0866E324
#define SCRIPT_TIMED_ATTACK_GRAVITY    0x16C1
/* gObjectScriptStepTable: Thumb handler pointers indexed by the step opcode. */
extern void *gObjectScriptStepTable[];

/* Fourth spawn-sprite script command (scriptCmdSpawnSprite4). The script
 * reference type selects one of two sprite kinds; the render part's four
 * default attributes come from gSpriteDefaultAttrs4, and the initial patrol
 * target is jittered by randomizePatrolTarget. */
#define SCRIPT_CMD4_REF_A   0xB3
#define SCRIPT_CMD4_REF_B   0xB4
#define SCRIPT_CMD4_KIND_A  0x56
#define SCRIPT_CMD4_KIND_B  0x6F
extern u16 gSpriteDefaultAttrs4[];

/* Entity sprite constructor (initEntitySpriteGraphics): the entity's kind word
 * selects one of two start frames; gEntitySpriteAnimTable supplies animation
 * data and the allocated render layer uses graphics id 0x8000000E. */
#define ENTITY_SPRITE_KIND_MASK  0x3FFF
#define ENTITY_SPRITE_KIND_A     0x1DE
#define ENTITY_SPRITE_KIND_B     0x1DF
#define ENTITY_SPRITE_ANIM_A     0x42
#define ENTITY_SPRITE_ANIM_B     0x46
#define ENTITY_SPRITE_GFX_ID     0x8000000E
#define ENTITY_SPRITE_WORK_SLOT  0x24
#define ENTITY_SPRITE_READY      0x1000
extern u8 gEntitySpriteAnimTable[];

/* Script-step and event callback tables used by the moving/scripted-entity
 * update path (updateScriptedProjectile). */
#define MOVING_ENTITY_STEP_TABLE    0x0866D9BC
#define SCRIPT_EVENT_CALLBACK_TABLE 0x08671BDC

#define ANGLE_EFFECT_KIND        0x5F      /* sprite kind written to state+0x1C */
#define ANGLE_EFFECT_POS_SCALE   0x600     /* world-offset scale applied to the trig result */
#define ANGLE_EFFECT_WORK_SLOT   0x48      /* size passed to allocWorkSlot */

/* Pose-animation step (updatePoseStep): animation id base, the frame at which
 * the result entity is spawned, the workspace kind word and the spawned kind. */
#define POSE_ANIM_BASE         0x27
#define POSE_FINAL_STEP        8
#define POSE_WORKSPACE_KIND    0x1870
#define POSE_RESULT_KIND       0xE9

/* Pause-menu status/item panel. Its state block starts at gMenuState and is
 * indexed with the offsets below; the panel is one of several screens that
 * share this work buffer. */
#define MENU_REDRAW_FLAG      0x69  /* toggled 0/1 whenever the category changes */
#define MENU_CATEGORY         0x6A  /* selected category, s8, wraps over 0..MENU_CATEGORY_MAX */
#define MENU_CATEGORY_MAX     3
#define MENU_ITEM_INDEX_BASE  0x6B  /* first item index of each category */
#define MENU_SUB_OBJECT       0x48  /* spawned item-preview object pointer */
#define MENU_ICON_TABLE       0x73  /* item icon ids, indexed by the item offset */
#define MENU_ENABLED_TABLE    0xF3  /* one enabled byte per category */
#define MENU_STATE_COPY_SIZE  0x48  /* player-state bytes snapshotted into the panel */
#define MENU_CANCEL_STATE     0x64  /* cleared when the panel is closed with B */

/* Button bits in the input words at gCameraState+0x1470 (held, with repeat)
 * and gCameraState+0x146C (pressed this frame). */
#define MENU_INPUT_PREV       0x40
#define MENU_INPUT_NEXT       0x80
#define MENU_INPUT_CANCEL     0x02
#define MENU_INPUT_CONFIRM    0x01
#define MENU_INPUT_DIR_BOTH   0xC0

/* Scripted-menu input handler: sounds and the script commands it dispatches. */
#define SCRIPT_MENU_MOVE_SFX     0x153
#define SCRIPT_MENU_CANCEL_SFX   0x159
#define SCRIPT_MENU_CONFIRM_SFX  0x155
#define SCRIPT_MENU_CANCEL_CMD   0x11
#define SCRIPT_MENU_CONFIRM_CMD  0x10

/* Sound effects played by the panel update. */
#define SFX_MENU_MOVE         (0xA7 << 1)
#define SFX_MENU_CANCEL       0x14F
#define SFX_MENU_CONFIRM      0x13B

/* Spawn kind and initial animation step of the item-preview object. */
#define MENU_SUB_OBJECT_KIND  0x1B
#define MENU_SUB_OBJECT_STEP  2

/* Script-thread fields used by the scripted angle-effect spawner. */
#define SCRIPT_ANGLE_SPRITE_PTR   0x38  /* spawned sprite written back to the script thread */
#define SCRIPT_ANGLE_WORK_PTR     0x3C  /* 0x48-byte work state allocated here */
#define SCRIPT_ANGLE_POS_X        0x4C
#define SCRIPT_ANGLE_POS_Y        0x5C
#define SCRIPT_ANGLE_VALUE        0x6C  /* angle fed to the trig lookup */
#define SCRIPT_ANGLE_ANIM_PARAM   0x7C
#define SCRIPT_ANGLE_SCALE_FLAG   0x90  /* when set, halve the layer's palette delta */
#define SCRIPT_ANGLE_CLEANUP_CB   0x24  /* handler called on any allocation failure */
#define ANGLE_SCRIPT_ATTR_FLAG    0x400  /* sprite attribute bit set on the spawned sprite */
#define ANGLE_SCRIPT_ANGLE_BIAS   0x4000 /* added to the angle before the trig lookup */

/* Work state of the scripted angle-driven effect (0x48 bytes at script+0x3C). */
struct ScriptedAngleEffectWork {
    u8 _0[8];
    u32 x;             /* 0x08 */
    u32 y;             /* 0x0C */
    u32 adjustedX;     /* 0x10: cosine-scaled position */
    u32 adjustedY;     /* 0x14: sine-scaled position */
    u8 _18[4];
    u16 kind;          /* 0x1C: ANGLE_EFFECT_KIND */
    u8 _1E[4];
    u16 gfxIndex;      /* 0x22: index returned by findKindIndex */
    u8 _24[4];
    struct ScriptedAngleLayer *layer; /* 0x28 */
};

/* Render layer allocated by allocEffectPart for the scripted angle effect. */
struct ScriptedAngleLayer {
    u8 _0, mode, layer, priority;    /* 0x00..0x03 */
    u16 gfxA;                        /* 0x04 */
    u16 affine0, affine1, affine2, affine3; /* 0x06..0x0C */
    s16 palette;                     /* 0x0E */
    u32 sprite;                      /* 0x10 */
};

/* gEffectGfxTable entry as viewed by the scripted angle spawner. */
struct ScriptedAngleGfxEntry { u8 _0[8]; u16 gfxA; u16 palette; u8 _C[0x1C]; };

/* Field views used by updateBoundedScriptedAttack (and its sibling scripted
 * attack updates): a collision target's transient hit byte, the sprite
 * attribute byte controlling visibility, and the work state's hit flag word. */
struct AttackTargetState {
    u8 status;     /* 0x00: target status word low byte */
    u8 hitState;   /* 0x01: transient hit flags (cleared on a new attack) */
};

struct AttackSpriteFlags {
    u8 flag;       /* 0x2A: bit 0x40 hides the sprite, bit 0x10 cleared when visible */
};

struct AttackHitFlags {
    u16 flag;      /* 0x00 of the attack work state: bit 0 means a hit landed */
};

/* Sprite visibility flag at AttackSpriteFlags+0, and the mask that clears it. */
#define ATTACK_SPRITE_HIDE_FLAG 0x40
#define ATTACK_SPRITE_SHOW_MASK 0xBF

/* States written to AttackTargetState.hitState by a bounded attack. */
#define ATTACK_TARGET_CLEAR  0
#define ATTACK_TARGET_PENDING 4

/* Tile-map collision walkers (traceTilemapCollision / resolveTilemapCollision).
 * Positions are 16.16 fixed point; a map page is 0x40 bytes, the low 16 bits
 * select a tile within the page, and a blocked tile reports the tile centre.
 * gTileTerrainFlags stores one u16 collision mask per terrain code at code*2. */
#define TILEMAP_PAGE_STRIDE      0x40
#define TILE_CENTER_BIAS         0x8000
#define FIXED_POINT_FRAC_MASK    0xFFFF0000

/* Result written by resolveTilemapCollision: resolved 16.16 X/Y and hit flags. */
struct TilemapCollision {
    u16 flags;   /* OR of TILEMAP_HIT_X / TILEMAP_HIT_Y */
    u16 pad;
    s32 x;
    s32 y;
};
#define TILEMAP_HIT_X        1        /* blocked along the movement axis */
#define TILEMAP_HIT_Y        2        /* blocked along the vertical probe */
#define TILEMAP_TILE_MASK    0xFFF80000  /* keep only the whole-tile X bits */
#define TILEMAP_CENTER_DOWN  0xFFFF8000  /* snap X back one tile */
#define TILEMAP_CENTER_UP    0x88000     /* snap X forward one tile */

/* Tables used by updateTargetedScriptedAttack. gAttackTargetKinds is a
 * zero-terminated s16 list of entity kinds accepted as a hit target; the
 * attack's step handlers live in gTargetedAttackStepTable (4-byte pointers). */
extern s16 gAttackTargetKinds[];
extern u8 gTargetedAttackStepTable[];

/* DSS card-combination menu (updateCardCombinationMenu). gMenuState is a shared
 * work buffer; this screen uses the fields below. Cards hold values 1..10. */
#define CARD_MENU_SLOT_A        0x40  /* card value in slot A */
#define CARD_MENU_SLOT_B        0x41  /* card value in slot B */
#define CARD_MENU_ACTIVE_SLOT   0xF8  /* 0 = slot B active, 1 = slot A active */
#define CARD_MENU_CLOSED_FLAG   0x64  /* cleared when the menu is closed */
#define CARD_MENU_CARD_MIN      1
#define CARD_MENU_CARD_MAX      10
#define CARD_MENU_STATE_ID      0x0E  /* state dispatched on close */

/* Held-input bits (gCameraState+0x1470) used by the card menu. */
#define CARD_INPUT_CARD_UP      0x20
#define CARD_INPUT_CARD_DOWN    0x10
#define CARD_INPUT_DIR_BOTH     0x30
#define CARD_INPUT_SLOT_A       0x40
#define CARD_INPUT_SLOT_B       0x80
#define CARD_INPUT_SLOT_BOTH    0xC0

/* Pressed-this-frame bits (gCameraState+0x146C): A/B close the menu. */
#define CARD_INPUT_CLOSE_MASK   3

/* Sound effects (sub_08005E80) played by the card menu. */
#define CARD_MENU_SFX_CHANGE    0x139
#define CARD_MENU_SFX_SLOT      0x140
#define CARD_MENU_SFX_CLOSE     0x14F

/* Randomized-offset attack spawned by spawnRandomOffsetAttack: the work state
 * at owner+0x3C holds the attack kind and the chosen animation slot. */
#define RAND_ATTACK_KIND       0x24   /* s16 kind stored at work+0x1C */
#define RAND_ATTACK_WORK_SIZE  0x48   /* bytes allocated for the work state */
#define RAND_ATTACK_ATTR_BASE  0x200  /* base OAM attribute word written to sprite+0x00 */
#define RAND_ATTACK_FRAME_BIAS 8      /* added to the animation slot for the frame id */

/* Owner fields read as the random-offset parameters passed to sub_0803C70C. */
#define RAND_ATTACK_X_DIR_MODE  0x98  /* s8 direction multiplier */
#define RAND_ATTACK_X_MODE      0x90  /* u8 X distribution mode */
#define RAND_ATTACK_Y_MODE      0x94  /* u8 Y distribution mode */
#define RAND_ATTACK_X_RANGE     0x6C  /* s32 fixed-point X range */
#define RAND_ATTACK_Y_RANGE     0x7C  /* s32 fixed-point Y range */

/* Timed actor/enemy AI update (updateActorAiWithTimer). Its work state hangs
 * off the actor's +0x6C pointer; the +0x3C field is a position reference. */
struct TimedAiActor {
    u8 _0[0x18];
    u8 kind;        /* 0x18 */
    u8 _19[9];
    s16 animIndex;  /* 0x22: current script-step index */
    u8 _24[0x14];
    u32 refPtr;     /* 0x38: position/target reference */
    u8 _3C[0x30];
    u32 aiPtr;      /* 0x6C: AI work state minus 4 */
};

struct TimedAiWork {
    u8 _0[0xD0];
    u16 fD0;        /* 0xD0 */
    u16 fD2;        /* 0xD2 */
};

struct TimedAiState {
    u8 _0[8];
    u32 f08;        /* 0x08 */
    u32 timer;      /* 0x0C: advanced from ENEMY_PARAM_TABLE */
    u8 _10[0x1A];
    u16 f2A;        /* 0x2A */
    u16 mode;       /* 0x2C */
    u8 _2E[0x12];
    u32 idleTimer;  /* 0x40 */
    u32 tableIndex; /* 0x44: row index into ENEMY_PARAM_TABLE */
    u8 _48[4];
    u32 flag4C;     /* 0x4C */
    u32 flag50;     /* 0x50 */
    u8 _54[0x64];
    u32 flagB8;     /* 0xB8 */
    u8 _BC[8];
    u32 aiResult;   /* 0xC4: script step to dispatch */
};

/* Dash afterimage effect (spawnDashAfterimageEffect). */
#define DASH_AFTERIMAGE_SFX       0x8F
#define DASH_AFTERIMAGE_TIMER     0x7B
#define DASH_AFTERIMAGE_SCALE_A   0x2D  /* percentage used for character 1 */
#define DASH_AFTERIMAGE_SCALE_B   0x20  /* percentage for other characters */
#define DASH_AFTERIMAGE_VEL_LEFT  0xFFF80000  /* fixed-point -8.0 */
#define DASH_AFTERIMAGE_VEL_RIGHT 0x00080000  /* fixed-point +8.0 */
#define DASH_AFTERIMAGE_ANIM_SEQ  0x084733C4  /* animation sequence installed at sprite+0x24 */
#define DASH_AFTERIMAGE_GFX_ID    0x80000006  /* graphics id installed at sprite+0x1C */

/* Clearing the horizontal-flip bit (SPRITE_OAM_FLIP_X) of sprite attribute 1. */
#define SPRITE_OAM_FLIP_X_CLEAR 0xFFEF

/* Standard GBA button bits in the input words at gCameraState+0x146C (pressed
 * this frame) and gMainWorkspace+0x2A (held). */
#define BUTTON_A       0x001
#define BUTTON_RIGHT   0x010
#define BUTTON_LEFT    0x020
#define BUTTON_UP      0x040
#define BUTTON_DOWN    0x080
#define BUTTON_R       0x100
#define BUTTON_L       0x200

/* Form-preview controller: fixed-point move step, highest form index and the
 * screen-centre coordinates written to the preview sprite. */
#define FORM_PREVIEW_MOVE_STEP 0x20000
#define FORM_PREVIEW_MAX_FORM  0x34
#define FORM_PREVIEW_CENTER_X  (0xF0 << 15)
#define FORM_PREVIEW_CENTER_Y  (0xC8 << 15)

/* Kind-0x68 effect spawner (50 render parts): shared layouts and tables. */

/* One render part allocated by allocEffectPart for each of the 50 slots. */
struct Kind68EffectPart {
    u8 _0;
    u8 active;     /* 0x01: 0 while spawning */
    u8 layer;      /* 0x02: 8 */
    u8 priority;   /* 0x03: 1 */
    u16 gfxIndex;  /* 0x04: tile id from gEffectGfxTable */
    u16 affine0;   /* 0x06 */
    u16 affine1;   /* 0x08 */
    u16 affine2;   /* 0x0A */
    u16 affine3;   /* 0x0C */
    u16 palette;   /* 0x0E: palette id from gEffectGfxTable */
    u32 sprite;    /* 0x10: owner sprite */
};

/* Four u16 affine/OAM words copied into each of the 50 render parts. */
extern u16 gKind68EffectAffineParams[];

/* Kind-0x59 script effect (spawnKind59ScriptEffect and its variant): the actor
 * owns a sprite plus a 0x48-byte work block, whose +0x28 pointer is one render
 * layer allocated by allocEffectPart. */
#define KIND59_EFFECT_KIND       0x59        /* kind / animation index */
#define KIND59_EFFECT_GFX_ID     0x80000009
#define KIND59_EFFECT_WORK_SIZE  0x48
#define KIND59_EFFECT_ANIM_TABLE 0x080CD400
#define KIND59_EFFECT_ANIM_FRAME 0x1E
#define KIND59_EFFECT_READY      0x1000       /* actor flags bit set on success */

/* Render layer allocated by allocEffectPart for the kind-0x59 script effect. */
struct Kind59EffectLayer {
    u8 _0;        /* 0x00: unused */
    u8 active;    /* 0x01: 0 while spawning */
    u8 layer;     /* 0x02: 8 */
    u8 priority;  /* 0x03: 1 */
    u16 gfxIndex; /* 0x04: tile id from gEffectGfxTable */
    u16 anim0;    /* 0x06 */
    u16 anim1;    /* 0x08 */
    u16 anim2;    /* 0x0A */
    u16 anim3;    /* 0x0C */
    u16 palette;  /* 0x0E: palette id from gEffectGfxTable */
    u32 sprite;   /* 0x10: owner sprite */
};

/* Per-kind graphics entry: tile id at +0x08, palette at +0x0A. */
struct Kind59GfxEntry {
    u8 _0[4];
    u16 f4;
    u16 f6;
    u16 gfxIndex; /* 0x08 */
    u16 palette;  /* 0x0A */
    u8 _C[0x1C];
};

/* Work block held in the actor's +0x3C slot. */
struct Kind59EffectWork {
    u8 _0[8];
    s32 x;        /* 0x08: world X */
    s32 y;        /* 0x0C: world Y */
    u32 f10;
    u32 f14;
    u8 _18[4];
    s16 kind;     /* 0x1C: KIND59_EFFECT_KIND */
    u8 _1E[4];
    s16 animSlot; /* 0x22: index returned by findKindIndex */
    u8 _24[4];
    struct Kind59EffectLayer *layer; /* 0x28 */
    u8 _2C[8];
};

/* Actor owning the kind-0x59 script effect. */
struct Kind59EffectActor {
    u16 f0;
    u16 flags;        /* 0x02: KIND59_EFFECT_READY */
    u8 _4[0x14 - 4];
    void *scriptTable; /* 0x14: script command handler table */
    u8 _18[0xA];
    s16 step;         /* 0x22: current script-step index */
    void *cleanup;    /* 0x24: cleanup callback */
    u8 _28[0x38 - 0x28];
    void *sprite;     /* 0x38 */
    void * volatile work; /* 0x3C */
    u8 _40[0xC];
    u32 spawnX;       /* 0x4C */
    u8 _50[0xC];
    u32 spawnY;       /* 0x5C */
};

/* Arcing trail attack: state block at work+0x48, holding one spawned object
 * pointer per trail point. */
struct ArcTrailState {
    s32 angle;         /* 0x00: sine-derived horizontal offset */
    u16 angleStep;     /* 0x04: sine-table index */
    u16 timer;         /* 0x06 */
    u16 spawnTimer;    /* 0x08: frames until the next trail point */
    u8 _0A[4];
    u16 count;         /* 0x0E: trail points still to spawn */
    s16 phase;         /* 0x10: 0 = start-up, 1 = looping */
    s32 centerX;       /* 0x14 */
    s32 centerY;       /* 0x18 */
    u8 _1C[8];
    s16 direction;     /* 0x24: +1 / -1 facing */
    u8 _26[2];
    void *points[10];  /* 0x28: dust objects spawned along the trail */
};

#define ARC_TRAIL_ANGLE_DIVISOR 0x24       /* angle-step divisor for the sine lookup */
#define ARC_TRAIL_MAX_POINTS    0xA        /* index bound of points[] */
#define ARC_TRAIL_DUST_KIND     0xA2       /* kind of the spawned trail dust */
#define SPAWN_KIND_OFFSET       0x1870     /* word in gMainWorkspace used as spawn parent/kind */

/* Kind-0x66 scripted effect (spawnKind66ScriptEffect). The script thread owns
 * a sprite at +0x38 and a 0x48-byte work block at +0x3C. gEffectGfxTable
 * records are 0x28 bytes; the tile/palette pair used by this kind sits at
 * +0x10/+0x12. */
#define KIND66_EFFECT_KIND       0x66
#define KIND66_EFFECT_GFX_ID     0x80000009
#define KIND66_EFFECT_WORK_SIZE  0x48
#define KIND66_EFFECT_READY      0x1000
#define KIND66_EFFECT_LAYER_KIND 5
#define KIND66_EFFECT_LAYER_NUM  8
#define KIND66_EFFECT_LAYER_PRI  1
#define KIND66_EFFECT_SCALE      (0xC0 << 10)
#define KIND66_EFFECT_ANIM_TABLE 0x080CD400

/* Kind-0x68 scripted effect (spawnKind68ScriptEffect): like the other
 * spawnKindXX constructors, but flips the sprite and scales its motion from a
 * signed script parameter jittered by a random factor. The gEffectGfxTable
 * record's tile/palette pair for this kind is at +0x08/+0x0A. */
#define KIND68_EFFECT_KIND       0x68
#define KIND68_EFFECT_GFX_ID     0x80000009
#define KIND68_EFFECT_WORK_SIZE  0x48
#define KIND68_EFFECT_READY      0x1000
#define KIND68_EFFECT_LAYER_KIND 5
#define KIND68_EFFECT_LAYER_NUM  8
#define KIND68_EFFECT_LAYER_PRI  1
#define KIND68_SCALE_JITTER      0x8000  /* random offset range */
#define KIND68_SCALE_BASE        0x40000 /* centres the scale near 1.0 */

/* Alternate kind-0x68 script effect (spawnKind68ScriptEffectAlt): same kind,
 * graphics id and ready flag as the primary variant, but a 0x5C work block,
 * the +0x10/+0x12 graphics pair, and no random scale. */
#define KIND68_ALT_WORK_SIZE 0x5C

/* Projected kind-0x68 script effect: actor +0x3C work state and +0x38 sprite.
 * The constructor randomizes +0x6C/+0x7C/+0x8C, then sub_080BC73C projects
 * the work state's motion into world coordinates. */
struct ProjectedKind68Layer {
    u8 mode;         /* 0x00 */
    u8 kind;         /* 0x01 */
    u8 layer;        /* 0x02 */
    u8 priority;     /* 0x03 */
    u16 gfxIndex;    /* 0x04 */
    u16 anim0;       /* 0x06 */
    u16 anim1;       /* 0x08 */
    u16 anim2;       /* 0x0A */
    u16 anim3;       /* 0x0C */
    s16 palette;     /* 0x0E */
    u32 sprite;      /* 0x10 */
};

struct ProjectedKind68Work {
    u8 _0[8];
    u32 f8;
    u32 fC;
    u32 f10;
    u32 f14;
    u8 _18[4];
    s16 kind;        /* 0x1C: 0x68 */
    u8 _1E[4];
    s16 animSlot;    /* 0x22 */
    u8 _24[4];
    struct ProjectedKind68Layer *layer; /* 0x28 */
};

struct ProjectedKind68Actor {
    u16 f0;
    u16 flags;       /* 0x02 */
    u8 _4[0x14 - 4];
    void *scriptTable; /* 0x14 */
    u8 _18[0x22 - 0x18];
    s16 step;        /* 0x22 */
    void *cleanup;   /* 0x24 */
    u8 _28[0x38 - 0x28];
    void *sprite;    /* 0x38 */
    void * volatile work; /* 0x3C */
    u8 _40[0x5C - 0x40];
    u32 f5C;
    u8 _60[0x6C - 0x60];
    s32 f6C;
    u8 _70[0x7C - 0x70];
    u32 f7C;
    u8 _80[0x8C - 0x80];
    s32 f8C;
};

struct ProjectedKind68GfxEntry {
    u8 _0[4];
    u16 gfxIndex;    /* 0x04 */
    u16 palette;     /* 0x06 */
    u8 _8[0x28 - 8];
};

/* Project actor motion using its sprite animation state and work output. */
extern void sub_080BC73C(void *, void *, void *);

/* Directional multi-part projectile, updated by updateDirectionalMultiPartProjectile
 * (whose graphics are built by initScriptedMultiPartGraphics).
 * Entity: +0x02 flags (0x8000 skips animation/motion), +0x14 active step-handler
 * table, +0x18 script stream (per-step timer at +1A, event byte at +1B), +0x22
 * step index, +0x24 cleanup callback, +0x38 sprite, +0x3C work state, +0x6C
 * direction flags (bit 1 re-aims the child layers).
 * Work state: +0x00 hit flag (bit 0), +0x08/+0x0C fixed-point world X/Y,
 * +0x10 X velocity, +0x14 Y velocity (random kick), +0x28 first render part,
 * +0x34 animation track, +0x48 part block (its s16 word at +0: 1 = special, its
 * s32 at +4: fall speed 0x16C1, its pointers at +0x34/+0x38: the other parts).
 * Render parts carry their active flag in byte +1; a hit clears all three and
 * dispatches event callback index 2 from gScriptEventCallbacks. */
extern u32 sMultiPartProjectileStepTable[];
#define MULTI_PART_PROJ_DIR_FLAG 2  /* entity+0x6C bit: re-aim child layers from direction */

/* Kind-0x15 scripted sprite built by spawnKind15ScriptSprite. The caller's +0xAC
 * holds the spawn parameters; the allocated work state at the entity's +0x3C has
 * its kind at +0x1C, animation track at +0x34 and three sub-object pointers at +0x54.
 * The sprite gets a config part at work+0x28 and three render sub-objects. */
#define KIND15_SPRITE_KIND       0x15
#define KIND15_WORK_SLOT         0x64
#define KIND15_SPRITE_GFX_ID     0x8000000A
#define KIND15_ANIM_STRIDE       12
#define KIND15_INIT_VALUE        8
#define KIND15_SPAWN_EFFECT      0xE1
#define KIND15_SPRITE_READY      0x1000

/* Work state of a moving actor, reached through actor->extra + 4. */
struct MovingActorState {
    u8 _0[8];
    s32 f8;             /* 0x08: cleared on the death transition */
    s32 speed;          /* 0x0C: advanced from the per-type timing table */
    u8 _10[0x40 - 0x10];
    s32 state;          /* 0x40: 1 starts the death transition */
    s32 type;           /* 0x44: row index into ENEMY_PARAM_TABLE */
    u8 _48[4];
    s32 f4C;            /* 0x4C */
    s32 f50;            /* 0x50 */
    s32 f54;            /* 0x54 */
};

/* Fields of the shared workspace read by updateMovingActor. */
struct ActorUpdateWorkspace {
    u8 _0[0x14ED];
    u8 mode;              /* 0x14ED: 0x35 starts a new round */
    u8 _14EE[0x1754 - 0x14EE];
    s32 smallSlotCounter; /* 0x1754: forced to 9 on the transition */
};

/* Script step dispatched by updateMovingActor on the death transition. */
#define ACTOR_STEP_DEATH 0x10

/* Kind-0x44 effect spawner (spawnKind44Effect): gEffectGfxTable record viewed as
 * a tile-id/palette-id pair at +8 and +0xA. */
struct Kind44GfxEntry { u8 _0[8]; u16 gfxIndex; u16 palette; u8 _c[0x1C]; };

/* Entity driven by updateEntityMotionAndSpawn. It keeps a sprite descriptor at
 * +0x38 and a motion mover at +0x3C; the mover's world X/Y/facing live at
 * +0x08/+0x0C/+0x10 and its animation track begins at +0x34. The sprite's
 * animation frame sits at +0x08 and its camera-relative screen X/Y are written
 * back to +0x14/+0x18. */
struct MotionEntity {
    u8 _00[0x38];
    struct MotionEntitySprite *sprite; /* 0x38 */
    struct MotionEntityMover *mover;   /* 0x3C */
    u8 _40[0x0C];
    u32 worldX;      /* 0x4C */
    u8 _50[0x0C];
    u32 worldY;      /* 0x5C */
    u8 _60[0x0C];
    u32 facing;      /* 0x6C */
    u8 _70[0x0C];
    u16 pose;        /* 0x7C */
    u8 _7E[6];
    s8 wantedPose;   /* 0x84 */
    u8 _85[3];
    s8 shownPose;    /* 0x88 */
    u8 _89[3];
    u8 spawnRequest; /* 0x8C */
};

struct MotionEntitySprite {
    u8 _00[0x02];
    u16 flags;       /* 0x02: ORIGIN_FLIP_X mirrors spawned children */
    u8 _04[0x04];
    u16 pose;        /* 0x08 */
    u8 _0A[0x0A];
    u32 screenX;     /* 0x14 */
    u32 screenY;     /* 0x18 */
};

struct MotionEntityMover {
    u8 _00[0x08];
    u32 x;           /* 0x08 */
    u32 y;           /* 0x0C */
    u32 facing;      /* 0x10 */
    u8 _14[0x14];
    u32 linkData;    /* 0x28 */
    u8 _2C[0x08];
};

struct MotionEntityWorkspace {
    u8 _0[0x18A8];
    u8 frame;        /* 0x18A8: video-frame counter */
};

/* One (dx,dy) child-spawn offset; gSpawnOffsets is indexed by spawnRequest - 1. */
struct MotionSpawnOffset { u32 dx; u32 dy; };
/* gPoseFrameIndices maps the requested pose to an animation-frame index. */

/* Values of MotionEntity.spawnRequest and the child X-direction argument. */
#define MOTION_SPAWN_NONE      0
#define MOTION_SPAWN_POSITION  1
#define MOTION_SPAWN_PARAM     2
#define MOTION_SPAWN_DIR_RIGHT 1
#define MOTION_SPAWN_DIR_LEFT  -1

/* Six-slot circular formation driven by updateSixSlotFormation. The work block
 * hangs off the entity's +0x3C pointer and its slot area starts at +0x48:
 *   +0x00..0x17 six child-entity pointers
 *   +0x18..0x2F cached child world X (six u32)
 *   +0x30..0x47 cached child world Y (six u32)
 *   +0x48 base angle (u16), +0x4A rotating angle (u16), +0x4F active flag
 * The entity keeps its sprite at +0x38, the step-handler table at +0x14, the
 * script stream at +0x18 and the current s16 step index at +0x22. */
#define FORMATION_SLOT_COUNT  6
#define FORMATION_ANGLE_STEP  0xD9
#define FORMATION_KIND_ACTIVE 4

/* ----- Scripted-entity per-frame update family (updateScriptedMover and siblings). -----
 * An entity's +0x3C slot points at a work state.  Its +0x00 halfword carries
 * transient hit flags; its +0x28 field points at a sensor/collision target
 * whose hit byte (+0x01) and status word (+0x14) drive the script's hit path.
 * Its +0x34 field is an animation track and +0x48 holds per-step state. */
struct ScriptedHitTarget {
    u8 _0;
    u8 hitBits;      /* 0x01: transient hit bits; 0x05 while probing */
    u8 _2[0x12];
    u16 status;      /* 0x14: cleared when the target is recycled */
};

struct ScriptedWorkFlags {
    u16 hitFlags;    /* work+0x00: bit 0 = a hit was registered this frame */
};

/* Constants used by the scripted-entity update path. */
#define SCRIPT_HIT_PROBE_BITS   5        /* bits set on the target while probing */
#define SCRIPT_HIT_BIT_CLEAR    0xFB     /* clears bit 2 of the target hit byte */
#define SCRIPT_WORK_HIT_BIT     1        /* bit 0 of the work flags */
#define SCRIPT_STEP_SKIP_ANIM   0x8000   /* entity flags bit 0x8000 skips the tail */
#define SCRIPT_DEATH_SFX        0x189
#define SCRIPT_SCROLL_STRIDE    0x40
#define SCRIPT_SCROLL_PB_OFFSET 0x18A8   /* frame counter inside the main workspace */
#define SCRIPT_SCROLL_X_OFFSET  0x1278
#define SCRIPT_SCROLL_Y_OFFSET  0x127C
#define SCRIPT_SCROLL_BIAS_X    0x8000
#define SCRIPT_SCROLL_BIAS_Y    0xFFFF8000
#define SCRIPT_FIXED_FRAC_MASK  0xFFFF0000

/* Step-handler table used by updateScriptedAttack (0x0805B078). Its Thumb
 * entries are indexed by the current script step's opcode. */
#define SCRIPTED_ATTACK_STEP_TABLE 0x0866E8BC

/* Extra fields consumed by updateScriptedEnemyWithOffset: the table entry's
 * X-offset word and the form installed on the mirrored target. */
#define ENEMY_PARAM_X_OFFSET 0x54
#define ENEMY_MIRROR_FORM    0x10

/* Step-handler table at 0x0866E518 used by updateScriptedMoverAlt and the
 * nearby mover script-step helpers (each Thumb handler entry is one word). */
#define SCRIPTED_MOVER_ALT_STEP_TABLE 0x0866E518

/* Step-handler table used by updateScriptedMoverVariant (Thumb handler words
 * for the scripted entity family around 0x08053xxx). */
#define SCRIPTED_MOVER_VARIANT_STEP_TABLE 0x0866E690

/* ---------- Script-driven entity sprite constructor (createScriptedEntitySprite) ---------- */

/* Work state allocated in the owner's +0x3C slot (0x48 bytes). */
struct ScriptEntitySpriteWork {
    u8 _0[8];
    s32 worldX;      /* 0x08: fixed-point X, from owner +0x4C */
    s32 worldY;      /* 0x0C: fixed-point Y, from owner +0x54 */
    s32 paramA;      /* 0x10: from owner +0x5C */
    s32 paramB;      /* 0x14: from owner +0x6C */
    u8 _18[4];
    s16 kind;        /* 0x1C: animation/graphics kind index */
    u8 _1E[4];
    s16 kindSlot;    /* 0x22: slot returned by findKindIndex */
};

/* Owner of the sprite. Its kind (+0x84) and frame selector (+0x7C) pick the
 * animation; the script step at +0x22 is marked consumed on success. */
struct ScriptEntitySpriteOwner {
    u8 _0[2];
    u16 flags;       /* 0x02: SCRIPT_ENTITY_SPRITE_READY set on success */
    u8 _4[0x22 - 4];
    s16 stepIndex;   /* 0x22 */
    u8 _24[0x38 - 0x24];
    u8 *sprite;      /* 0x38 */
    struct ScriptEntitySpriteWork *work; /* 0x3C */
    u8 _40[0x4C - 0x40];
    s16 spawnX;      /* 0x4C */
    u8 _4E[6];
    s16 spawnY;      /* 0x54 */
    u8 _56[0x5C - 0x56];
    s32 paramA;      /* 0x5C */
    u8 _60[0x6C - 0x60];
    s32 paramB;      /* 0x6C */
    u8 _70[0x7C - 0x70];
    s16 frameIndex;  /* 0x7C: index into gScriptedSpriteFrameTable */
    u8 _7E[0x84 - 0x7E];
    u16 kind;        /* 0x84 */
};

/* Shared workspace and camera-scroll views used to place the sprite. */
struct ScriptEntityWorkspace {
    u8 _0[0x18A8];
    u8 frameCounter; /* 0x18A8 */
    u8 _18A9[0x19];
    u16 gfxFlags;    /* 0x18C2 */
};
struct ScriptEntityCamera {
    u8 _0[0x1278];
    u32 scrollX;     /* 0x1278 */
    u32 scrollY;     /* 0x127C */
};

#define SCRIPT_ENTITY_SPRITE_WORK_SIZE 0x48
#define SCRIPT_ENTITY_SPRITE_GFX_ID    0x8000000A
#define SCRIPT_ENTITY_SPRITE_READY     0x1000
#define SCRIPT_ENTITY_ANIM_STRIDE      0xC
#define SCRIPT_ENTITY_SCROLL_X_OFFSET  0x1278
#define SCRIPT_ENTITY_SCROLL_Y_OFFSET  0x127C
#define SCRIPT_ENTITY_SCROLL_SHIFT     6           /* 0x40-byte scroll rows */
#define SCRIPT_ENTITY_BIAS_X           0x8000
#define SCRIPT_ENTITY_BIAS_Y           0xFFFF8000
#define SCRIPT_ENTITY_FRAC_MASK        0xFFFF0000

/* Actor child-effect variant spawner (spawnActorChildEffectVariant).
 * Workspaces/parts are offset views of the shared effect tables. */
struct ActorChildVariantWorkspace {
    u8 _0[0x14EF];
    u8 parity;            /* 0x14EF: selects the child's active flag */
    u8 _1[0x1510 - 0x14F0];
    u8 frameFlag;         /* 0x1510: copied to parent+0x55 */
    u8 _2[0x1728 - 0x1511];
    u32 kindA;            /* 0x1728 */
    u32 kindB;            /* 0x172C: biased by -0x140000 */
};

/* Render part allocated by allocEffectPart for the child effect. */
struct ActorChildVariantPart {
    u8 _0;
    u8 variant;           /* 0x01: workspace parity bit */
    u8 kind;              /* 0x02 */
    u8 layer;             /* 0x03 */
    u16 gfxIndex;         /* 0x04 */
    u16 param0;           /* 0x06 */
    u16 param1;           /* 0x08 */
    u16 param2;           /* 0x0A */
    u16 param3;           /* 0x0C */
    u16 scaledValue;      /* 0x0E */
    u32 sprite;           /* 0x10 */
    u8 _14[2];
    u16 frame;            /* 0x16 */
    u16 _18;
};

/* State block reached through parent+4. */
struct ActorChildVariantState {
    u8 _0[4];
    u32 kindB;            /* 0x04: workspace kindB minus 0x140000 */
    u8 _1[0x18 - 0x08];
    u32 savedHandler;     /* 0x18: previous entity handler */
    u8 _2[0x2C - 0x1C];
    struct ActorChildVariantPart *part; /* 0x2C */
    u32 handleA, handleB, handleC, handleD; /* 0x30..0x3C */
    u8 _40[0x14];
    u32 extra54;          /* 0x54 */
};

/* One 2-byte script step: opcode byte then countdown byte at +0x19. */
struct ActorChildVariantStep { u8 _0[0x19]; u8 counter; };

#define ACTOR_CHILD_VARIANT_FLIP_BIT    0x10
#define ACTOR_CHILD_VARIANT_PART_KIND   2
#define ACTOR_CHILD_VARIANT_PART_LAYER  8
#define ACTOR_CHILD_VARIANT_PARAM       9
#define ACTOR_CHILD_VARIANT_SCALE       0x20
#define ACTOR_CHILD_VARIANT_FRAME       0x1E
#define ACTOR_CHILD_VARIANT_SCRIPT      0x084DCFBC
#define ACTOR_CHILD_VARIANT_TIMER_TABLE 0x084DD09C
#define ACTOR_CHILD_VARIANT_EXTRA54     0x1C
#define ACTOR_CHILD_VARIANT_VEL_RIGHT   0x00028000
#define ACTOR_CHILD_VARIANT_VEL_LEFT    0xFFFD8000
#define ACTOR_CHILD_VARIANT_VEL_Y       0xFFFB0000

/* Kind-0x66 three-part effect spawner (spawnKind66ThreePartEffect). */
#define KIND66_3PART_LAYER_PARAMS 0x08102B84  /* u16 affine parameter table */
#define KIND66_3PART_GFX_ID       0x80000009
#define KIND66_3PART_VISIBLE_FLAG 0x400       /* sprite attribute bit set on success */

/* Player-actor update family. All three per-frame updaters share the same
 * entity/work-state layout: +0x38 sprite, +0x3C work state, +0x14 script-step
 * table, +0x18 script stream, +0x22 current step index (s16), +0x24 cleanup
 * callback. Work state: +0x00 animation flags, +0x08/+0x0C 16.16 world X/Y,
 * +0x28 spawn-flag byte pair, +0x34 animation track, +0x48 view timer.
 * Their step tables are adjacent: sPlayerScriptStepTable (0x0866D748),
 * sPlayerIntroScriptStepTable (0x0866D78C), sPlayerAltScriptStepTable
 * (0x0866D7A0). */
struct PlayerActorSpawnFlags { u8 unk0; u8 flags; };
struct PlayerActorAnimFlags { u16 flags; };
struct PlayerActorCameraScroll { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
struct PlayerActorWorkspace { u8 _0[0x18A8]; u8 frameCounter; };

/* Step-handler table installed by the scripted-object update (updateTimedScriptedActor).
 * Entry 0 is also used as the event callback; the table is indexed by the
 * current step's opcode byte. */
#define SCRIPT_OBJECT_STEP_HANDLERS 0x0866E6BC

/* ---------- Path-driven scripted effect (updateScriptedEffectPath) ---------- */

/* Phase byte at script+8. */
enum PathFxPhase {
    PATHFX_PHASE_APPROACH = 0, /* wait for the target to enter camera range */
    PATHFX_PHASE_MOVE     = 1, /* walk the path's base+velocity positions */
    PATHFX_PHASE_HOLD     = 2, /* keep the animation ticking */
    PATHFX_PHASE_SWAY     = 3  /* sway vertically, then snap and finish */
};

/* One fixed point of the effect's path: base position and per-step velocity. */
struct PathFxPoint {
    s32 baseX; /* 0x00 */
    s32 velX;  /* 0x04 */
    s32 baseY; /* 0x08 */
    s32 velY;  /* 0x0C */
};

/* Animation/state block at target+0x48, shared with the animation helpers. */
struct PathFxScript {
    u8 frame;       /* 0x00 */
    s8 lastFrame;   /* 0x01 */
    u8 ticks;       /* 0x02 */
    s8 ticksReload; /* 0x03 */
    s16 *durations; /* 0x04 */
    u8 phase;       /* 0x08: PathFxPhase */
    s32 step;       /* 0x0C */
    s32 savedY;     /* 0x10 */
};

/* Moving object steered by the effect: 16.16 position and velocity. */
struct PathFxMotion {
    u8 _0[8];
    s32 x;  /* 0x08 */
    s32 y;  /* 0x0C */
    s32 vx; /* 0x10 */
    s32 vy; /* 0x14 */
};

/* Entity owning the effect: child list head at +0x30. */
struct PathFxOwner {
    u8 _0[0x30];
    void *child; /* 0x30 */
};

/* A child in the owner's +0x30 list: next pointer at +0x2C, flag at +0x70. */
struct PathFxChild {
    u8 _0[0x2C];
    void *next; /* 0x2C */
    u8 _30[0x70 - 0x30];
    u8 active;  /* 0x70 */
};

/* Camera position held in the main workspace. */
struct PathFxWorkspace {
    u8 _0[0x174C];
    s32 camX; /* 0x174C */
    s32 camY; /* 0x1750 */
};

/* Distances, step counts and final position used by the state machine. */
#define PATHFX_APPROACH_RANGE 0x4FFFFF
#define PATHFX_MOVE_LAST_STEP 0x12
#define PATHFX_HOLD_LAST_STEP 0x10
#define PATHFX_SWAY_LAST_STEP 0x18
#define PATHFX_SWAY_ANGLE_SHIFT 10
#define PATHFX_FINAL_X 0xFFFF8000

/* Constants for spawnKind2FFixedFrameSprite, the kind-0x2F sprite created from
 * an entity with a fixed starting animation frame. Its state block holds the
 * world position and the kind slot; the sprite's screen position is derived
 * from the per-frame camera scroll rows. */
#define KIND2F_FIXED_WORK_SLOT     0x48
#define KIND2F_FIXED_ANIM_FRAME    0x17
#define KIND2F_FIXED_GFX_ID        0x8000000A
#define KIND2F_FIXED_ATTR_MASK     0xC00
#define KIND2F_FIXED_ATTR_BIAS     0x200
#define KIND2F_FIXED_FRAME_BIAS    8
#define KIND2F_FIXED_SCROLL_X      0x1278
#define KIND2F_FIXED_SCROLL_Y      0x127C
#define KIND2F_FIXED_SCROLL_BIAS_X 0x8000
#define KIND2F_FIXED_SCROLL_BIAS_Y 0xFFFF8000
#define KIND2F_FIXED_FRAC_MASK     0xFFFF0000

/* Work block hung off the scripted multi-part object's state at +0x48, as
 * torn down by teardownScriptedMultiPartObject. The matching source keeps
 * these as raw pointers, so this layout is documentation for porters. */
struct ScriptedTeardownAttach {
    u8 _0[0x14];
    u8 *spriteHolderA; /* 0x14: holder whose +0x38 sprite gets bit 0x400 set at +2 */
    u8 *spriteHolderB; /* 0x18: second such holder */
    s32 secondaryMode; /* 0x1C: passed to setObjectModeWord */
    s32 attachedMode;  /* 0x20: passed to setAttachedObjectMode */
    u8 _24[8];
    u8 *scriptPartA;   /* 0x2C: +0x24 holds its step handler */
    u8 *scriptPartB;   /* 0x30 */
    u8 *effectPart;    /* 0x34: disableEffectPart / setEffectPartState */
    u8 _38[8];
    u32 timer;         /* 0x40: cleared when the teardown finishes */
};

/* Script-driven entity action-step family (updateEntityActionScript).
 * Object: +0x02 flags (0x8000 skips animation/repositioning), +0x14 step
 * handler table, +0x18 stream of (opcode, timer) step pairs, +0x22 current
 * step index, +0x38 sprite, +0x3C work state. */
#define SCRIPT_ENTITY_ACTION_HIT           1       /* work+0x00: a hit landed */
#define SCRIPT_ENTITY_ACTION_CONTACT       4       /* work+0x02: contact flag */
#define SCRIPT_ENTITY_ACTION_MIRROR        0x100   /* work+0x02 mirrored to work+0x04 */
#define SCRIPT_ENTITY_ACTION_MIRROR_CLEAR  0xFEFF
#define SCRIPT_ENTITY_ACTION_SKIP_ANIM     0x8000  /* object+0x02: skip animation */
#define SCRIPT_ENTITY_ACTION_SPECIAL_MOVE  1       /* step state+0x06: special move */
#define SCRIPT_ENTITY_ACTION_MOVE_SPEED    0xB60
#define SCRIPT_ENTITY_ACTION_STEP_TABLE    0x0866E4F8  /* gEntityActionStepTable */
#define SCRIPT_ENTITY_ACTION_EVENT_TABLE   0x08671BDC  /* gScriptEventCallbacks */
#define SCRIPT_ENTITY_ACTION_HIT_EVENT     2           /* callback id on a hit */

struct ScriptEntityActionWorkFlags {
    u16 hitFlags;      /* 0x00 */
    u16 contactFlags;  /* 0x02 */
    u16 statusFlags;   /* 0x04: mirrors contactFlags bit 0x100 */
    u16 f6;
    u16 f8;
    u16 targetGfx;     /* 0x0A: copied to the step target's +4 */
    u16 fC;
    u16 targetFrame;   /* 0x0E: +1 copied to the step target's +6 */
};

struct ScriptEntityActionObject {
    u8 _0[2];
    u16 flags;         /* 0x02 */
    u8 _4[0x10];
    u32 stepTable;     /* 0x14 */
    u8 _18[0x0A];
    s16 stepIndex;     /* 0x22 */
    u8 _24[0x14];
    u32 sprite;        /* 0x38 */
    u32 work;          /* 0x3C */
};

/* Spawn variant of a scripted entity AI effect (spawnEntityAiEffectVariant).
 * entity+0x6C points at a work block minus 4; the work state starts at +4.
 * Offsets in that work state: +0x08 X, +0x0C Y, +0x10 flags/state word,
 * +0x18 saved update handler, +0x3C render layer, +0x4C entity parameter.
 * The render layer is volatile so every field store re-reads its pointer. */
struct AiVariantWorkSlot {
    u8 _0[0x3C];
    u8 * volatile layer; /* 0x3C: layer allocated by allocEffectPart */
};

/* Values used while seeding the variant's render layer and sprite. */
#define AI_VARIANT_LAYER_KIND       2      /* layer byte at +2 */
#define AI_VARIANT_LAYER_PRIORITY   8      /* layer byte at +3 */
#define AI_VARIANT_LAYER_TIMER      0xF    /* layer halfword at +0x16 */
#define AI_VARIANT_LAYER_TAIL       0x7F   /* layer halfword at +0x18 */
#define AI_VARIANT_GFX_ID           0x80000006 /* sprite graphics id at +0x1C */
#define AI_VARIANT_WORK_FLAGS       0x2BF  /* work state word at +0x10 */
#define AI_VARIANT_WORK_Y_BIAS      0xFFEC0000 /* applied to the workspace Y */
#define AI_VARIANT_STATE_READY      2      /* workspace byte at +0x14EC */

/* Table-driven directional child effect (spawnActorChildEffectFromTable).
 * entity+0x9C holds a u32 variant index; gActorChildEffectVariantTable has
 * 8-byte records: +0 pointer to timer data, +4 direction byte. The part hangs
 * off the work state at +0x2C (work state = entity+0x6C pointer + 4). */
struct TabledChildEffectPart {
    u8 flags;       /* 0x00 */
    u8 variant;     /* 0x01: workspace bit 0 */
    u8 kind;        /* 0x02: 2 */
    u8 layer;       /* 0x03: 8 */
    u16 gfxIndex;   /* 0x04: from gGameStatus+0x304 */
    u16 width;      /* 0x06: 4 */
    u16 height;     /* 0x08: 4 */
    u16 affine0;    /* 0x0A */
    u16 affine1;    /* 0x0C */
    u16 palette;    /* 0x0E: gGameStatus+0x2E2 scaled by 50% */
    u32 sprite;     /* 0x10: owner sprite */
    u8 _14[2];
    u16 frame;      /* 0x16: 5 */
    u16 animStep;   /* 0x18: 0x54 */
};

/* Animation data installed on the sprite, and work-state constants. */
#define CHILD_EFFECT_TABLED_ANIM_DATA 0x084D962C
#define CHILD_EFFECT_WORK_DISTANCE    0x50000
#define CHILD_EFFECT_STATE_TIME       0x18

/* Main-workspace byte at +0x1510 supplies the child effect's variant bit. */
struct ChildEffectWorkspace { u8 _0[0x1510]; u8 variantBit; };

/* Scene/layer object kept in sync with an actor (updateSceneObjectFromActor).
 * +0x04/+0x08 callback arguments, +0x10 state-change callback, +0x14/+0x18
 * child objects, +0x1C layer index, +0x29 previous state, +0x2C/+0x30 world
 * position, +0x34 state byte passed to children, +0x35 signed state. */
struct SceneObjectFlags { u8 _0[2]; u16 flags; };
struct SceneObjectPosition { u8 _0[8]; s32 x; s32 y; };
struct SceneObjectChildState { u8 _0[0x58]; u8 state; };
struct SceneObject {
    u8 _0[4];
    s32 f04[2];
    u8 _0C[4];
    void *callback;
    void *childA;
    void *childB;
    u8 layer;
    u8 _1D[0xC];
    s8 prevState;
    u8 _2A[2];
    s32 posX;
    s32 posY;
    u8 stateByte;
    s8 state;
};
struct SceneWorkspace { u8 _0[0x18A8]; u8 activeLayer; };

/* gCameraState is split into 0x40-byte pages, one per layer. */
struct SceneLayerEntry { u32 x; u32 y; u8 _[0x38]; };
struct SceneLayerFlagRecord { u16 flag; u8 _[0x3E]; };
struct SceneLayerFlags { u8 _0[0x1260]; struct SceneLayerFlagRecord recs[1]; };
struct SceneLayerEntries { u8 _0[0x1278]; struct SceneLayerEntry entries[1]; };

#define SCENE_OBJ_FLIP_X         0x10
#define SCENE_OBJ_FLIP_CLEAR     0xFFEF
#define SCENE_LAYER_FLAG         0x2000
#define SCENE_LAYER_FLAG_CLEAR   0xDFFF
#define SCENE_LAYER_SHIFT        6
#define SCENE_SCROLL_X_ROUND     0x8000
#define SCENE_SCROLL_Y_ROUND     0xFFFF8000
#define SCENE_SCROLL_FRAC_MASK   0xFFFF0000
#define SCENE_SCROLL_BIAS        0x400000

/* Kind-0x44 script effect spawned by spawnKind44ScriptEffect (script command). */
#define KIND44_SCRIPT_EFFECT_KIND       0x44
#define KIND44_SCRIPT_EFFECT_WORK_SIZE  0x48
#define KIND44_SCRIPT_EFFECT_GFX_ID     1
#define KIND44_SCRIPT_EFFECT_FRAME      0x1A
#define KIND44_SCRIPT_EFFECT_INIT_TIMER 0xFF
#define KIND44_SCRIPT_EFFECT_READY      0x1000
#define KIND44_SCRIPT_LAYER_KIND        5
#define KIND44_SCRIPT_LAYER_INDEX       8
#define KIND44_SCRIPT_LAYER_PRIORITY    1
extern u16 gKind44ScriptEffectLayerAttrs[];

/* Alternate kind-0x66 three-part effect (spawnKind66ThreePartEffectAlt). */
#define KIND66_ALT_WORK_SLOT_SIZE 0x48
#define KIND66_ALT_GFX_ID         0x8000000B
#define KIND66_ALT_KIND           0x66
#define KIND66_ALT_ANIM_FRAME     0x6A
#define KIND66_ALT_LAYER_KIND     1
#define KIND66_ALT_LAYER_INDEX    8
#define KIND66_ALT_LAYER_PRIORITY 1
#define KIND66_ALT_SPRITE_ATTR    0x400
#define KIND66_ALT_READY_FLAG     0x1000
extern u16 gKind66ThreePartAltLayerAttrs[];

/* Controlled-entity update (updateControlledEntity). */
#define CONTROLLED_MOTION_ACTIVE_FLAG 1
#define CONTROLLED_HIT_STEP           4
#define CONTROLLED_CONTROL_BUSY_FLAG  4
#define CONTROLLED_LINK_BUSY_FLAG     2
#define CONTROLLED_ENTITY_SKIP_FLAG   0x8000
#define CONTROLLED_MOVE_STEP          0x100000
extern u8 gControlledEntityStepHandlers[];

/* Alternate controlled-entity update (updateControlledEntityAlt). */
#define ALT_CONTROLLED_STEP_HANDLERS   0x0866DB00
#define ALT_CONTROLLED_EVENT_CALLBACKS 0x08671BDC
#define ALT_CONTROLLED_MOTION_FLAG     1
#define ALT_CONTROLLED_HIT_STEP        2
#define ALT_CONTROLLED_CONTROL_FLAG    4
#define ALT_CONTROLLED_LINK_FLAG       2
#define ALT_CONTROLLED_READY_FLAG      0x8000
#define ALT_CONTROLLED_MOVE_STEP       0x80000

/* Script-step defeat handler (scriptStepDefeatEntity). The entity's work state
 * holds an animation stage at +0x34 (byte +1 selects the stage, word +4 gates
 * particle emission) and a motion block at +0x48 receiving velocity, launch
 * jitter and knockback. */
#define DEFEAT_STAGE_VARIANT     1     /* anim+1: choose a variant from the global flag */
#define DEFEAT_STAGE_PARTICLES   2     /* anim+1: emit directional particles */
#define DEFEAT_PARTICLE_GATE     1     /* anim+4 must equal this to emit them */
#define DEFEAT_KNOCKBACK_FLAG    2     /* anim+0 bit: jitter, knockback and finish */
#define DEFEAT_ANIM_FRAME        5
#define DEFEAT_VARIANT_VELOCITY  0x10000  /* written to motion+0x14 when the flag is set */
#define DEFEAT_KNOCKBACK_LEFT    0xA000
#define DEFEAT_KNOCKBACK_RIGHT   0xE000
#define DEFEAT_PARTICLE_SPEED    0x30000

/* Global workspace word at +0x189C, read by the defeat step to alternate its
 * variant (bit 1 of value/2). Declared here so sources need only the extern. */
struct MainWorkspaceDefeatFlag {
    u8 _0[0x189C];
    s32 flag;
};

/* ---------- Angle-driven projectile (updateAngledProjectile) ---------- */

/* Bit in the script entity's flag word at +0x64 that fires the projectile. */
#define ANGLE_PROJECTILE_FIRE_FLAG    0x20

/* Trig-lookup constants: a quarter turn turns the sine lookup into a cosine,
 * and the biases make negative products truncate toward zero before the shift. */
#define ANGLE_PROJECTILE_QUARTER_TURN 0x4000
#define ANGLE_PROJECTILE_SIN_BIAS     0x7FF
#define ANGLE_PROJECTILE_COS_BIAS     0xFFF
#define ANGLE_PROJECTILE_SIN_SHIFT    11
#define ANGLE_PROJECTILE_COS_SHIFT    12
#define ANGLE_PROJECTILE_POS_SCALE    8

/* Angle source read through the motion block's +0x58 pointer. */
struct AngledProjectileTarget {
    u8 _0[2];
    u16 facing;       /* 0x02: rotates the direction vector */
    u16 offsetAngle;  /* 0x04: angle of the added position offset */
};

/* Motion parameters embedded at work+0x48. */
struct AngledProjectileMotion {
    u8 _0[8];
    u16 angle;        /* 0x08: angle whose sine/cosine produce the direction */
    u8 _0A[0xE];
    s16 paramA;       /* 0x18: projectile spawner parameter at +0x5C */
    u8 _1A[8];
    s16 paramB;       /* 0x22: projectile spawner parameter at +0x6C */
    u8 _24[0x34];
    struct AngledProjectileTarget *target; /* 0x58 */
    s32 baseX;        /* 0x5C */
    s32 baseY;        /* 0x60 */
};

/* Work state reached through the entity's +0x3C pointer. The motion block is
 * embedded at +0x48 (not a pointer). */
struct AngledProjectileWork {
    u8 _0[8];
    s32 worldX;    /* 0x08: output, rotated trig position */
    s32 worldY;    /* 0x0C: output, rotated trig position */
    u8 _10[0xC];
    s16 kind;      /* 0x1C: kind passed to the projectile spawner */
    u8 _1E[0x2A];
    struct AngledProjectileMotion motion; /* 0x48 */
};

/* Script command handler table and event callback index used by the combat
 * scripted-object update (updateScriptedCombatObject). */
#define COMBAT_SCRIPT_STEP_TABLE 0x0866E854
#define COMBAT_SCRIPT_SOUND_EVENT 3

/* gCameraState fields reset by the level-scene loader. */
struct LevelLoadCameraState {
    u8 _0[0x125C];
    u32 f125C;
    u16 f1260;
    u16 f1262;
    u8 _1264[0x14];
    u32 f1278;
    u32 f127C;
    u8 _1280[0x20];
    u16 f12A0;
    u8 _12A2[0x3E];
    u16 f12E0;
    u8 _12E2[0x3E];
    u16 f1320;
};

/* Constants used by loadLevelScene: hardware registers, scroll offset and the
 * compressed graphics blobs with their VRAM/palette destinations. */
#define LEVEL_GFX_MODE_REG      0x03000830
#define LEVEL_DMA3_REG          0x040000D4
#define LEVEL_SCROLL_X_OFFSET   0x1278
#define LEVEL_TILES_VRAM_C000   0x08634AC8
#define LEVEL_TILES_VRAM_0      0x086363FC
#define LEVEL_PALETTE_DATA      0x086361BC
#define LEVEL_TILES_VRAM_10000  0x08635A70
#define LEVEL_PALETTE_EXTRA     0x086363BC

/* Constants of the projectile spawn constructor (spawnProjectileEntity). */
#define PROJECTILE_WORK_SLOT      0x48
#define PROJECTILE_GFX_ID         0x8000000A
#define PROJECTILE_ANIM_FRAME     9
#define PROJECTILE_READY_FLAG     0x1000
#define PROJECTILE_READY_FLAG_ALT 0x800
#define PROJECTILE_SCROLL_X_OFFSET 0x1278
#define PROJECTILE_SCROLL_Y_OFFSET 0x127C

/* Kind and fixed starting animation frame of the kind-0x29 fixed-frame spawner. */
#define SPRITE_KIND_FIXED_FRAME_29 0x29
#define FIXED_FRAME_29_START_FRAME 0xC

/* Scene-object setup performed by initSceneObject. The object's +0x02 u16
 * flags word gains SCENE_OBJ_READY_FLAG once setup is complete; +0x14 is the
 * update handler, +0x24 the cleanup callback and +0x5C the saved callback. */
#define SCENE_OBJ_READY_FLAG       0x800
#define SCENE_OBJ_UPDATE_HANDLER   0x080BDF45
#define SCENE_OBJ_CLEANUP_CALLBACK 0x080BE215

/* Transition-state slot seeded from a ROM template (two 0x20-byte entries). */
#define SCENE_OBJ_STATE_SLOT       0x99
#define SCENE_OBJ_STATE_TEMPLATE   0x08102FFC
#define SCENE_OBJ_STATE_COPY_SIZE  0x40

/* VRAM DMA blocks loaded while setting up the scene object. */
#define SCENE_OBJ_DMA_REG    0x040000D4
#define SCENE_OBJ_GFX_A_SRC  0x085127E0
#define SCENE_OBJ_GFX_A_DST  0x0600C000
#define SCENE_OBJ_GFX_A_CTRL 0x80001000
#define SCENE_OBJ_GFX_B_SRC  0x0851ACBC
#define SCENE_OBJ_GFX_B_DST  0x0600F700
#define SCENE_OBJ_GFX_B_CTRL 0x80000480

/* Base of the shadow input/state block and the halfword flag written into it. */
#define SCENE_OBJ_INPUT_BASE 0x02025FF0
#define SCENE_OBJ_INPUT_FLAG 0x1000

/* Bounded follow-path controller (struct FollowPath in the updater):
 * 0x00 position, 0x04 angle, 0x08 minPos, 0x0C maxPos, 0x10 speed,
 * 0x14 maxTurn, 0x18 dirFlags, 0x1A controlFlags, 0x1C timeLimit,
 * 0x20 travelLimit, 0x24 timer, 0x28 accumulated travel. */
#define FOLLOW_CTRL_MOVE_FORWARD  1
#define FOLLOW_CTRL_MOVE_BACKWARD 2
#define FOLLOW_CTRL_CHECK_DIR     4
#define FOLLOW_CTRL_CHECK_TIME    8
#define FOLLOW_CTRL_CHECK_TRAVEL  0x10
#define FOLLOW_DIR_NEGATIVE       1
#define FOLLOW_DIR_POSITIVE       2
#define FOLLOW_DIR_TURN_LIMIT     4
#define FOLLOW_DIR_TRAVEL_LIMIT   8

/* Data installed by the entity-child spawn path: sprite animation sequence and
 * the timer descriptor passed to startEffectTimer. */
#define CHILD_OBJ_ANIM_SEQ   0x084F52C8
#define CHILD_OBJ_TIMER_DATA 0x084F52E8

/* Script-reference types handled by scriptCmdSpawnReferencedSprite and the
 * sprite kinds they select in gSpriteKindTable. */
#define SCRIPT_REF_TYPE_C9  0xC9
#define SCRIPT_REF_TYPE_CA  0xCA
#define REF_SPRITE_KIND_C9  8
#define REF_SPRITE_KIND_CA  0x74

/* Position reference carried by a main-object script thread (thread+0xAC holds
 * the holder, whose +4 field points at this record). */
struct RefSpawnPositionRef { s16 value0; s16 value1; s16 type; s16 flags; };
struct RefSpawnPositionHolder { u8 _0[4]; struct RefSpawnPositionRef *ref; };

/* Per-kind graphics entry in gSpriteKindTable: tile id, starting frame and
 * palette/mode id, 0x14 bytes per kind. */
struct RefSpawnKindEntry { u16 tile; s16 frame; u16 mode; u8 _6[0x14 - 6]; };

/* gSpriteAffineParams holds the four affine/OAM words copied into the render
 * layer of the sprite spawned by this command. */
extern u16 gSpriteAffineParams[];

/* Thumb step-handler table installed in an enemy's +0x14 field by
 * updateEnemyMotionEntity; indexed by the opcode byte at entity+0x18+2*step. */
#define ENEMY_MOTION_STEP_TABLE 0x0866FCA0

/* Table of Thumb trig-lookup entries; the fading particle effect loads its
 * first pointer to convert a random angle into particle offsets. */
#define TRIG_FUNC_TABLE 0x08671BFC

/* ---------- Waypoint-approach actor update family ---------- */

/* Script steps dispatched when the approach finishes or when the tracked X
 * coordinate drifts too far from the camera focus. */
#define WAYPOINT_STEP_ARRIVED 2   /* waypoint reached: finish the approach */
#define WAYPOINT_STEP_RESET   4   /* tracked X out of focus range: reset */

/* Animation track at (work state)+0x34, consumed by setAnimationFrame. */
struct WaypointAnimTrack {
    u8 mode;        /* 0x00: playback mode */
    u8 state;       /* 0x01: 1 enables the approach */
    u8 _02[2];
    u32 flag;       /* 0x04: 1 resets the approach angle */
};

/* Per-step steering block at (work state)+0x48. Angles are fixed point. */
struct WaypointSteerState {
    u32 trigResult;    /* 0x00: doubled result of the trig lookup */
    u16 angle;         /* 0x04: advanced by one every frame */
    u8 _06[4];
    s16 nearTarget;    /* 0x0A: 1 while inside the target box */
    s16 targetReached; /* 0x0C: 1 once the polar radius is exhausted */
    u8 _0E[0xE];
    s32 trackedX;      /* 0x1C: fixed-point X compared against focus */
    s32 targetY;       /* 0x20: fixed-point Y of the approach target */
    u8 _24[0x2C];
    u8 movement[4];    /* 0x50: parameters for the movement integrator */
    s32 facing;        /* 0x54: horizontal facing passed to setSpriteFlip */
};

/* Work state hung off the actor's +0x3C pointer. */
struct WaypointWorkState {
    u8 _0[0x34];
    struct WaypointAnimTrack anim;    /* 0x34 */
    struct WaypointSteerState steer;  /* 0x48 */
};

/* Script-driven actor running the waypoint approach. */
struct WaypointActor {
    u8 _0[0x18];
    u8 *scriptSteps;  /* 0x18: stream of opcode/timer byte pairs */
    u8 _1C[4];
    s16 stepIndex;    /* 0x22 */
    u8 _24[0x14];
    u32 sprite;       /* 0x38 */
    struct WaypointWorkState *work; /* 0x3C */
};

/* Constants used while steering toward the waypoint. */
#define WAYPOINT_SCREEN_X_BIAS (0xF1 << 0xF)   /* screen-centre X offset */
#define WAYPOINT_NEAR_DX       (0xC0 << 0xE)   /* target box half-width */
#define WAYPOINT_NEAR_DY       (0x80 << 0xD)   /* target box half-height */
#define WAYPOINT_FOCUS_CUTOFF  (0xD2 << 0x10)  /* reset distance from focus */
#define WAYPOINT_ANGLE_DIVISOR 0x24            /* angle units per trig step */
#define WAYPOINT_SHRINK_STEP   (0x80 << 0x6)   /* radius decrement per frame */

/* Contact target reached from a scripted attack's per-step pointer pair at
 * work+0x48/+0x4C. Bit 0x20 of the flag word at +0x6C marks it blocked. */
struct ScriptAttackContactTarget { u8 pad[0x6C]; u16 flags; };
#define SCRIPT_TARGET_BLOCKED_FLAG 0x20    /* ORed into a contact target's status */
#define SCRIPT_TARGET_UNBLOCK_MASK 0xFFDF  /* clears the blocked bit above */

/* Step-handler table installed at entity+0x14 by the scripted-attack tick. */
#define SCRIPT_ATTACK_OBJ_STEP_TABLE 0x0866DC10

/* Five-part scripted entity. Its work state (+0x3C) holds five render-part
 * pointers at +0x84; part[1] is the OAM alpha byte (0 opaque, 1 translucent).
 * The entity is idle (and fades its parts) when none of these flag bits are set. */
#define FIVE_PART_PART_ALPHA_OPAQUE 0
#define FIVE_PART_PART_ALPHA_FADE   1
#define FIVE_PART_ACTIVE_FLAGS      0x0D
#define FIVE_PART_STEP_END_SFX      0x85

/* Workspace fields and constants used when a script command starts a main-object
 * timer effect. The two coordinate pairs select the effect's spawn origin. */
#define MAIN_OBJ_GATE_BYTE          0x173A
#define MAIN_OBJ_WORK_STATE         0x14EC
#define MAIN_OBJ_MODE_BYTE          0x14ED
#define MAIN_OBJ_MODE_SPECIAL       0xA2
#define MAIN_OBJ_EFFECT_X           0x1728
#define MAIN_OBJ_EFFECT_X_ALT       0x1744
#define MAIN_OBJ_EFFECT_Y           0x172C
#define MAIN_OBJ_EFFECT_Y_ALT       0x1748
#define MAIN_OBJ_EFFECT_Y_BIAS      0xFFEC0000  /* -0x140000 in 16.16 */
#define MAIN_OBJ_EFFECT_VALUE_A     0x2BF
#define MAIN_OBJ_EFFECT_VALUE_B     0x57E
#define MAIN_OBJ_TIMER_EFFECT_ANIM_TABLE 0x08472A58

/* Script-step steering helper (updateSteerTowardPlayerStep).
 * The player's fixed-point world position lives in the main workspace at
 * STEER_PLAYER_X_OFFSET / STEER_PLAYER_Y_OFFSET (see also the playerX/playerY
 * view used by the other player-tracking steps). */
#define STEER_PLAYER_X_OFFSET 0x174C
#define STEER_PLAYER_Y_OFFSET 0x1750

/* Animation-track flag raised on the frame that retriggers the steering
 * adjustment, and the frame installed in response. */
#define STEER_KEYFRAME_FLAG 2
#define STEER_ANIM_FRAME 5

/* Steering step block hung off the work state at +0x48:
 *   +0: u8 index into gSteerAngleOffsets
 *   +8: s32 heading produced from the bearing and the table offset */
#define STEER_HEADING_OFFSET 8

/* Render layer reached through work+0x28. Its +2 byte is the layer id and +3
 * the priority; the steering step clears them, then restores these values. */
#define STEER_LAYER_VALUE 8
#define STEER_PRIORITY_VALUE 1

/* Per-state angle adjustments added to (or subtracted from, by bearing
 * quadrant) the direction to the player. Indexed by the steering block's
 * first byte. */
extern s32 gSteerAngleOffsets[];

/* View/camera position synchronisation (syncViewPosition). gMainWorkspace is
 * the global state buffer; this is the partial view used when the camera
 * follows a world position. */
struct ViewSyncState {
    u8 _0[0x14B8];
    u32 modeFlags;       /* 0x14B8: low nibble selects the position source */
    u8 _14BC[8];
    u8 fracXFrom;        /* 0x14C4: fractional X of the previous position */
    u8 fracYFrom;        /* 0x14C5 */
    u8 fracXTo;          /* 0x14C6: fractional X of the target position */
    u8 fracYTo;          /* 0x14C7 */
    u32 srcX;            /* 0x14C8: 16.16 source position */
    u32 srcY;            /* 0x14CC */
    u8 _14D0[0x258];
    u32 viewX;           /* 0x1728: camera position written back here */
    u32 viewY;           /* 0x172C */
    u8 _1730[0x1C];
    u32 playerX;         /* 0x174C: player position written back here */
    u32 playerY;         /* 0x1750 */
    u8 _1754[0x150];
    u32 mode;            /* 0x18A4: low nibble copied from modeFlags */
};

/* Script parameter reached through the action context's +0x12C pointer. */
struct ViewSyncParam {
    u8 _0[0xC];
    s16 offsetY;         /* 0x0C: 16.16 vertical adjustment (shifted <<16) */
};

struct ViewSyncContext {
    u8 _0[0x12C];
    struct ViewSyncParam *param; /* 0x12C */
};

/* Output world position, in 16.16 fixed point. */
struct WorldPosition { u32 x; u32 y; };

/* Low nibble of ViewSyncState.modeFlags selects how the position is chosen. */
#define VIEW_SYNC_FLAGS_MASK      0x0F
#define VIEW_SYNC_FLAG_HELD       0x08  /* keep the current position */
#define VIEW_SYNC_FLAG_INTERP     0x05  /* interpolate between fractional parts */
#define VIEW_SYNC_FLAG_DIRECT     0x02  /* copy the source position directly */

/* Values returned by syncViewPosition. */
#define VIEW_SYNC_MODE_NONE          0
#define VIEW_SYNC_MODE_HELD          1
#define VIEW_SYNC_MODE_INTERPOLATED  2
#define VIEW_SYNC_MODE_DIRECT        3

/* Render layer grabbed from allocEffectPart and hung off a scripted entity's
 * work state at +0x3C by spawnPoseCompanionEffect. Its fields mirror the
 * standard effect-layer layout, with two extra words at +0x16/+0x18. */
struct PoseCompanionLayer {
    u8 _0;           /* 0x00: unused */
    u8 mode;         /* 0x01: low bits of the scene mode flags */
    u8 kind;         /* 0x02: POSE_COMPANION_KIND */
    u8 layer;        /* 0x03: render layer index */
    u16 gfxIndex;    /* 0x04 */
    u16 affine0;     /* 0x06 */
    u16 affine1;     /* 0x08 */
    u16 affine2;     /* 0x0A */
    u16 affine3;     /* 0x0C */
    u16 palette;     /* 0x0E: percentage-scaled duration */
    u32 sprite;      /* 0x10: owning sprite handle */
    u8 _14[2];       /* 0x14 */
    u16 animSlot;    /* 0x16: starting animation slot */
    u16 extraFlags;  /* 0x18: companion-specific flags */
};

#define POSE_COMPANION_MODE_MASK     5
#define POSE_COMPANION_KIND          2
#define POSE_COMPANION_LAYER         8
#define POSE_COMPANION_AFFINE_0      8
#define POSE_COMPANION_AFFINE_1      0x10
#define POSE_COMPANION_ANIM_SLOT     0xF
#define POSE_COMPANION_FLAGS         0x7E
#define POSE_COMPANION_SCALE_100     0x64
#define POSE_COMPANION_SCALE_ALT     0x8D
#define POSE_COMPANION_Y_OFFSET      0x500000
#define POSE_COMPANION_VARIANT_SHIFT 3
#define POSE_COMPANION_VARIANT_MASK  7

/* Companion sprite variant of the pose-effect spawner: it seeds the owner
 * sprite's animation/position fields instead of the work-state coordinates,
 * and uses a different affine preset and percentage scale. */
#define POSE_COMPANION_SPRITE_AFFINE_0  0x1E
#define POSE_COMPANION_SPRITE_AFFINE_1  0x1E
#define POSE_COMPANION_SPRITE_SCALE_100 0x2D
#define POSE_COMPANION_SPRITE_SCALE_ALT 0x3F
#define POSE_COMPANION_SPRITE_FLAGS     0x7D

/* gPoseCompanionOffsets (0x080E00C8) holds eight fixed-point offsets; the
 * pose manager's variant word selects one with (variant >> 3) & 7. */

/* Work state hung off a scripted companion entity at +0x3C. */
struct CompanionWorkState {
    u8 _0[4];
    u16 flags;           /* 0x04: pending-cancel bit cleared on finalize */
    u8 _6[0xA];
    u32 velocityX;       /* 0x10 */
    u32 velocityY;       /* 0x14 */
    u8 _18[0x1C];
    u8 animDesc[0x14];   /* 0x34: graphics descriptor passed to forceAnimationFrame */
    u8 _48[8];
    void *effect;        /* 0x50: spawned effect entity */
    u8 _54[0xC];
    void *timerNode;     /* 0x60 */
    u8 _64[7];
    u8 state;            /* 0x6B */
    u16 timer;           /* 0x6C */
};

/* Child-node kinds whose pending callbacks are cancelled during finalize. */
#define COMPANION_CHILD_CANCEL_A 0x17D
#define COMPANION_CHILD_CANCEL_B 0x177

/* Flags, state and animation/audio constants of the finalize path. */
#define COMPANION_FINAL_FLAG_MASK 0xFFFB
#define COMPANION_DONE_FLAG       0x0400
#define COMPANION_FINAL_STATE     0x10
#define COMPANION_FINAL_FRAME     9
#define COMPANION_FINAL_BEHAVIOR  1
#define COMPANION_FINAL_SFX       0x186
#define COMPANION_FINAL_PARAM     0x0B

/* Work block hung off a main object at +0x6C: layout used by initMainObjectEffectGraphics. */
struct MainObjectEffectWork {
    u8 _0[4];
    u32 gfxWord0;        /* 0x04: first graphics-init word */
    u8 _8[0x10C];
    u32 posX;            /* 0x114: zeroed */
    u32 posY;            /* 0x118: zeroed */
    u8 _11C[8];
    u8 statusByte0;      /* 0x124: from gGameStatus */
    u8 statusByte1;      /* 0x125 */
    u8 statusByte2;      /* 0x126 */
    u8 _127[9];
    struct MainObjectEffectLayer *layer1; /* 0x130 */
    struct MainObjectEffectLayer *layer2; /* 0x134 */
};

/* Render layer allocated twice by allocEffectPart and stored in the work block above. */
struct MainObjectEffectLayer {
    u8 mode;             /* 0x00 */
    u8 active;           /* 0x01 */
    u8 param2;           /* 0x02 */
    u8 param3;           /* 0x03 */
    u16 gfxA;            /* 0x04 */
    u8 affine[8];        /* 0x06..0x0D */
    u16 gfxB;            /* 0x0E */
    void *sprite;        /* 0x10: owner sprite */
    u8 _14[2];
    u16 timer;           /* 0x16 */
    u16 tail;            /* 0x18 */
};

/* Companion/boss action handler (tryCompanionBossAction): layout of the global
 * workspace it samples. The first fields mirror ActionWorkspace; +0x1848 is
 * the flag word armed when the special attack fires. */
struct CompanionActionWorkspace {
    u8 pad0[0x24];
    u32 modeFlags;      /* 0x24: nonzero selects the modeMask input word */
    u16 modeMask;       /* 0x28: action bits active in that mode */
    u8 pad2A[0x14C3];
    u8 actionState;     /* 0x14ED: nonzero queues a screen transition */
    u8 pad14EE[0x35A];
    u32 attackFlags;    /* 0x1848 */
};

/* gGameStatus bytes consulted by the companion action gate. */
#define COMPANION_ACTION_MASK     0x3C2  /* u16 action-allow mask */
#define COMPANION_GATE_BYTE       0x2DB  /* must read 0 for the special attack */
#define COMPANION_GATE_INDEX_A    0x304  /* index into the table at +0x30B */
#define COMPANION_GATE_INDEX_B    0x305  /* index into the table at +0x315 */
#define COMPANION_GATE_TABLE_A    0x30B
#define COMPANION_GATE_TABLE_B    0x315

/* Special action armed by tryCompanionBossAction. */
#define COMPANION_ATTACK_FLAG_BITS 0x49FE0000
#define COMPANION_ATTACK_FORM      0x35
#define COMPANION_ATTACK_SFX       0x12C
#define COMPANION_ATTACK_STEP      0x1C
#define COMPANION_ACTION_READY     0x8C  /* work+0x8C set to 1 on success */

/* Main work buffer at 0x02025FF0, as viewed by the enemy script step that
 * spawns a projectile: +0x1870 is the owner id passed to the spawner. */
struct EnemySpawnWorkspace {
    u8 _0[0x1870];
    u32 ownerId;
};

/* Animation opcodes read from the current frame-table entry of an enemy
 * script step. The motion opcode advances movement instead of spawning. */
#define ENEMY_STEP_OP_MOTION 0x0E
#define ENEMY_STEP_OP_POSE_1 15
#define ENEMY_STEP_OP_POSE_2A 17
#define ENEMY_STEP_OP_POSE_2B 19
#define ENEMY_STEP_OP_POSE_3 21

/* Constants of the random-projectile script step and of its animation track. */
#define ENEMY_STEP_PROJECTILE_KIND 1
#define ENEMY_STEP_PROJECTILE_LIFE 2
#define ENEMY_STEP_QUARTER_TURN    0x4000
#define ENEMY_STEP_SKIP_FLAG       1
#define ANIM_TRACK_CALLBACK_FLAG   2

/* Offsets into gCameraState used by initMainObjectGraphics. */
#define CAMERA_MO_STATE_WORD  0x125C
#define CAMERA_MO_MAP_BASE    0x1260
#define CAMERA_MO_MAP_CONTROL 0x1262
#define CAMERA_MO_SCROLL_X    0x1278
#define CAMERA_MO_SCROLL_Y    0x127C

/* Table at 0x0866CB50: one 8-byte record per object kind,
 * {compressed gfx A, compressed gfx B}, followed by handler pointers. */
#define MAIN_OBJ_GFX_TABLE 0x0866CB50

/* Compressed graphics loaded by initMainObjectGraphics. Kinds 0..4 use the
 * normal pair, other kinds the alternate pair; the per-kind pair comes from
 * MAIN_OBJ_GFX_TABLE. */
#define MAIN_OBJ_TILE_GFX_NORMAL_A 0x0864292C
#define MAIN_OBJ_TILE_GFX_NORMAL_B 0x086452A4
#define MAIN_OBJ_TILE_GFX_ALT_A    0x08644680
#define MAIN_OBJ_TILE_GFX_ALT_B    0x08645604
#define MAIN_OBJ_SPRITE_GFX        0x08645264

/* Script state shared by the main-object timer callbacks. The step bytes start
 * at +0x18 (one byte at +0x19 is the current step's counter), +0x22 is the
 * signed step index and +0x3C selects the object's graphics set. */
struct MainObjectState {
    u8 _0[0x14];
    void *stepTable; /* 0x14 */
    u8 steps[0xE];   /* 0x18 */
    s16 stepIndex;   /* 0x22 */
    u8 _24[0x18];
    u32 kind;        /* 0x3C */
};

/* Script-step stream layout: steps begin at SCRIPT_STEP_BASE_OFFSET (0x18) as
 * 2-byte (opcode, timer) records; the next two bytes carry event ids. */
#define SCRIPT_STEP_TIMER_OFFSET       0x19
#define SCRIPT_STEP_EVENT_OFFSET       0x1A
#define SCRIPT_STEP_EVENT_TIMER_OFFSET 0x1B

/* Actor extra-flag bit at +0x6C that latches the work-state hit flag, and the
 * event callback id dispatched when a flagged projectile hit lands. */
#define SCRIPT_PROJ_ATTACK_FLAG 0x02
#define SCRIPT_PROJ_HIT_EVENT   1

/* Sprite OAM attribute words (attribute 0 and attribute 1) as viewed by the
 * scripted effect updates. */
struct EffectSpriteAttrs { u16 attr0; u16 attr1; };

/* Step-handler table installed by updateCameraRelativeEffect. */
#define EFFECT_VIEW_STEP_TABLE 0x0866DDD0

/* ---- Moving-object tile-collision update (updateObjectTileCollision) ---- */

/* The actor's +0x6C slot points at a scene block; scene+4 is the position/
 * motion body passed to setSpriteScreenPosition and the delay-timer helpers. */
struct TileCollisionScene {
    u8 _0[4];
    s32 coordX;        /* 0x04: world X, 16.16 */
    u8 _8[0x2C];
};

struct TileCollisionBody {
    u8 _0[4];
    s32 coordY;        /* 0x04: world Y, 16.16 */
    s32 offsetX;       /* 0x08: pending X motion */
    s32 offsetY;       /* 0x0C: pending Y motion */
    u8 _10[0x2C];
    void *effect;      /* 0x3C: effect whose +0x14 flags gate the extra spawn */
    u8 _40[8];
    s32 bounce;        /* 0x4C: collision bounce value */
};

struct TileCollisionEffect { u8 _0[0x14]; u16 flags; };

/* gMainWorkspace byte at +0x18A8 selects the current tilemap page. */
struct TilePageWorkspace { u8 _0[0x18A8]; u8 pageIndex; };

/* Payload installed on the hit timer and the kind spawned on a flagged hit. */
#define TILE_COLLISION_ANIM_DATA 0x08472AB0
#define TILE_COLLISION_EFFECT_KIND 8

/* Bounce written to the body on a tile hit, and the collision sound id. */
#define TILE_COLLISION_BOUNCE 0x4000
#define TILE_COLLISION_SFX 0x6F

/* Large actor effect sub-object (work slot 0x120, kind 0x67). The actor keeps
 * its script at +0x18 (2-byte steps, index at +0x22), its cleanup callback at
 * +0x24, the spawned sprite at +0x38 and the work state at +0x3C. The work
 * state stores its kind at +0x1C, the kind-table animation slot at +0x22, a
 * per-step part word at +0x48 and a 16-byte copy of the sprite's part byte at
 * +0x110. The spawned sprite takes its graphics id from the actor's +0x5C. */
#define LARGE_EFFECT_KIND            0x67
#define LARGE_EFFECT_WORK_SLOT_SIZE  0x120
#define LARGE_EFFECT_SPRITE_PART_OFFSET 0x2A
#define LARGE_EFFECT_PART_COPY_OFFSET 0x110
#define LARGE_EFFECT_PART_COPY_COUNT  16
#define LARGE_EFFECT_FRAME_SHIFT      6
#define LARGE_EFFECT_FRAME_BIAS       0x200
#define LARGE_EFFECT_FRAME_MASK       0xFC0
#define LARGE_EFFECT_ATTR1_FLAG       0x400
#define LARGE_EFFECT_SCRIPT_BASE      0x18
#define LARGE_EFFECT_STEP_INDEX_OFFSET 0x22
#define LARGE_EFFECT_ANIM_SEQUENCE    0x0841EB04

/* Workspace fields read by the scripted-motion entity updater. Offsets are
 * absolute from gMainWorkspace (0x02025FF0). */
struct MotionObjectWorkspace {
    u8 _0[0x10];
    s32 activeForm;        /* 0x10: nonzero while an active form is held */
    u8 _14[0x14ED-0x14];
    u8 actionState;        /* 0x14ED */
    u8 _14EE[0x173A-0x14EE];
    u8 sceneState;         /* 0x173A: 0x1C requests entity cleanup */
    u8 _173B[0x1754-0x173B];
    s32 formIndex;         /* 0x1754: raised to at least 9 on a motion hit */
    u8 _1758[0x18A8-0x1758];
    u8 frameCounter;       /* 0x18A8: indexes the tilemap page table */
    u8 _18A9[0x19];
    u16 gfxFlags;          /* 0x18C2: copied to sprite OAM attribute 0 */
};

/* Phase, terrain and effect constants used by the scripted-motion updater. */
#define MOTION_OBJ_PHASE_STEP      0x4000       /* per-frame phase increment */
#define MOTION_OBJ_PHASE_MAX       0x80000      /* phase clamp */
#define MOTION_OBJ_TILEMAP_BASE    0x02023130   /* base of gTilemapPages */
#define MOTION_OBJ_HIT_FORM_BASE   8            /* formIndex values <= this are raised */
#define MOTION_OBJ_HIT_FORM_MIN    9            /* formIndex floor after a hit */
#define MOTION_OBJ_HIT_ANIM        8            /* animation fields set on a hit */
#define MOTION_OBJ_HIT_SFX         0x142        /* playSound id on a hit */
#define MOTION_OBJ_CLEANUP_SCENE   0x1C         /* sceneState that releases the entity */
#define MOTION_OBJ_HIT_EFFECT_DATA 0x084D8DF4   /* timer payload of the hit effect */

/* Five-way menu selection state at gMenuState. */
struct MenuSelectionState {
    u8 _0[0x64];
    u8 chosenValue;    /* 0x64: value chosen for the highlighted option */
    u8 _65[3];
    s8 selection;      /* 0x68: highlighted option, wraps over 0..MENU_SELECTION_MAX */
};

/* Pressed-button words at gCameraState. */
struct MenuInputCameraState {
    u8 _0[0x146C];
    u16 actionButtons; /* 0x146C: A/B/Start pressed this frame */
    u8 _146E[2];
    u16 dirButtons;    /* 0x1470: directions pressed this frame */
};

#define MENU_SELECTION_MAX      4     /* highest selectable menu option */
#define MENU_INPUT_CANCEL_ANY   0x00A /* B or Start cancels the selection */
#define MENU_CURSOR_TILE_ROW    2     /* VRAM tile row redrawn for the cursor */
#define MENU_CURSOR_FILL_SIZE   0xFC0 /* bytes cleared for that tile */
#define MENU_SCRIPT_CMD_CANCEL  0x10  /* script command id sent on cancel */
#define MENU_SCRIPT_CMD_CONFIRM 0xE   /* script command id sent on confirm */

/* Five-way selection menu (handleMenuSelectionInput): the cursor wraps over
 * indices 0..FIVEWAY_MENU_MAX_INDEX, the two held bits in
 * FIVEWAY_MENU_CANCEL_BITS close the screen, and a change redraws one tile
 * row of the menu icon. The step timer byte sits just before the step stream. */
#define FIVEWAY_MENU_MAX_INDEX   4
#define FIVEWAY_MENU_CANCEL_BITS 0xA
#define FIVEWAY_MENU_TILE_ROW    2
#define FIVEWAY_MENU_TILE_SIZE   0xFC0
#define FIVEWAY_STEP_TIMER_OFF   0x17
#define FIVEWAY_MENU_CANCEL_CMD  0x10
#define FIVEWAY_MENU_CONFIRM_CMD 0xE

/* Hovering-effect step (updateHoveringEffectStep): field views and tunables.
 * The script object holds its sprite at +0x38 and a work state at +0x3C. In
 * the work state +0x02 bit 1 reverses X velocity, +0x08/+0x0C are 16.16 world
 * coordinates, +0x10 is X velocity, +0x34 an animation track, and +0x48 a
 * motion block whose +0x02/+0x04 are velocity/facing countdowns. The focus
 * coordinates live in gMainWorkspace; step callbacks are dispatched through
 * the _call_via_r3 thunk with a callback from SCRIPT_STEP_CALLBACK_TABLE. */
struct MainWorkspaceView {
    u8 _0[0x174C];
    s32 targetX; /* 0x174C: focus X, 16.16 */
    s32 targetY; /* 0x1750: focus Y, 16.16 */
};

#define HOVER_FACING_TIMER_SPAN  0x3D       /* random span for facing-timer reload */
#define HOVER_FACING_TIMER_BASE  0x5A       /* base delay for facing-timer reload */
#define HOVER_FLIP_MIN_DELAY     0x5A       /* min delay passed to updateFacingFlipTimer */
#define HOVER_FLIP_MAX_DELAY     0x78       /* max delay passed to updateFacingFlipTimer */
#define HOVER_END_DISTANCE       0x600000   /* |worldX/Y - focus| that ends the step */
#define HOVER_WORK_FLAG_REVERSE  2          /* work+0x02 bit: reverse X velocity */
#define HOVER_FAR_X_DISTANCE     0x400000   /* |worldX - focus| that selects the long delay */
#define HOVER_VEL_SHORT_SPAN     0x0B        /* short velocity-delay random span */
#define HOVER_VEL_SHORT_BASE     0x1E        /* short velocity-delay base */
#define HOVER_VEL_LONG_SPAN      0x06        /* long velocity-delay random span */
#define HOVER_VEL_LONG_BASE      0x0A        /* long velocity-delay base */

/* Virtual-input flag word at gCrossfadeGfxState[0]: two direction bits derived
 * from the raw coordinate pairs at gCameraState+0x1460..0x1467. The remaining
 * fields of that u16 array hold the two coordinate pairs (indices 5..8), the
 * 16-bit id (index 9) and the pressure byte (index 10). */
#define VIRTUAL_INPUT_FLAG_A       0x2000  /* 0x80 << 6, from the even pair */
#define VIRTUAL_INPUT_FLAG_B       0x4000  /* 0x80 << 7, from the odd pair */
#define VIRTUAL_INPUT_FLAG_A_CLEAR 0xDFFF  /* ~VIRTUAL_INPUT_FLAG_A */
#define VIRTUAL_INPUT_FLAG_B_CLEAR 0xBFFF  /* ~VIRTUAL_INPUT_FLAG_B */

/* Step records of a scripted attack: the s16 step index at script+0x22 selects
 * two-byte records at script+0x18 (opcode byte then timer byte). The next two
 * bytes hold a "already active" flag and a "cleared on hit" flag. The attacker
 * is re-anchored each frame by subtracting the current room's scroll row. */
#define ATTACK_STEP_STRIDE      2
#define ATTACK_STEP_TIMER_OFF   0x19
#define ATTACK_STEP_FLAG_A_OFF  0x1A
#define ATTACK_STEP_FLAG_B_OFF  0x1B
#define ATTACK_ROOM_COUNTER_OFF 0x18A8  /* gMainWorkspace frame/room index */
#define ATTACK_SCROLL_STRIDE    0x40    /* bytes per scroll row */
#define ATTACK_SCROLL_X_OFF     0x1278  /* gCameraState room scroll X */
#define ATTACK_SCROLL_Y_OFF     0x127C  /* gCameraState room scroll Y */
#define ATTACK_SCROLL_BIAS_X    0x8000
#define ATTACK_SCROLL_BIAS_Y    0xFFFF8000
#define ATTACK_SCROLL_FRAC_MASK 0xFFFF0000

/* Alternate room-anchored scripted attack (updateRoomAnchoredScriptedAttackAlt).
 * It shares the 2-byte step stream and per-step flag bytes of
 * updateRoomAnchoredScriptedAttack, but its attack-state block is shifted by
 * four bytes: fixed-point world X/Y at +0x04/+0x08, collision target at +0x10
 * and animation track at +0x14. gScriptedAttackCmdTableAlt (0x0866F9A0) holds
 * its 4-byte script-command handler pointers. */
