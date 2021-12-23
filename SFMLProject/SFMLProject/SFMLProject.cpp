#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Tus.h"
#include "SpaceSurvival.h"
#include "tredRace.h"
#include "Raycasting.h"




using namespace sf;
using namespace std;

tredRace rc;
SpaceSurvival spc;
Raycasting ryc;

int main(int argc, char* argv[]){
    vector<Tus> tuslar;
  
    RenderWindow ekran(VideoMode(1024, 800), "GAAAMMMEESSSSS!!!!!",Style::Default);
    ekran.setFramerateLimit(60);

    Tus tus1 ("Psedo Drive" , { 200,50 }, Color::Black, Color::White );
    tus1.TusPoz({ 150,50 });
    Font arial;
    arial.loadFromFile("arial.ttf");
    tus1.sFont(arial);
    tus1.FontSize(20);
    tuslar.push_back(tus1);


    Tus tus2("SurvivalSpace", { 200,50 }, Color::Black, Color::White);
    tus2.TusPoz({ 150,150 });
    tus2.sFont(arial);
    tus2.FontSize(20);
    tuslar.push_back(tus2);

    Tus tus3("RayCasting", { 200,50 }, Color::Black, Color::White);
    tus3.TusPoz({ 150,250 });
    tus3.sFont(arial);
    tus3.FontSize(20);
    tuslar.push_back(tus3);



    while (ekran.isOpen())
   
    {
        Event olay;

        while (ekran.pollEvent(olay)) {
           
            switch (olay.type) {


            case  Event::Closed: {
                ekran.close();
            }
            case(Event::MouseMoved): {
                for (int i = 0; i < tuslar.size(); i++) {
                    if (tuslar[i].FareHover(ekran)) {
                        tuslar[i].ArkaRenk(Color::Blue);
                    }
                    else {
                        tuslar[i].ArkaRenk(Color::White);
                    }
                }
                break;
            }
            case Event::MouseButtonPressed:
                if (tus1.FareHover(ekran)) {
                        rc.PsedoMain();
                    
                }
                else if (tus2.FareHover(ekran)) {
                    spc.SpaceMain();
                    
                }
                else if (tus3.FareHover(ekran)) {
                    ryc.RayMain( argc, argv);

                }

            }
             
           
                
            
            
        }
        ekran.clear();
        tus1.EkranaCiz(ekran);
        tus2.EkranaCiz(ekran);
        tus3.EkranaCiz(ekran);
        ekran.display();

        
    }

    return 0;
}

