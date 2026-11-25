/* Main object driving this effect spawn. */
struct MainObj {
    u8 _00[0x14];
    u32 scriptTable;    /* 0x14 */
    u8 _18[0x0A];
    s16 index;          /* 0x22 */
    u32 updateCb;       /* 0x24 */
    u8 _28[0x10];
    u32 target;         /* 0x38 */
    u8 _3C[0x30];
    u32 state;          /* 0x6C */
    u8 _70[0x0C];
    u32 kindA;          /* 0x7C */
    u8 _80[0x0C];
    u32 kindB;          /* 0x8C */
};

/* Graphics/animation descriptor allocated by sub_08016190. */
struct GfxDesc {
    u8 _00;
    u8 type;            /* 0x01 */
    u8 layer;           /* 0x02 */
    u8 priority;        /* 0x03 */
    u16 gfxIndex;       /* 0x04 */
    u16 anim0, anim1, anim2, anim3, anim4; /* 0x06..0x0E */
    u32 object;         /* 0x10 */
    u8 _14[0x02];
    u16 flag;           /* 0x16 */
    u16 id;             /* 0x18 */
};

/* Mutable state of the spawned effect (stateHeader+4). */
struct EffectState {
    u32 copy0;          /* 0x00 */
    u32 copy1;          /* 0x04 */
    u32 f08;
    u32 f0C;
    u32 f10;
    u8 _14[0x04];
    u32 updateCb;       /* 0x18 */
    u8 _1C[0x10];
    struct GfxDesc *gfx; /* 0x2C */
    u32 counter0;       /* 0x30 */
    u32 counter1;       /* 0x34 */
    u32 counter2;       /* 0x38 */
    u32 counter3;       /* 0x3C */
    u8 _40[0x08];
    u32 f48;            /* 0x48 */
    u32 source;         /* 0x4C */
};

/* Header of the spawned effect, referenced by the main object at +0x6C. */
struct EffectHeader {
    u8 _00[0x04];
    u32 kindA;          /* 0x04 */
    u8 _08[0x18];
    u32 f20;            /* 0x20 */
};

/* Object referenced by the main object at +0x38. */
struct Target {
    u8 _00[0x04];
    u16 scaleX;         /* 0x04 */
    u16 scaleY;         /* 0x06 */
    u16 rotation;       /* 0x08 */
    u8 _0A[0x1A];
    u32 scriptAddr;     /* 0x24 */
};

extern u8 D_02025368[];

void sub_08003A6C(u32, u32, u32);
void *sub_08016190(void);
void sub_0806D2D0(void *);
u16 sub_0806D62C(u16, u32);
void sub_080C31E4(u32, u32, u32);
void sub_080C31E0(u32, u32);
extern void sub_0808449C(void);

/* Spawn a large scaled effect driven by another entity: allocate a graphics
   descriptor, initialise the effect state from the source object and script,
   then dispatch the current state's handler. */
void sub_08074520(struct MainObj *arg0) {
    struct EffectHeader *stateHeader = (struct EffectHeader *)arg0->state;
    struct EffectState *state = (struct EffectState *)((u8 *)stateHeader + 4);
    struct Target *target = (struct Target *)arg0->target;
    struct GfxDesc *gfx;
    u32 zero;
    u32 kindBValue;
    u8 *data = D_02025368;
    u8 *scriptPtr;
    u8 *source;
    u32 *cmdTable;

    gfx = (struct GfxDesc *)sub_08016190();
    state->gfx = gfx;
    if (gfx == 0) {
        sub_0806D2D0(arg0);
        return;
    }
    zero = 0;
    state->counter0 = zero;
    state->counter1 = zero;
    state->counter2 = zero;
    state->counter3 = zero;
    gfx->type = zero;
    state->gfx->layer = 2;
    state->gfx->priority = 8;
    state->gfx->gfxIndex = *(u8 *)(data + (0xC1 << 2));
    state->gfx->anim0 = 0x10;
    state->gfx->anim1 = 0x10;
    state->gfx->anim2 = zero;
    state->gfx->anim3 = zero;
    state->gfx->anim4 = sub_0806D62C(*(u16 *)(data + 0x2E2), 0x16);
    state->gfx->flag = 5;
    state->gfx->id = 0x2B;
    state->gfx->object = (u32)target;
    state->updateCb = arg0->updateCb;
    arg0->updateCb = (u32)&sub_0808449C;
    target->scriptAddr = 0x08499408;
    sub_08003A6C((u32)((u8 *)stateHeader + 0x20), 0, 0x08499690);
    target->scaleX = 0x400;
    target->scaleY = 0x400;
    target->rotation = zero;
    state->source = arg0->kindA;
    kindBValue = *(u32 *)((u8 *)arg0 + 0x8C);
    *(u8 *)((u8 *)stateHeader + 0x54) = kindBValue;
    source = (u8 *)state->source;
    *(u32 *)((u8 *)stateHeader + 4) = *(u32 *)(source + 0xC);
    state->copy1 = *(u32 *)(source + 0x10);
    state->f10 = 0x12C;
    *(u8 *)((u8 *)arg0 + (s16)arg0->index * 2 + 0x19) = zero;
    cmdTable = (u32 *)0x08671BB0;
    scriptPtr = (u8 *)arg0 + 0x18;
    sub_080C31E4((u32)scriptPtr, (u32)((u8 *)arg0 + 0x22), *cmdTable);
    {
        u8 *bytePtr = (u8 *)((s16)arg0->index * 2 + (u32)arg0) + 0x19;
        *bytePtr = *bytePtr + 1;
    }
    scriptPtr += (s16)arg0->index * 2;
    sub_080C31E0((u32)arg0, *(u32 *)((u32)arg0->scriptTable + *(u8 *)scriptPtr * 4));
}
