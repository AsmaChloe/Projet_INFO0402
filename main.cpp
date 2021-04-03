#include <iostream>
#include "classA.h"
#include "deque.h"
#include <deque>

int main() {
    A a=2;
     A aBis=4;
    // constructions
    deque<A>   deque1;                                       // défaut
    deque<A>   deque2(13);                             // count
    deque<A>   deque3(2, a);                           // count/value
    deque<A>   deque6( {1,2,3,4,5,6,7} );               //Liste d'initialisation
    deque<A>   deque66( {8,7,6,5,4,7} );                //Liste d'initialisation bis
    deque<A>   deque4(deque6);                              //Copie
    deque<A>   deque5(std::move(deque4));                   //Par déplacement
    deque<A>   deque7(deque6.begin(),deque6.end());         //first/last

    //Vrai deque
    std::deque<A>   dequea;                                 // défaut
    std::deque<A>   dequeb(13);                          // count
    std::deque<A>   dequec(2,a);                         // count/value
    std::deque<A>   dequef( {1,2,3,4,5,6,7} );           //Liste d'initialisation
    std::deque<A>   dequeff( {8,7,6,5,4,7} );            //Liste d'initialisation bis
    std::deque<A>   dequed(dequef);                         //Copie
    std::deque<A>   dequee( std::move(dequed) );            // Par déplacement
    std::deque<A>   dequeg( dequef.begin(), dequef.end() ); // first/last

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

    // pop
    /*deque4.pop_back();
    deque4.pop_front();*/

    // tests
    /*std::cout
            << (deque4 == deque5) << ", "
            << (deque4 != deque5) << ", "
            << (deque4 <  deque5) << ", "
            << (deque4 <= deque5) << ", "
            << (deque4 >  deque5) << ", "
            << (deque4 == deque5) << std::endl;*/

    // swap
    /*deque4.swap(deque5);
    swap(deque1,deque2);*/

    //**************************************ITERATEUR**************************************
    //VRAI DEQUE
    std::cout<<"***************VRAI DEQUE - version const ***************\n";
    std::deque<A> constdequeff=dequeff;

    std::deque<A>::const_iterator itff=constdequeff.begin();
    std::deque<A>::const_iterator itffBis(itff);

    std::cout<<"Voici constdequeff : "<<std::endl;
    for (auto it = constdequeff.cbegin(); it != constdequeff.cend(); it++) {
        std::cout << *it << ", ";
    }

    //Operateur ++ --
    std::cout<<"\n\nPremier élément : "<<*(itffBis++)<<std::endl;
    std::cout<<"Deuxieme élément : "<<*itffBis<<std::endl;
    std::cout<<"Troisieme élément : "<<*(++itffBis)<<std::endl;
    std::cout<<"Troisieme élément : "<<*(itffBis--)<<std::endl;
    std::cout<<"Deuxieme élément : "<<*(itffBis)<<std::endl;
    std::cout<<"Premier élément : "<<*(--itffBis)<<std::endl;


    //Comparaison
    std::cout<<"\nitff : "<<*itff<<" - itffBis : "<<*itffBis<<std::endl;
    std::cout<<"itff == itffBis ? "<<(itff == itffBis)<<std::endl;
    std::cout<<"itff != itffBis ? "<<(itff != itffBis)<<std::endl;

    //Random access
    std::cout<<"itff < itffBis ? "<<(itff < itffBis)<<std::endl;
    std::cout<<"itff <= itffBis ? "<<(itff <= itffBis)<<std::endl;
    std::cout<<"itff > itffBis ? "<<(itff > itffBis)<<std::endl;
    std::cout<<"itff >= itffBis ? "<<(itff >= itffBis)<<std::endl;

    //+= -=
    std::cout<<"\nitff : "<<*itff<<"\n ...itff+=3..."<<std::endl;
    itff+=3;
    std::cout<<"itff : "<<*itff<<"\n...itff-=3..."<<std::endl;
    itff-=3;
    std::cout<<"itf : "<<*itff<<std::endl;

    //Operateur []
    std::cout<<"itff[3]="<<itff[3]<<std::endl;

    std::cout<<"\n\n"<<std::endl;
    //MON DEQUE
    std::cout<<"***************MON DEQUE - version const***************\n";
    deque<A> constdeque66=deque66;

    deque<A>::const_iterator it66=constdeque66.begin();
    deque<A>::const_iterator it66Bis(it66);

    std::cout<<"Voici constdeque66 : "<<std::endl;
    for (auto it66 = constdeque66.cbegin(); it66 != constdeque66.cend(); it66++) {
        std::cout << *it66 << ", ";
    }

    //Operateur ++ --
    std::cout<<"\n\nPremier élément : "<<*(it66Bis++)<<std::endl;
    std::cout<<"Deuxieme élément : "<<*it66Bis<<std::endl;
    std::cout<<"Troisieme élément : "<<*(++it66Bis)<<std::endl;
    std::cout<<"Troisieme élément : "<<*(it66Bis--)<<std::endl;
    std::cout<<"Deuxieme élément : "<<*(it66Bis)<<std::endl;
    std::cout<<"Premier élément : "<<*(--it66Bis)<<std::endl;

    //Comparaison
    std::cout<<"\nit66 : "<<*it66<<" - it66Bis : "<<*it66Bis<<std::endl;
    std::cout<<"it66 == it66Bis ? "<<(it66 == it66Bis)<<std::endl;
    std::cout<<"it66 != it66Bis ? "<<(it66 != it66Bis)<<std::endl;

    //Random access
    std::cout<<"it66 < it66Bis ? "<<(it66 < it66Bis)<<std::endl;
    std::cout<<"it66 <= it66Bis ? "<<(it66 <= it66Bis)<<std::endl;
    std::cout<<"it66 > it66Bis ? "<<(it66 > it66Bis)<<std::endl;
    std::cout<<"it66 >= it66Bis ? "<<(it66 >= it66Bis)<<std::endl;

    //+= -=
    std::cout<<"\nit66 : "<<*it66<<"\n ...it66+=3..."<<std::endl;
    it66+=3;
    std::cout<<"it66 : "<<*it66<<"\n...it66-=3..."<<std::endl;
    it66-=3;
    std::cout<<"it66 : "<<*it66<<std::endl;

    //Operateur []                  ERREUR
    //std::cout<<"it66[3]="<<it66[3]<<std::endl;

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