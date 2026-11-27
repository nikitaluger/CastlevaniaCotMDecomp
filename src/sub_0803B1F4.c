void uploadPendingSpriteGraphic(void *self, void *owner);

struct EnemyAnim {
    u8 pad_00[0x28];
    void *anim;             /* current animation/sprite data (dirty flag at +0x14) */
};

struct AttachedParts {
    void *part[3];          /* attached objects (dirty flag at +0x14) */
};

/* Uploads the enemy's current graphic frame when its animation data or one of
 * its three attached parts has been marked dirty: uploadPendingSpriteGraphic clears the
 * request and does the copy, so at most one upload happens per call. */
void sub_0803B1F4(void *task, struct EnemyAnim *enemy, struct AttachedParts *parts) {
    uploadPendingSpriteGraphic(task, enemy->anim);
    uploadPendingSpriteGraphic(task, parts->part[0]);
    uploadPendingSpriteGraphic(task, parts->part[1]);
    uploadPendingSpriteGraphic(task, parts->part[2]);
}
