extern s32 sub_0805F9B4(s32, s32);
extern void sub_080113A8(void *, void *);
extern void sub_080C31E0(void *, s32);
extern u8 D_02021E90[];
extern u8 D_02025FF0[];

/* Flag byte at actor + 0x2A. */
struct ActorFlag { u8 flag; };

/*
 * Updates a scripted task: reflects a hit into the actor's flag, dispatches
 * the current step's handler from D_0866F9D0, then syncs the actor's position
 * to the subject with the camera/scroll correction.
 */
void sub_0809209C(u8 *task) {
    u32 mask32;
    u8 *actor;
    u8 *subject;
    u8 *subjectState;
    s32 hit;
    u8 *stepState;
    u8 *coords;
    u8 *coordBase;
    u8 *camera;
    u32 coordIndex;
    u32 coordX;
    u32 coordY;
    u32 handlerIndex;
    u8 *stateEntry;
    s32 stepOffset;
    u8 *component;

    actor = *((u8 **) (task + 0x38));
    subject = *((u8 **) (task + 0x3C));
    subjectState = subject + 0x24;
    hit = sub_0805F9B4(*((s32 *) (subject + 0x04)), *((s32 *) (subject + 0x08)));
    if (hit == 1) {
        ((struct ActorFlag *) (actor + 0x2A))->flag = 0xBF & ((struct ActorFlag *) (actor + 0x2A))->flag;
    } else {
        ((struct ActorFlag *) (actor + 0x2A))->flag |= 0x40;
    }
 do {
    component = *((u8 **) (subject + 0x1C));
    mask32 = 0xFFFF0000;
    *((u16 *) (component + 0x06)) = *((u16 *) (subject + 0x12));
    *((u32 *) (subject + 0x14)) = *((u32 *) (subject + 0x10));
    *((u32 *) (task + 0x14)) = 0x0866F9D0;
    *((u16 *) (task + 0x22)) = (*((u16 *) (task + 0x22))) + 1;
    stepState = (u8 *) ((((u32) (*((s16 *) (task + 0x22)))) * 2) + ((u32) task));
    *((u8 *) (stepState + 0x19)) = (*((u8 *) (stepState + 0x19))) + 1;
    stepOffset = (*((s16 *) (task + 0x22))) * 2;
    stateEntry = task;
    stateEntry += 0x18;
    handlerIndex = *((u8 *) (((u32) stateEntry) + ((u32) stepOffset)));
 } while (0);
    sub_080C31E0(task, *((u32 *) ((*((u32 *) (task + 0x14))) + (handlerIndex * 4))));
    *((u16 *) (task + 0x22)) = (*((u16 *) (task + 0x22))) - 1;
    if ((*((u16 *) (task + 2))) & 0x8000) return;
    if ((*((s16 *) (subject + 0x0C))) == 1) {
        sub_080113A8(actor, subjectState);
    }
    coords = D_02021E90;
    camera = D_02025FF0;
    camera += 0x18A8;
    coordIndex = (((u32) (*camera)) + 1) * 0x40;
    coordBase = coords + 0x1278;
    coordX = *((u32 *) (coordBase + coordIndex));
    *((u32 *) (actor + 0x14)) = (*((u32 *) (subject + 0x04))) - ((coordX + 0x8000) & mask32);
    coordIndex = (((u32) (*camera)) + 1) * 0x40;
    coords += 0x127C;
    coordY = *((u32 *) (coords + coordIndex));
    *((u32 *) (actor + 0x18)) = (*((u32 *) (subject + 0x08))) - ((coordY + 0xFFFF8000) & mask32);
}
