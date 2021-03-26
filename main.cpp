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

    // assignation
    /*deque1 = deque6;
    deque2 = std::move(deque1);
    deque3 = { 4, 5, 6, 7};*/

    // assign
    /*deque1.assign( 5, 2);
    deque2.assign( deque1.begin(), deque1.end() ); ========> impossible pour l'instant
    deque3.assign( {8,9,10,11} );*/

    // front/back
    /*const deque<A>&deque6const = deque6;
    std::cout
            << deque6.at(0) << ","
            << deque6const.at(0) << ","
            << deque6[1] << ","
            << deque6const[1] << ","
            << deque6.front() << ", "
            << deque6const.front() << ", "
            << deque6.back()  << ", "
            << deque6const.back()  << ", "
            << deque6.empty() << ", "
            << deque6.size()  << std::endl;*/


    // clear
    /*deque5.clear();
    deque5.resize(10);
    deque4.resize(6,4);*/

    // push
    //deque4.push_back(2);
    // avec rvalue: impossible à tester pour T=int
    //deque4.push_front(6);
    // avec rvalue: impossible à tester pour T=int

    //*****************************************POP BACK*****************************************

    std::cout<<"***************VRAI DEQUE***************\n";
    for(int i=0;i<dequec.size();i++)
        std::cout<<" dequec["<<i<<"]="<<dequec[i];

    dequec.pop_back();
    std::cout<<"\n\n...dequec.pop_back();..."<<std::endl;

    for(int i=0;i<dequec.size();i++)
        std::cout<<" dequec["<<i<<"]="<<dequec[i];


    //MON DEQUE
    std::cout<<"\n\n***************MON DEQUE***************\n\n";
    for(int i=0;i<deque3.size();i++)
        std::cout<<" deque3["<<i<<"]="<<deque3[i];

    deque3.pop_back();
    std::cout<<"\n\n...deque3.pop_back();..."<<std::endl;

    for(int i=0;i<deque3.size();i++)
        std::cout<<" deque3["<<i<<"]="<<deque3[i];

    //*****************************************SWAP*****************************************
    // swap
    //deque4.swap(deque5);
    //swap(deque1,deque2);
    /*std::cout<<"***************VRAI DEQUE***************\n";
    for(int i=0;i<dequec.size();i++)
        std::cout<<" dequec["<<i<<"]="<<dequec[i];
    std::cout<<"\n";
    for(int i=0;i<dequee.size();i++)
        std::cout<<" dequee["<<i<<"]="<<dequee[i];

    dequec.swap(dequee);
    std::cout<<"\n\n...dequec.swap(dequee);..."<<std::endl;

    for(int i=0;i<dequec.size();i++)
        std::cout<<" dequec["<<i<<"]="<<dequec[i];
    std::cout<<"\n";
    for(int i=0;i<dequee.size();i++)
        std::cout<<" dequee["<<i<<"]="<<dequee[i];

    dequee.swap(dequec);
    std::cout<<"\n\n...dequee.swap(dequec);..."<<std::endl;

    for(int i=0;i<dequec.size();i++)
        std::cout<<" dequec["<<i<<"]="<<dequec[i];
    std::cout<<"\n";
    for(int i=0;i<dequee.size();i++)
        std::cout<<" dequee["<<i<<"]="<<dequee[i];


    //MON DEQUE
    std::cout<<"\n\n***************MON DEQUE***************\n\n";
    for(int i=0;i<deque3.size();i++)
        std::cout<<" deque3["<<i<<"]="<<deque3[i];
    std::cout<<"\n";
    for(int i=0;i<deque5.size();i++)
        std::cout<<" deque5["<<i<<"]="<<deque5[i];

    deque3.swap(deque5);
    std::cout<<"\n\n...deque3.swap(deque5);..."<<std::endl;

    for(int i=0;i<deque3.size();i++)
        std::cout<<" deque3["<<i<<"]="<<deque3[i];
    std::cout<<"\n";
    for(int i=0;i<deque5.size();i++)
        std::cout<<" deque5["<<i<<"]="<<deque5[i];

    deque5.swap(deque3);
    std::cout<<"\n\n...deque5.swap(deque3);..."<<std::endl;

    for(int i=0;i<deque3.size();i++)
        std::cout<<" deque3["<<i<<"]="<<deque3[i];
    std::cout<<"\n";
    for(int i=0;i<deque5.size();i++)
        std::cout<<" deque5["<<i<<"]="<<deque5[i];*/


    //*****************************************OPERATEUR DE TEST*****************************************
    //MON DEQUE
    /*std::cout
            << "Deque 6 == Deque 3 : " << ((deque6 == deque3)?"OUI" : "NON") << std::endl
            << "Deque 6 != Deque 3 : " << ((deque6 != deque3)?"OUI" : "NON") << std::endl
            << "Deque 6 < Deque 3 : " << ((deque6 < deque3)?"OUI" : "NON") << std::endl
            << "Deque 6 <= Deque 3 : " << ((deque6 <= deque3)?"OUI" : "NON") << std::endl
            << "Deque 6 > Deque 3 : " << ((deque6 > deque3)?"OUI" : "NON") << std::endl
            << "Deque 6 >= Deque 3 : " << ((deque6 >= deque3)?"OUI" : "NON") << std::endl;

    //VRAI DEQUE
    std::cout << "VERIFICATIONS :" << std::endl
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
*/


    return 0;
}