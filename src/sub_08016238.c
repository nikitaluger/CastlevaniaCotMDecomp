extern struct Ent *D_020202B0;
extern struct Ent *D_020202AC;
extern struct Ent *D_020202A8;

struct Ent {
    u8 flags00;          /* bit 0x40: active / collidable */
    u8 pad01;
    u8 attackCat;        /* attacker's hit-category mask */
    u8 vulnerableCat;    /* target's hit-category mask */
    u16 flags04;         /* bit 0x200: also set the secondary hit flag */
    u8 _p06[0x0A];
    void *owner;         /* source/owner; equal owners never collide */
    u16 status;          /* bit 0: hit, bit 1: secondary */
    u8 _p16[0x0A];
    struct Ent *next;
    u8 flags24;          /* bit 4: can deal a hit, bit 1: can be hit */
    u8 _p25;
    s16 radiusX;         /* half-width for the overlap test */
    s16 radiusY;         /* half-height for the overlap test */
    u8 _p2A[6];
    s16 posX;
    s16 posY;
};

/* Scan the collision list for the first entity the attacker overlaps, unlink
 * it, set its hit flags and return it; return 0 when nothing is hit. */
struct Ent *sub_08016238(struct Ent *attacker) {
    struct Ent *candidate;
    struct Ent **listLink;
    s32 dist;
    u16 hitFlags;

    if (!(attacker->flags24 & 4))
        return 0;
    if (!(attacker->flags00 & 0x40))
        return 0;
    if (attacker == D_020202B0) {
        candidate = D_020202AC;
        listLink = &D_020202AC;
    } else {
        candidate = D_020202A8;
        D_020202B0 = attacker;
        listLink = &D_020202AC;
    }
    if (candidate == 0)
        goto clear;
    while (1) {
        if ((attacker->attackCat & candidate->vulnerableCat) && (1 & candidate->flags24) &&
            (attacker->owner != candidate->owner) && (candidate->flags00 & 0x40)) {
            dist = candidate->posX - attacker->posX;
            if (dist < 0) dist = -dist;
            if (dist < (s32)(candidate->radiusX + attacker->radiusX)) {
                dist = candidate->posY - attacker->posY;
                if (dist < 0) dist = -dist;
                if (dist < (s32)(candidate->radiusY + attacker->radiusY)) {
                    *listLink = candidate->next;
                    hitFlags = 1 | candidate->status;
                    candidate->status = hitFlags;
                    if (attacker->flags04 & 0x200) candidate->status = hitFlags | 2;
                    return candidate;
                }
            }
        }
        candidate = candidate->next;
        if (candidate == 0)
            goto clear;
    }

clear:
    *listLink = 0;
    return 0;
}
