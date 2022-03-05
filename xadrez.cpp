//////////

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int size = 56;


int main(int argc, char** argv)
{

    RenderWindow wnd( VideoMode(454, 454), "xadrez.exe" );

    Texture t1, t2;
    t1.loadFromFile("images\\board0.png");
    t2.loadFromFile("images\\figures.png");
    
    Sprite board;
    board.setTexture(t1);

    Sprite f;
    f.setTexture(t2);

    Event evento;

    double dx = 0, dy = 0;
    bool isMove = false;


    while(wnd.isOpen())
    {
        Vector2<int> pos  =  Mouse::getPosition(wnd);  // posição atual do cursor

        while( wnd.pollEvent(evento) )
        {
            if(evento.type == Event::Closed) { wnd.close(); }

            //----- drag/arrastar -----
            if(evento.type == Event::MouseButtonPressed && evento.key.code == Mouse::Left)
            {
                if(f.getGlobalBounds().contains(pos.x, pos.y))
                {
                    isMove = true;                             // calcula deslocamento
                    dx  =  pos.x  -  f.getPosition().x ;       // deslocamento horizontal
                    dy  =  pos.y  -  f.getPosition().y ;       // deslocamento vertical
                }
            }

            
            cout << pos.x << " - " << f.getPosition().x << " = " << dx << endl;
            cout << pos.y << " - " << f.getPosition().y << " = " << dy << endl << endl;


            //----- drop/soltar -----
            if(evento.type == Event::MouseButtonReleased && evento.key.code == Mouse::Left)
            {
                isMove = false;
            }

        }

        if(isMove) { f.setPosition(pos.x - dx, pos.y - dy); }



        wnd.clear();
        wnd.draw(board);
        wnd.draw(f);
        wnd.display();
    }








}