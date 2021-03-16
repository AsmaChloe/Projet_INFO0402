#include <iostream>
#include "classA.h"
#include "deque.h"
#include <deque>

int main() {
    const A a=2;
    // constructions
    deque<A>   deque1;                   // défaut
    //deque<A>   deque2(10,0);    // first/last
    deque<A>   deque2(7);    // count
    deque<A>   deque22(11,a);    // count/value
    //deque<A>   deque3( deque2.begin(), deque2.end() );  // itérateur
    /*deque<A>   deque4( deque2 );
    deque<A>   deque5( std::move(deque4) );*/
    deque<A>   deque6( {1,2,3,4,5,6} );

    //Vrai deque
    std::deque<A>   dequea;                   // défaut
    std::deque<A>   dequeb(7);    // count
    std::deque<A>   dequebb(11,a);    // count/value
    std::deque<A>   dequec( dequeb.begin(), dequeb.end() );  // itérateur
    std::deque<A>   dequed( dequeb );
    std::deque<A>   dequee( std::move(dequed) );
    std::deque<A>   dequef( {1,2,3,4,5,6} );


    //TEST DE TAILLE
    std::cout<<"Taille deque normal : " << dequea.size() << " - Taille mon deque : "<< deque1.size() << std::endl;
    std::cout<<"Taille deque normal : " << dequeb.size() << " - Taille mon deque : "<< deque2.size() << std::endl;
    std::cout<<"Taille deque normal : " << dequebb.size() << " - Taille mon deque : "<< deque22.size() << std::endl;
    std::cout<<"Taille deque normal : " << dequef.size() << " - Taille mon deque : "<< deque6.size() << std::endl;

    //TEST AVEC OPERATOR
    std::cout<<"Avec mm element partout : "<<std::endl;
    for(int i=0;i<deque22.size();i++){
        std::cout<<"Element "<<i<<" : "<<deque22[i]<<std::endl;
    }

    std::cout<<"Avec liste d'initialisation : "<<std::endl;
    for(int i=0;i<deque6.size();i++){
        std::cout<<"Element "<<i<<" : "<<deque6[i]<<std::endl;
    }
    // assignation
    /*deque1 = deque6;
    deque2 = std::move(deque1);
    deque3 = { 4, 5, 6, 7};

    // assign
    deque1.assign( 5, 2);
    deque2.assign( deque1.begin(), deque1.end() );
    deque3.assign( {8,9,10,11} );

    // front/back
    const deque<A>&deque6const = deque6;
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
            << deque6.size()  << std::endl;

    // clear
    deque5.clear();
    deque5.resize(10);
    deque4.resize(6,4);

    // push
    deque4.push_back(2);
    // avec rvalue: impossible à tester pour T=int
    deque4.push_front(6);
    // avec rvalue: impossible à tester pour T=int

    // pop
    deque4.pop_back();
    deque4.pop_front();

    // tests
    std::cout
            << (deque4 == deque5) << ", "
            << (deque4 != deque5) << ", "
            << (deque4 <  deque5) << ", "
            << (deque4 <= deque5) << ", "
            << (deque4 >  deque5) << ", "
            << (deque4 == deque5) << std::endl;

    // iterateur
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