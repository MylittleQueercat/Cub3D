#include "cub3d.h"

int collide_sprite_at(t_club *club, double nx, double ny)
{
    const double pr = 0.25; // 玩家半径：0.20~0.25
    int i;

    if (!club->sprites || club->sprite_count <= 0)
        return (0);

    i = 0;
    while (i < club->sprite_count)
    {
        t_sprite *s = &club->sprites[i];
        double dx = nx - s->x;
        double dy = ny - s->y;
        double r = pr + s->radius + 0.04; // 0.02 缓冲

        if (dx * dx + dy * dy < r * r)
            return (1);
        i++;
    }
    return (0);
}

