s32 getAngleFromDelta(s32, s32);
void setPolarOffset(void *, s32, s32);

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

/* Steer a bounded follow path toward a target point: move within its position
 * limits, turn by at most maxTurn, accumulate travel, then store the resulting
 * heading and position on the entity as cartesian offsets. */
void updateFollowPath(u8 *entity, struct FollowPath *path, s32 targetX, s32 targetY) {
    s32 canMove = 1;
    s32 targetAngle;
    s32 angleDelta;
    s32 absDelta;
    s32 turnStep;
    s32 newTravel;
    s32 signedDelta;

    if (path->controlFlags & FOLLOW_CTRL_MOVE_FORWARD)
    {
        s32 x = path->position + path->speed;
        path->position = x;
        if (x > path->maxPos)
        {
            path->position = path->maxPos;
        }
    }
    if (path->controlFlags & FOLLOW_CTRL_MOVE_BACKWARD)
    {
        s32 x = path->position - path->speed;
        path->position = x;
        if (x < path->minPos)
        {
            path->position = path->minPos;
        }
    }
    targetAngle = getAngleFromDelta(targetY - (*((s32 *) (entity + 0xC))), targetX - (*((s32 *) (entity + 8))));
    angleDelta = (u16) (targetAngle - path->angle);
    if (path->controlFlags & FOLLOW_CTRL_CHECK_DIR)
    {
        if ((path->dirFlags & FOLLOW_DIR_NEGATIVE) && (((s32) (angleDelta << 16)) < 0))
        {
            canMove = 0;
        }
        if ((path->dirFlags & FOLLOW_DIR_POSITIVE) && (((s32) (angleDelta << 16)) > 0))
        {
            canMove = 0;
        }
    }
    if ((FOLLOW_CTRL_CHECK_TIME & path->controlFlags) && (path->timer >= path->timeLimit))
    {
        canMove = 0;
        path->dirFlags = (u16) (path->dirFlags | FOLLOW_DIR_TURN_LIMIT);
    }
    if ((FOLLOW_CTRL_CHECK_TRAVEL & path->controlFlags) && (path->travel >= path->travelLimit))
    {
        canMove = 0;
        path->dirFlags = (u16) (path->dirFlags | FOLLOW_DIR_TRAVEL_LIMIT);
    }
    if (canMove == 1)
    {
        s32 delta16;
        signedDelta = angleDelta << 16;
        if ((signedDelta >> 16) < 0)
        {
            path->dirFlags = (u16) ((path->dirFlags & 0xFFFE) | FOLLOW_DIR_POSITIVE);
        }
        else
          if ((signedDelta >> 16) > 0)
        {
            path->dirFlags = (u16) ((path->dirFlags & 0xFFFD) | FOLLOW_DIR_NEGATIVE);
        }
        delta16 = (s16)angleDelta;
        absDelta = (delta16 < 0) ? (-delta16) : delta16;
        turnStep = path->maxTurn;
        if (absDelta <= turnStep)
        {
            path->angle = targetAngle;
            absDelta = (delta16 < 0) ? (-delta16) : delta16;
            newTravel = path->travel + absDelta;
        }
        else
        {
            path->angle = ((delta16 < 0) ? (path->angle - turnStep) : (path->angle + turnStep)) & 0xFFFF;
            newTravel = path->travel + turnStep;
        }
        path->travel = newTravel;
    }
    path->timer = path->timer + 1;
    setPolarOffset(entity, path->angle, turnStep = path->position);
}
