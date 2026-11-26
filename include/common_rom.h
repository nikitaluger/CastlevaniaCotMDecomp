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



