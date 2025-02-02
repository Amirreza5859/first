bool is_valid(int x, int y, Map *map)
{
    chtype ch = mvinch(y, x) & A_CHARTEXT;
    chtype ch1 = mvinch(y - 1, x) & A_CHARTEXT;
    chtype ch2 = mvinch(y + 1, x) & A_CHARTEXT;
    chtype ch3 = mvinch(y, x - 1) & A_CHARTEXT;
    chtype ch4 = mvinch(y, x + 1) & A_CHARTEXT;
    chtype ch5 = mvinch(y - 1, x - 1) & A_CHARTEXT;
    chtype ch6 = mvinch(y + 1, x + 1) & A_CHARTEXT;
    chtype ch7 = mvinch(y + 1, x - 1) & A_CHARTEXT;
    chtype ch8 = mvinch(y - 1, x + 1) & A_CHARTEXT;
    if (
        ch1 == '#' || ch2 == '#' || ch3 == '#' || ch4 == '#' ||
        ch5 == '#' || ch6 == '#' || ch7 == '#' || ch8 == '#'
    )
    {
        return false;
    }
    return x >= 0 && x < COLS && y >= 3 && y < LINES - 3 && (ch == ' ' || ch == '+');
}

void connect_rooms(Point door1, Point door2, Map *map, Corridor *corridor)
{
    int dx[] = {0, 0, 1, -1};
    int dy[] = {-1, 1, 0, 0};

    bool visited[MAX_MAPS_LEN][MAX_MAPS_LEN] = {{false}};
    Point queue[MAX_QUEUE_SIZE];
    Point prev[MAX_MAPS_LEN][MAX_MAPS_LEN];

    int front = 0, rear = 0;
    queue[rear++] = door1;
    visited[door1.y][door1.x] = true;

    for (int i = 0; i < MAX_MAPS_LEN; i++)
    {
        for (int j = 0; j < MAX_MAPS_LEN; j++)
        {
            prev[i][j] = (Point){-1, -1};
        }
    }

    while (front < rear)
    {
        Point current = queue[front++];

        if (current.x == door2.x && current.y == door2.y)
        {
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            Point point = (Point){nx, ny};

            if (is_valid(nx, ny, map) && !visited[ny][nx])
            {
                visited[ny][nx] = true;
                queue[rear++] = (Point){nx, ny};
                prev[ny][nx] = current;

                if (rear >= MAX_QUEUE_SIZE)
                {
                    break;
                }
            }
        }
    }

    Point p = door2;
    int count = 0;

    while (!(p.x == door1.x && p.y == door1.y))
    {
        if (count >= MAX_MAPS_LEN * MAX_MAPS_LEN)
        {
            break;
        }

        corridor->blocks[count] = p;
        corridor->blocks[count].is_reveald = false;
        count++;
        p = prev[p.y][p.x];
    }

    if (count < MAX_MAPS_LEN * MAX_MAPS_LEN)
    {
        corridor->blocks[count++] = door1;
    }

    corridor->block_count = count;
    corridor->is_reveald = false;
}

void connect_rooms(Room *room1, Room *room2, Map *map, Corridor *corridor)
{
    int dx[] = {0, 0, 1, -1}; 
    int dy[] = {-1, 1, 0, 0};

    bool visited[MAX_MAPS_LEN][MAX_MAPS_LEN] = {false};
    Point queue[MAX_QUEUE_SIZE];
    Point prev[MAX_MAPS_LEN][MAX_MAPS_LEN];

    int front = 0, rear = 0;

    Point door1 = {room1->x1, room1->y1};
    Point door2 = {room2->x2, room2->y2};

    queue[rear++] = door1;
    visited[door1.y][door1.x] = true;

    for (int i = 0; i < MAX_MAPS_LEN; i++)
        for (int j = 0; j < MAX_MAPS_LEN; j++)
            prev[i][j] = (Point){-1, -1};

    bool path_found = false;
    while (front < rear)
    {
        Point current = queue[front++];

        if (current.x == door2.x && current.y == door2.y)
        {
            path_found = true;
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (is_valid(nx, ny, map) && !visited[ny][nx])
            {
                visited[ny][nx] = true;
                queue[rear++] = (Point){nx, ny};
                prev[ny][nx] = current;

                if (rear >= MAX_QUEUE_SIZE)
                    break;
            }
        }
    }

    if (!path_found)
    {
        return;
    }

    Point p = door2;
    int count = 0;

    while (!(p.x == door1.x && p.y == door1.y))
    {
        if (count >= MAX_MAPS_LEN * MAX_MAPS_LEN)
            break;

        corridor->blocks[count] = p;
        corridor->blocks[count].is_reveald = false;
        count++;
        p = prev[p.y][p.x];
    }

    if (count < MAX_MAPS_LEN * MAX_MAPS_LEN)
        corridor->blocks[count++] = door1;

    corridor->block_count = count;
    corridor->is_reveald = false;
}
