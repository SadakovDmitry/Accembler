#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "Read_file.h"
#include "stack.h"
#include "SPU_func.h"
#include <SFML/Graphics.hpp>
/*
int main()
{
    sf::Image image;
    if (image.loadFromFile("./image.png"))
    {
        printf("Succses!!!\n");
    }
    else
    {
        printf("ERROR!!!");
    }
}
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "My window");

    sf::RectangleShape rectangle(sf::Vector2f(10.f, 10.f));

    while (window.isOpen())
    //for (int i = 0; i < 1000; i++)
    {
        //window.isOpen();
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
                break;
        }

        window.clear(sf::Color::Black);

        rectangle.setFillColor(sf::Color(100, 250, 50));
        window.draw(rectangle);

        window.display();
    }
    printf("end\n");
    return 0;
}

