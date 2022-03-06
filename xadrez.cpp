//////////

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int size = 56;
Sprite f[32];

int tabuleiro[8][8] = {
    -1,-2,-3,-4,-5,-3,-2,-1,
    -6,-6,-6,-6,-6,-6,-6,-6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    6, 6, 6, 6, 6, 6, 6, 6,
    1, 2, 3, 4, 5, 3, 2, 1
};

void loadPosition()
{
    int k = 0;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            int peca  =  tabuleiro[i][j];
            if(!peca) { continue; }
            int cor  =  (peca > 0) ? 1 : 0;  // define a cor da peça
            peca = abs(peca) - 1;            // define a peça

            f[k].setTextureRect(IntRect(peca*size, cor*size, size, size));
            f[k].setPosition(j*size, i*size);
            k++;
        }
    }
}



int main(int argc, char** argv)
{

    RenderWindow wnd( VideoMode(454, 454), "xadrez.exe" );

    Texture t1, t2;
    t1.loadFromFile("images\\board0.png");
    t2.loadFromFile("images\\figures.png");
    
    Sprite board;
    board.setTexture(t1);

    for(int i = 0; i < 32; i++) { f[i].setTexture(t2); }
    loadPosition();

    Event evento;

    double dx = 0, dy = 0;
    bool isMove = false;
    int n = 0;


    while(wnd.isOpen())
    {
        Vector2<int> pos  =  Mouse::getPosition(wnd);  // posição atual do cursor

        while( wnd.pollEvent(evento) )
        {
            if(evento.type == Event::Closed) { wnd.close(); }

            //----- drag/arrastar -----
            if(evento.type == Event::MouseButtonPressed && evento.key.code == Mouse::Left)
            {
                for(int i = 0; i < 32; i++)
                {
                    if(f[i].getGlobalBounds().contains(pos.x, pos.y))
                    {
                        n = i;
                        isMove = true;                             // calcula deslocamento
                        dx  =  pos.x  -  f[i].getPosition().x ;       // deslocamento horizontal
                        dy  =  pos.y  -  f[i].getPosition().y ;       // deslocamento vertical
                    }
                }
            }

            //----- drop/soltar -----
            if(evento.type == Event::MouseButtonReleased && evento.key.code == Mouse::Left)
            {
                isMove = false;
            }

        }

        if(isMove) { f[n].setPosition(pos.x - dx, pos.y - dy); }



        wnd.clear();
        wnd.draw(board);
        for(int i = 0; i < 32; i++) { wnd.draw(f[i]); }
        wnd.display();
    }








}