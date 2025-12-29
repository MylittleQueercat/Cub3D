#include "cub3d.h"

static int  is_sprite_char(char c)
{
    return (c == '2' || c == '3' || c == '4' || c == '5');
}

int  count_sprites_all(char **map)
{
    int x = 0;
    int y = 0;
    int count = 0;

    if (!map)
        return (0);
    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (is_sprite_char(map[y][x]))
                count++;
            x++;
        }
        y++;
    }
    return (count);
}

int collide_sprite_at(t_club *club, double nx, double ny)
{
    const double pr = 0.25;
    int i;

    if (!club->sprites || club->sprite_count <= 0)
        return (0);

    i = 0;
    while (i < club->sprite_count)
    {
        t_sprite *s = &club->sprites[i];
        double dx = nx - s->x;
        double dy = ny - s->y;
        double r = pr + s->radius + 0.04;

        if (dx * dx + dy * dy < r * r)
            return (1);
        i++;
    }
    return (0);
}

