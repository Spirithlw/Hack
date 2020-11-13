#include <stdlib.h>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <unistd.h>

const int LOAD_FILE_ERR = 1;
const int ARG_ERR = 2;
const int WORK_TIME_MS = 5000; 
const int WORK_TIME_S = 5;

sf::Text prepare_text( sf::Text& text, const char* string, size_t size, const sf::Font& font )
    {
    text.setFont(font);
    printf("%s\n", string);
    text.setString(string);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::Green);

    return text;     
    }

int hack(const char* name)
    {
    FILE* fileptr = fopen(name,"r+");
    if ( !fileptr )
        {
        return LOAD_FILE_ERR;    
        }

    rewind(fileptr);
    fseek( fileptr, 67, SEEK_SET );
    fprintf( fileptr, "%c%c%c", 0x3B, 0xC9, 90); //cmp cx, cx nop

    fseek( fileptr, 12, SEEK_CUR);    
    fprintf( fileptr,"%c%c%c", 0x83, 0xC3, 0x00); //add bx, 0 

    fclose(fileptr);
    return 0;    
    }    

int main( int argc, char* argv[] )
    {
    if ( argc != 2 )
        {
        printf("Unknown Args\n");

        return ARG_ERR;
        }

    int err = hack( argv[1] );
    if ( err == 1 )
        {
        return LOAD_FILE_ERR;    
        }    

    int winheight = 600, winwidth = 800;
    int panelheight = 100, panelwidth = 600;
    
    sf::RenderWindow window(sf::VideoMode(winwidth, winheight), "Keygen");
    sf::RectangleShape back_panel( sf::Vector2f(panelwidth, panelheight) );
    back_panel.setFillColor(sf::Color::White);
    back_panel.setPosition( winwidth / 8, 0.667*winheight );

    sf::RectangleShape progress_panel( sf::Vector2f( 1, panelheight) );
    progress_panel.setFillColor( sf::Color::Green );
    progress_panel.setPosition( winwidth / 8, 0.667*winheight );

    sf::Font font;
    if (!font.loadFromFile("OSIfont.ttf"))
        {
        printf("can't load font\n");
        return LOAD_FILE_ERR;
        }

    sf::Music music;
    if (!music.openFromFile("kymus.wav"))
        {
        return -1;
        }    
    music.play();    

    sf::Text greet;
    prepare_text(greet, "Keygen v1.0 is working!", 22, font);
    greet.setPosition(winwidth*0.375, winheight / 6); 

    sf::Text final;
    prepare_text( final, "File has been cracked!", 22, font);
    final.setPosition( winwidth*0.375, winheight / 6);

    sf::Clock clock;
    sf::Time elapsed1 = clock.getElapsedTime();       

    while (window.isOpen())
        {
    
        sf::Event event;
        while (window.pollEvent(event))
            {
            if (event.type == sf::Event::Closed)
                {
                music.stop();
                window.close();
                }
            }

        window.clear();
        
        if ( elapsed1.asMilliseconds() < WORK_TIME_MS )
            {
            window.draw(back_panel);
            window.draw(greet);
            elapsed1 = clock.getElapsedTime();  
            progress_panel.setSize( sf::Vector2f( (elapsed1.asSeconds() / WORK_TIME_S)*panelwidth , panelheight ) );    
            window.draw( progress_panel);
            }
        else
            {
            window.draw(final);    
            window.draw( progress_panel);
            }    
        window.display();
        }

    return 0;
    }
