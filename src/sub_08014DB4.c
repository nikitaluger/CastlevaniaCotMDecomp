s32 sub_08005910(s32, s32);
void sub_080146D0(void *, s32, s32);

/* Bounded follow/turn controller state. */
struct FollowPath {
    s32 position;     /* 0x00, current coordinate */
    s32 angle;        /* 0x04, current heading */
    s32 minPos;       /* 0x08 */
    s32 maxPos;       /* 0x0C */
    s32 speed;        /* 0x10, movement per frame */
    s32 maxTurn;      /* 0x14, maximum heading change */
    u16 dirFlags;     /* 0x18 */
    u16 controlFlags; /* 0x1A */
    s32 timeLimit;    /* 0x1C */
    s32 travelLimit;  /* 0x20 */
    s32 timer;        /* 0x24 */
    s32 travel;       /* 0x28, distance accumulated */
};

/* Advance a bounded follow controller toward a target point: apply any
   requested linear motion, check turn/travel limits, rotate toward the target
   heading and push the resulting heading/position to the entity. */
void sub_08014DB4(u8 *arg0, struct FollowPath *p, s32 targetX, s32 targetY) {
    s32 canMove = 1;
    s32 targetAngle;
    s32 angleDelta;
    s32 absDelta;
    s32 turnStep;
    s32 newTravel;
    s32 signedDelta;

    if (p->controlFlags & 1)
    {
        s32 x = p->position + p->speed;
        p->position = x;
        if (x > p->maxPos)
        {
            p->position = p->maxPos;
        }
    }
    if (p->controlFlags & 2)
    {
        s32 x = p->position - p->speed;
        p->position = x;
        if (x < p->minPos)
        {
            p->position = p->minPos;
        }
    }
    targetAngle = sub_08005910(targetY - (*((s32 *) (arg0 + 0xC))), targetX - (*((s32 *) (arg0 + 8))));
    angleDelta = (u16) (targetAngle - p->angle);
    if (p->controlFlags & 4)
    {
        if ((p->dirFlags & 1) && (((s32) (angleDelta << 16)) < 0))
        {
            canMove = 0;
        }
        if ((p->dirFlags & 2) && (((s32) (angleDelta << 16)) > 0))
        {
            canMove = 0;
        }
    }
    if ((8 & p->controlFlags) && (p->timer >= p->timeLimit))
    {
        canMove = 0;
        p->dirFlags = (u16) (p->dirFlags | 4);
    }
    if ((0x10 & p->controlFlags) && (p->travel >= p->travelLimit))
    {
        canMove = 0;
        p->dirFlags = (u16) (p->dirFlags | 8);
    }
    if (canMove == 1)
    {
        s32 delta16;
        signedDelta = angleDelta << 16;
        if ((signedDelta >> 16) < 0)
        {
            p->dirFlags = (u16) ((p->dirFlags & 0xFFFE) | 2);
        }
        else
          if ((signedDelta >> 16) > 0)
        {
            p->dirFlags = (u16) ((p->dirFlags & 0xFFFD) | 1);
        }
        delta16 = (s16)angleDelta;
        absDelta = (delta16 < 0) ? (-delta16) : delta16;
        turnStep = p->maxTurn;
        if (absDelta <= turnStep)
        {
            p->angle = targetAngle;
            absDelta = (delta16 < 0) ? (-delta16) : delta16;
            newTravel = p->travel + absDelta;
        }
        else
        {
            p->angle = ((delta16 < 0) ? (p->angle - turnStep) : (p->angle + turnStep)) & 0xFFFF;
            newTravel = p->travel + turnStep;
        }
        p->travel = newTravel;
    }
    p->timer = p->timer + 1;
    sub_080146D0(arg0, p->angle, turnStep = p->position);
}
