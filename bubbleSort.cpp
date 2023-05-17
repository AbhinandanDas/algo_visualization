#include <SFML/Graphics.hpp>
#include <random>

#define SCREENWIDTH 1200
#define SCREENHEIGHT 900

using namespace sf;

RenderWindow window(VideoMode(SCREENWIDTH,SCREENHEIGHT), "Bubble Sort");
Mutex mutex;

int numBars = 15;
int currentBar = 0;
int compareBar = 0;
int totalComparisions = 0;
int totalSwaps = 0;
int minBar;

void DrawBars(int* barHeight) {
    for(int i = 0 ; i < numBars; i++) {
        RectangleShape bar(Vector2f(SCREENWIDTH / numBars , barHeight[i]));
        bar.setPosition((SCREENWIDTH / numBars) * i , SCREENHEIGHT - barHeight[i]);
        if(i == compareBar) {
            bar.setFillColor(Color::Red);
        }
        else if(i == currentBar) {
            bar.setFillColor(Color::Green);
        }
        else if(i == minBar) {
            bar.setFillColor(Color::Blue);
        }
        else {
            bar.setFillColor(Color::White);
        }
        window.draw(bar);
    }
}

// void BubbleSort(int* arr) {
//     for(currentBar = 0 ; currentBar < numBars ; currentBar++) {
//         bool swap = false;
//         for(compareBar = 0 ; compareBar < numBars - currentBar - 1 ; compareBar++) {
//             totalComparisions++;
//             if(arr[compareBar] > arr[compareBar + 1]) {
//                 int temp = arr[compareBar];
//                 arr[compareBar] = arr[compareBar + 1];
//                 arr[compareBar + 1] = temp;
//                 swap = true;
//                 totalSwaps++;
//             }
//             sleep(milliseconds(100));
//         }

//         if(!swap) {
//             return;
//         }
//     }
// }

void SelectionSort(int* arr) {
    for(currentBar = 0 ; currentBar < numBars - 1; currentBar++) {
        minBar = currentBar;
        for(compareBar = currentBar + 1 ; compareBar < numBars ; compareBar++) {
            if(arr[compareBar] <  arr[minBar]) {
                totalComparisions++;
                minBar = compareBar; 
            }
            sleep(milliseconds(200));
        }

        if(minBar!=currentBar) {
            int temp = arr[currentBar];
            arr[currentBar] = arr[minBar];
            arr[minBar] = temp;
            totalSwaps++;
        }
    }
}

int main() {
    window.setFramerateLimit(60);
    int *barHeight = (int*) malloc(sizeof(int) * numBars);

    for(int i = 0 ; i < numBars ; i++) {
        barHeight[i] = rand() % SCREENHEIGHT; // generates bars [0 , SCREENHEIGHT]
    }

    Thread sort(&SelectionSort, barHeight);
    Text comparisionsText;
    Text swapsText;
    Font font;
    font.loadFromFile("fonts/arial.ttf");
    comparisionsText.setFont(font);
    comparisionsText.setFillColor(Color::White);
    swapsText.setFont(font);
    swapsText.setFillColor(Color::White);
    swapsText.setPosition(300, 0);

    sort.launch(); // i have doubts

    while(window.isOpen()) {
        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear();

        comparisionsText.setString((String)"Comparisions: " + std::to_string(totalComparisions));
        swapsText.setString((String)"Swaps : " + std::to_string(totalSwaps));
        window.draw(comparisionsText);
        window.draw(swapsText);
        DrawBars(barHeight);
        window.display();
    }

}
