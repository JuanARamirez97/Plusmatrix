#include <iostream>
#include <string>
#include <curses.h>
#include <cstdlib>
#include <ctime>
#include <vector>

// Struct to map string names to ncurses color codes
struct ColorOption {
    std::string name;
    short code;
};

// Available colors vector
const std::vector<ColorOption> COLORS_AVAILABLE = {
    {"green", COLOR_GREEN},
    {"red", COLOR_RED},
    {"blue", COLOR_BLUE},
    {"cyan", COLOR_CYAN},
    {"magenta", COLOR_MAGENTA},
    {"yellow", COLOR_YELLOW},
    {"white", COLOR_WHITE}
};

// Struct to store the state of a single "drop" of characters
struct Drop {
    int x;       // Horizontal position
    int y;       // Vertical position (head)
    int length;  // Length of the drop's tail
    int speed;   // Speed threshold (higher is slower)
    int counter; // Frame counter to manage speed
};

// Function to initialize or reset the array of drops
void initDrops(std::vector<Drop>& drops, int maxX, int maxY) {
    drops.clear(); // Clear in case of terminal resize
    
    // Create drops spaced by 2 columns to prevent overlapping text
    for (int i = 0; i < maxX; i += 2) {
        Drop d;
        d.x = i;
        
        // Start slightly above the screen for a natural entry effect
        d.y = -(rand() % maxY); 
        d.length = (rand() % (maxY / 2)) + 5;
        d.speed = (rand() % 3) + 1; // Assign random speeds
        d.counter = 0;
        
        drops.push_back(d);
    }
}

int main(int argc, char* argv[]) {
    // Default Color is green
    short selectedColor = COLOR_GREEN;

    // Command line argument parsing
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        
        // Check if the user passed the -c (color) flag
        if (arg == "-c" && i + 1 < argc) {
            std::string colorArg = argv[i + 1];
            bool colorFound = false;
            
            // Look for the requested color in our struct
            for (const auto& colorOpt : COLORS_AVAILABLE) {
                if (colorOpt.name == colorArg) {
                    selectedColor = colorOpt.code;
                    colorFound = true;
                    break;
                }
            }
            
            // Handle invalid color inputs
            if (!colorFound) {
                std::cerr << "Invalid color: " << colorArg << "\n";
                std::cerr << "Available colors: green, red, blue, cyan, magenta, yellow, white\n";
                return 1; // Exit with error
            }
            i++; // Skip the color name argument
        }
    }

    // Initialize ncurses environment
    initscr();              // Start curses mode
    cbreak();               // Disable line buffering
    noecho();               // Don't echo pressed keys
    keypad(stdscr, TRUE);   // Enable special keys
    curs_set(0);            // Hide the cursor
    nodelay(stdscr, TRUE);  // Non-blocking input

    // Initialize colors if the terminal supports them
    if (has_colors()) {
        start_color();
        use_default_colors(); // Allows terminal transparency
        
        // Pair 1: Trail color. Pair 2: Head color (White)
        init_pair(1, selectedColor, -1);
        init_pair(2, COLOR_WHITE, -1);
    }

    // Seed for random number generation
    srand(time(0)); 

    // Get terminal dimensions
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    // Character set used for the matrix rain
    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}|;':\",./<>?\\~`";
    int charLen = (int)chars.size();

    // Create and initialize the drops
    std::vector<Drop> drops;
    initDrops(drops, maxX, maxY);

    int ch;
    // Main loop: breaks only if 'q' or 'Q' is pressed
    while ((ch = getch()) != 'q' && ch != 'Q') {
        
        // Handle window resize dynamically
        if (ch == KEY_RESIZE) {
            clear();                      // Clear visual garbage
            getmaxyx(stdscr, maxY, maxX); // Get new dimensions
            initDrops(drops, maxX, maxY); // Reinitialize drops
            continue;                     // Skip frame to avoid OOB draws
        }

        // Process and draw each drop
        for (auto& drop : drops) {
            drop.counter++;

            // Move the drop only if its counter reaches its speed threshold
            if (drop.counter >= drop.speed) {
                drop.counter = 0;

                // Erase the tail (last character of the drop)
                int tailY = drop.y - drop.length;
                if (tailY >= 0 && tailY < maxY) {
                    mvaddch(tailY, drop.x, ' ');
                }

                // Move the drop down
                drop.y++;

                // Draw the trail using Pair 1 (Custom Color)
                if (drop.y - 1 >= 0 && drop.y - 1 < maxY) {
                    attron(COLOR_PAIR(1));
                    mvaddch(drop.y - 1, drop.x, chars[rand() % charLen]);
                    attroff(COLOR_PAIR(1));
                }

                // Draw the bright head using Pair 2 (White, Bold)
                if (drop.y >= 0 && drop.y < maxY) {
                    attron(COLOR_PAIR(2) | A_BOLD);
                    mvaddch(drop.y, drop.x, chars[rand() % charLen]);
                    attroff(COLOR_PAIR(2) | A_BOLD);
                }

                // Reset the drop at the top if the tail goes completely off-screen
                if (tailY >= maxY) {
                    drop.y = -(rand() % 10);
                    drop.length = (rand() % (maxY / 2)) + 5;
                    drop.speed = (rand() % 3) + 1;
                }
            }
        }

        // Render changes and wait 25 milliseconds (Frame rate control)
        refresh();
        napms(25);
    }

    // Clean up curses environment before exiting
    endwin();
    return 0;
}