#include <iostream>
#include "classA.h"
#include "deque.h"
#include <deque>

int main() {
    const A a=2;
    // constructions
    deque<A>   deque1;                                      // défaut
    deque<A>   deque2(13);                             // count
    deque<A>   deque3(11, a);                         // count/value
    deque<A>   deque6( {1,2,3,4,5,6,7} );               //Liste d'initialisation
    deque<A>   deque4(deque6);                              //Copie
    deque<A>    deque5(std::move(deque4));                  //Par déplacement
    //A tester encore : first/last

    //Vrai deque
    std::deque<A>   dequea;                                 // défaut
    std::deque<A>   dequeb(13);                           // count
    std::deque<A>   dequec(11,a);                        // count/value
    std::deque<A>   dequef( {1,2,3,4,5,6,7} );            //Liste d'initialisation
    std::deque<A>   dequed(dequef);                         //Copie
    std::deque<A>   dequee( std::move(dequed) );            // Par déplacement
    //td::deque<A>   dequec( dequeb.begin(), dequeb.end() );  // itérateur

    //assign
    //deque1 = deque6;
    //deque2 = std::move(deque1);

    //*****************************************operator= : liste d'initialisation*****************************************
    /*std::cout<<"\n ...dequea = { 4, 5, 6, 7}...\n";
    dequeb = { 4, 5, 6, 7};

    for(int i=0;i<dequeb.size();i++)
        std::cout<<"dequeb["<<i<<"] ="<<dequeb[i]<<std::endl;


    std::cout<<"\n\nMON DEQUE !!!!!!"<<std::endl;

    std::cout<<"\n ...deque2 = { 4, 5, 6, 7};;...\n";
    deque2 = { 4, 5, 6, 7};

    for(int i=0;i<deque2.size();i++)
        std::cout<<"deque2["<<i<<"] ="<<deque2[i]<<std::endl;*/


    //*****************************************assign : count, value*****************************************
    /*std::cout<<"\n ...dequea.assign( 5, a);...\n";
    dequea.assign( 6, a);

    for(int i=0;i<dequea.size();i++)
        std::cout<<"dequea["<<i<<"] ="<<dequea[i]<<std::endl;


    std::cout<<"\n\nMON DEQUE !!!!!!"<<std::endl;

    std::cout<<"\n ...deque1.assign( 5, a);...\n";
    deque1.assign( 6, a);

    for(int i=0;i<deque1.size();i++)
        std::cout<<"deque1["<<i<<"] ="<<deque1[i]<<std::endl;*/

    //*****************************************assign : liste d'initialisation*****************************************

    std::cout<<"\n ...dequec.assign( 5, a);...\n";
    dequec.assign( {8,9,10,11} );

    for(int i=0;i<dequec.size();i++)
        std::cout<<"dequec["<<i<<"] ="<<dequec[i]<<std::endl;


    std::cout<<"\n\nMON DEQUE !!!!!!"<<std::endl;

    std::cout<<"\n ...deque3.assign( {8,9,10,11} );...\n";
    deque3.assign( {8,9,10,11} );

    for(int i=0;i<deque3.size();i++)
        std::cout<<"deque3["<<i<<"] ="<<deque3[i]<<std::endl;

    /* A FAIRE QUAND ITERATOR !!!!!!!!!!!!! deque2.assign( deque1.begin(), deque1.end() );*/


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