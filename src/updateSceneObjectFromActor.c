/* Keep a layer's scene object in sync with an actor: copy its position, set
 * the layer's flip flag, pass the state byte to both children, fire the
 * state-change callback, and refresh the layer's camera scroll entry. */
void postDisplaySprite(s32, s32, s32, s32, s32);
void spawnSceneObjectTableEntries(void *);

extern struct SceneWorkspace gMainWorkspace;
extern u8 gCameraState[];

void updateSceneObjectFromActor(struct SceneObjectFlags *spriteFlags,
                                struct SceneObjectPosition *actor,
                                struct SceneObject *obj) {
    u32 t;
    s32 idx;

    obj->posX = actor->x;
    obj->posY = actor->y;

    if (obj->state == -1)
        spriteFlags->flags &= SCENE_OBJ_FLIP_CLEAR;
    else
        spriteFlags->flags |= SCENE_OBJ_FLIP_X;

    if (obj->childA != NULL)
        ((struct SceneObjectChildState *)obj->childA)->state = obj->stateByte;
    if (obj->childB != NULL)
        ((struct SceneObjectChildState *)obj->childB)->state = obj->stateByte;

    if (obj->stateByte != 0) {
        u8 *base = gCameraState;
        ((struct SceneLayerFlags *)(base + (obj->layer << SCENE_LAYER_SHIFT)))->recs[0].flag |= SCENE_LAYER_FLAG;
        return;
    }
    {
        u8 *base = gCameraState;
        ((struct SceneLayerFlags *)(base + (obj->layer << SCENE_LAYER_SHIFT)))->recs[0].flag &= SCENE_LAYER_FLAG_CLEAR;
    }

    {
        s8 state = obj->state;
        if (state != obj->prevState) {
            t = (u32)~state;
            idx = (((0u - t) | t) >> 31) << 2;
            {
                u8 *callbackWords = (u8 *)obj + 4;
                idx = *(s32 *)(callbackWords + idx);
            }
            if (idx != 0 && obj->callback != NULL) {
                postDisplaySprite(1, idx, (s32)obj->callback, 0x400, 0x10);
            }
            spawnSceneObjectTableEntries(obj);
        }
    }
    *(u8 *)((u8 *)obj + 0x29) = *(u8 *)((u8 *)obj + 0x35);

    ((struct SceneLayerEntries *)gCameraState)->entries[obj->layer].x =
        (((struct SceneLayerEntries *)gCameraState)->entries[gMainWorkspace.activeLayer + 1].x + SCENE_SCROLL_X_ROUND & SCENE_SCROLL_FRAC_MASK) - obj->posX + SCENE_SCROLL_BIAS;
    ((struct SceneLayerEntries *)gCameraState)->entries[obj->layer].y =
        (((struct SceneLayerEntries *)gCameraState)->entries[gMainWorkspace.activeLayer + 1].y + SCENE_SCROLL_Y_ROUND & SCENE_SCROLL_FRAC_MASK) - obj->posY + SCENE_SCROLL_BIAS;
}
