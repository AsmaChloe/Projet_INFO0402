#include <iostream>
#include "classA.h"
#include "deque.h"
#include <deque>

int main() {
    const A a=2;
    const A aBis=4;
    // constructions
    deque<A>   deque1;                                      // défaut
    deque<A>   deque2(13);                             // count
    deque<A>   deque3(3, a);                         // count/value
    deque<A>   deque6( {1,2,3,4,5,6,7} );               //Liste d'initialisation
    deque<A>   deque66( {0,1,2,3,4,5,6} );               //Liste d'initialisation bis
    deque<A>   deque4(deque6);                              //Copie
    deque<A>    deque5(std::move(deque4));                  //Par déplacement
    //A tester encore : first/last

    //Vrai deque
    std::deque<A>   dequea;                                 // défaut
    std::deque<A>   dequeb(13);                           // count
    std::deque<A>   dequec(3,a);                        // count/value
    std::deque<A>   dequef( {1,2,3,4,5,6,7} );            //Liste d'initialisation
    std::deque<A>   dequeff( {0,1,2,3,4,5,6} );               //Liste d'initialisation bis
    std::deque<A>   dequed(dequef);                         //Copie
    std::deque<A>   dequee( std::move(dequed) );            // Par déplacement
    //td::deque<A>   dequec( dequeb.begin(), dequeb.end() );  // itérateur

    //assign => A FAIRE : assign( deque1.begin(), deque1.end() )
    //deque1 = deque6;
    //deque2 = std::move(deque1);

    //*****************************************PUSH BACK*****************************************
    //VRAI DEQUE
    /*std::cout<<"VRAI DEQUE\n";
    for(int i=0;i<dequec.size();i++)
        std::cout<<"dequec["<<i<<"] ="<<dequec[i]<<std::endl;
    // push
    dequec.push_back(3);
    dequec.push_back(a);

    std::cout<<"\n";
    for(int i=0;i<dequec.size();i++)
        std::cout<<"dequec["<<i<<"] ="<<dequec[i]<<std::endl;

    //MON DEQUE
    std::cout<<"\nMON DEQUE\n";
    for(int i=0;i<deque3.size();i++)
        std::cout<<"deque3["<<i<<"] ="<<deque3[i]<<std::endl;
    // push
    deque3.push_back(3);
    deque3.push_back(a);

    std::cout<<"\n";
    for(int i=0;i<deque3.size();i++)
        std::cout<<"deque3["<<i<<"] ="<<deque3[i]<<std::endl;*/

    //*****************************************PUSH FRONT*****************************************
    //VRAI DEQUE
    /*std::cout<<"VRAI DEQUE\n";
    for(int i=0;i<dequec.size();i++)
        std::cout<<"dequec["<<i<<"] ="<<dequec[i]<<std::endl;
    // push
    dequec.push_front(3);
    dequec.push_front(aBis);
    std::cout<<"\n    dequec.push_front(3);\n"
               "    dequec.push_front(aBis);\n"<<std::endl;

    for(int i=0;i<dequec.size();i++)
        std::cout<<"dequec["<<i<<"] ="<<dequec[i]<<std::endl;

    //MON DEQUE
    std::cout<<"\nMON DEQUE\n";
    for(int i=0;i<deque3.size();i++)
        std::cout<<"deque3["<<i<<"] ="<<deque3[i]<<std::endl;
    // push
    deque3.push_front(3);
    deque3.push_front(aBis);
    std::cout<<"\n    deque3.push_front(3);\n"
               "    deque3.push_front(aBis);\n"<<std::endl;

    for(int i=0;i<deque3.size();i++)
        std::cout<<"deque3["<<i<<"] ="<<deque3[i]<<std::endl;*/
    // avec rvalue: impossible à tester pour T=int
    //deque4.push_front(6);
    // avec rvalue: impossible à tester pour T=int

    //*****************************************RESIZE*****************************************
    //VRAI DEQUE
    std::cout<<"***************VRAI DEQUE***************\n";
    for(int i=0;i<dequef.size();i++)
        std::cout<<" dequef["<<i<<"]="<<dequef[i];

    dequef.resize(5);
    std::cout<<"\n\n...dequef.resize(5)..."<<std::endl;

    for(int i=0;i<dequef.size();i++)
        std::cout<<" dequef["<<i<<"]="<<dequef[i];

    dequef.resize(10,2);
    std::cout<<"\n\n...dequef.resize(10,2)..."<<std::endl;

    for(int i=0;i<dequef.size();i++)
        std::cout<<" dequef["<<i<<"]="<<dequef[i];


    //MON DEQUE
    std::cout<<"\n\n***************MON DEQUE***************\n\n";
    for(int i=0;i<deque6.size();i++)
        std::cout<<" deque6["<<i<<"]="<<deque6[i];

    deque6.resize(5);
    std::cout<<"\n\n...deque6.resize(5)..."<<std::endl;

    for(int i=0;i<deque6.size();i++)
        std::cout<<" deque6["<<i<<"]="<<deque6[i];

    deque6.resize(10,2);
    std::cout<<"\n\n...deque6.resize(10,2)..."<<std::endl;

    for(int i=0;i<deque6.size();i++)
        std::cout<<" deque6["<<i<<"]="<<deque6[i];
    // clear & resize
    //deque5.clear();
    //std::cout << " Clear deque 5 : " << deque5.size() << std::endl;
    /*deque5.resize(10);
    deque4.resize(6,4);

    // pop
    deque4.pop_back();
    deque4.pop_front();*/

    //*****************************************OPERATEUR DE TEST*****************************************
    //ERREUR POUR UN DEQUE COMPOSE DE A mais ok pour deque de int /!\ A RESOUDRE !!!

    //MON DEQUE
    /*std::cout
            << "Deque 6 == Deque 3 : " << ((deque6 == deque66)?"OUI" : "NON") << std::endl
            << "Deque 6 != Deque 3 : " << ((deque6 != deque66)?"OUI" : "NON") << std::endl
            << "Deque 6 < Deque 3 : " << ((deque6 < deque66)?"OUI" : "NON") << std::endl
            << "Deque 6 <= Deque 3 : " << ((deque6 <= deque66)?"OUI" : "NON") << std::endl
            << "Deque 6 > Deque 3 : " << ((deque6 > deque66)?"OUI" : "NON") << std::endl
            << "Deque 6 >= Deque 3 : " << ((deque6 >= deque66)?"OUI" : "NON") << std::endl;

    //VRAI DEQUE
    std::cout << "VERIFICATIONS :" << std::endl
    //dequef( {1,2,3,4,5,6,7} );
    //dequeff( {0,1,2,3,4,5,6} );
            << "ddequef == dequec : " << ((dequef == dequec)?"OUI" : "NON") << std::endl
            << "dequef != dequec : " << ((dequef != dequec)?"OUI" : "NON") << std::endl
            << "dequef < dequec : " << ((dequef < dequec)?"OUI" : "NON") << std::endl
            << "dequef <= dequec : " << ((dequef <= dequec)?"OUI" : "NON") << std::endl
            << "dequef > dequec : " << ((dequef > dequec)?"OUI" : "NON") << std::endl
            << "dequef >= dequec : " << ((dequef >= dequec)?"OUI" : "NON") << std::endl;*/

    // iterateur
    /*
    for(auto it=deque4.begin(); it!=deque4.end(); ++it) std::cout << *it << ",";
    std::cout << std::endl;
    deque<A>::iterator it1 = deque1.insert( deque1.cbegin(), 7 );
    // avec rvalue: impossible à tester pour T=int
    deque<A>::iterator it3 = deque1.insert( it1, 4, 7 );
    deque<A>::iterator it4 = deque1.insert( it3, deque2.begin(), deque2.end() );
    deque<A>::iterator it5 = deque1.insert( it4, {5,4,3,2,1,0} );
    deque<A>::iterator it6 = deque1.erase(it5);
    deque1.erase(it6, deque1.cend() );
    // swap
    deque4.swap(deque5);
    swap(deque1,deque2);*/


    return 0;
}