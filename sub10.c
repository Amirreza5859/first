
typedef struct {
    int x,y;
    int xx,yy;          
    int locked;    
    char code[5];       
    int attempts;       
} PasswordDoor;

PasswordDoor password_doors[3];
int password_door_count_global = 0;

int check_door_collision(PasswordDoor new_door){
    int y = new_door.y;
    int x = new_door.x;
    if(map[y][x] == '+' && map[y][x + 1] == '*' && map[y][x - 1] == '*'){
        return 1;
    }
    return 0;
}

void generate_password_door(){
    int password_door_count = 0;
    while (password_door_count < 3){
    PasswordDoor new_door;

    new_door.x = rand() % WIDTH;
    new_door.y = rand() % HEIGHT;
    new_door.locked = 1;
    new_door.attempts = 0;

        if (check_door_collision(new_door)){
            map[new_door.y][new_door.x] = '@';
            password_doors[password_door_count] = new_door;
            (password_door_count)++;
            
        }
    }
    password_door_count_global = password_door_count;
}

void password_door_print() {
    for (int i = 0; i < password_door_count_global; i++) {

        int y = password_doors[i].y;
        int x = password_doors[i].x;

        if (password_doors[i].locked) {
            attron(COLOR_PAIR(1)); 
            mvaddch(y, x, '@');
            attroff(COLOR_PAIR(1));
        } 
        
        else {
            attron(COLOR_PAIR(2));
            mvaddch(y, x, '@');
            attroff(COLOR_PAIR(2));
        }
    }
}

void generate_button_print() {

    for (int i = 0; i < password_door_count_global; i++) {

        int number_room = near_room(password_doors[i].x,password_doors[i].y,room_count_global);
    
        int y = rooms[number_room].y;
        int x = rooms[number_room].x;

        password_doors[i].xx = x;
        password_doors[i].yy = y;

            attron(COLOR_PAIR(4));
            mvaddch(y, x, '&');  
            attroff(COLOR_PAIR(4));
    }
}

void generate_random_password(char *password) {

    for (int i = 0; i < 4; i++) {
        password[i] = '1' + rand() % 9;
    }
    password[4] = '\0';
}

void check_key_press(int player_x, int player_y) {

    for (int i = 0; i < password_door_count_global; i++) {
        if (password_doors[i].xx == player_x && password_doors[i].yy == player_y) {
            mvprintw(0,0,"please enter 'e' to make password");

            int ch = getch();
            if (ch == 'e' || ch == 'E') { 
                generate_random_password(password_doors[i].code);
                mvprintw(0,0,"%s",password_doors[i].code);
                password_doors[i].locked = 0;
            }
        }
    }
}
