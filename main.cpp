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

    //Test apres constructeur par déplacement
    for(int i=0;i<deque4.size();i++)
        std::cout<<"Mon deque : "<<dequed[i]<< "- Vrai deque :"<<deque4[i]<<std::endl;

    //assign
    std::cout<<"VRAI DEQUE !!!!!!"<<std::endl;
    for(int i=0;i<dequeb.size();i++)
        std::cout<<"dequeb["<<i<<"] ="<<dequeb[i]<<std::endl;

    std::cout<<"\n";

    for(int i=0;i<dequef.size();i++)
        std::cout<<"dequef["<<i<<"] ="<<dequef[i]<<std::endl;

    std::cout<<"\n ...dequeb=dequef...\n";
    dequeb = dequef;

    for(int i=0;i<dequeb.size();i++)
        std::cout<<"dequeb["<<i<<"] ="<<dequeb[i]<<std::endl;

    std::cout<<"MON DEQUE !!!!!!"<<std::endl;
    for(int i=0;i<deque2.size();i++)
        std::cout<<"deque2["<<i<<"] ="<<deque2[i]<<std::endl;

    std::cout<<"\n";

    for(int i=0;i<deque6.size();i++)
        std::cout<<"deque6["<<i<<"] ="<<deque6[i]<<std::endl;

    std::cout<<"\n ...deque2=deque6...\n";
    deque2 = deque6;

    for(int i=0;i<deque2.size();i++)
        std::cout<<"deque2["<<i<<"] ="<<deque2[i]<<std::endl;
    /*deque2 = std::move(deque1);
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