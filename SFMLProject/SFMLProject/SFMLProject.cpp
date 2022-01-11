#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Tus.h"
#include "SpaceSurvival.h"
#include "tredRace.h"
#include "Raycasting.h"
#include "pongs.h"




using namespace sf;
using namespace std;

tredRace rc;
SpaceSurvival spc;
Raycasting ryc;
pongs png;

int main(int argc, char* argv[]){
    vector<Tus> tuslar;
  
    RenderWindow ekran(VideoMode(1024, 800), "SFML-GAME_CENTER",Style::Default);
    ekran.setFramerateLimit(60);

    Tus tus1 ("Psedo Drive" , { 200,50 }, Color::Black, Color::White );
    tus1.TusPoz({ 400,50 });
    Font arial;
    arial.loadFromFile("arial.ttf");
    tus1.sFont(arial);
    tus1.FontSize(20);
    tuslar.push_back(tus1);


    Tus tus2("SurvivalSpace", { 200,50 }, Color::Black, Color::White);
    tus2.TusPoz({ 400,150 });
    tus2.sFont(arial);
    tus2.FontSize(20);
    tuslar.push_back(tus2);

    Tus tus3("RayCasting", { 200,50 }, Color::Black, Color::White);
    tus3.TusPoz({ 400,250 });
    tus3.sFont(arial);
    tus3.FontSize(20);
    tuslar.push_back(tus3);

    Tus tus4("Poing", { 200,50 }, Color::Black, Color::White);
    tus4.TusPoz({ 400,350 });
    tus4.sFont(arial);
    tus4.FontSize(20);
    tuslar.push_back(tus4);



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
                    ryc.RayMain(argc, argv);

                }
                else if (tus4.FareHover(ekran)) {
                    png.mainPong();

                }

            }
             
           
                
            
            
        }
        ekran.clear();
        tus1.EkranaCiz(ekran);
        tus2.EkranaCiz(ekran);
        tus3.EkranaCiz(ekran);
        tus4.EkranaCiz(ekran);
        ekran.display();

        
    }

    return 0;
}

