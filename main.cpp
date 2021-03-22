#include <iostream>
#include "classA.h"
#include "deque.h"
#include <deque>

int main() {
    const A a=2;
    // constructions
    deque<A>   deque1;                                      // défaut
    deque<A>   deque2(13);                             // count
    deque<A>   deque3(4, a);                         // count/value
    deque<A>   deque6( {1,2,3,4,5,6,7} );               //Liste d'initialisation
    deque<A>   deque4(deque6);                              //Copie
    deque<A>    deque5(std::move(deque4));                  //Par déplacement
    //A tester encore : first/last

    //Vrai deque
    std::deque<A>   dequea;                                 // défaut
    std::deque<A>   dequeb(13);                           // count
    std::deque<A>   dequec(4,a);                        // count/value
    std::deque<A>   dequef( {1,2,3,4,5,6,7} );            //Liste d'initialisation
    std::deque<A>   dequed(dequef);                         //Copie
    std::deque<A>   dequee( std::move(dequed) );            // Par déplacement
    //td::deque<A>   dequec( dequeb.begin(), dequeb.end() );  // itérateur

    //assign
    //deque1 = deque6;
    //deque2 = std::move(deque1);


    //*****************************************FRONT BACK*****************************************
    /*const deque<A>&deque6const = deque6;
    const std::deque<A>&dequefconst = dequef;
    //VRAI DEQUE
    std::cout
            << dequef.at(0) << ","
            << dequefconst.at(0) << ","
            << dequef[1] << ","
            << dequefconst[1] << ","
            << dequef.front() << ", "
            << dequefconst.front() << ", "
            << dequef.back()  << ", "
            << dequefconst.back()  << ", "
            << dequef.empty() << ", "
            << dequef.size()  << ", "
            << dequea.empty()<<std::endl;

    //MON DEQUE
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
            << deque6.size()  <<", "
            << deque1.empty()<<std::endl;*/

    //*****************************************PUSH BACK*****************************************
    //VRAI DEQUE
    std::cout<<"VRAI DEQUE\n";
    for(int i=0;i<dequec.size();i++)
        std::cout<<"dequec["<<i<<"] ="<<dequec[i]<<std::endl;
    // push
    dequec.push_back(3);

    std::cout<<"\n";
    for(int i=0;i<dequec.size();i++)
        std::cout<<"dequec["<<i<<"] ="<<dequec[i]<<std::endl;

    //MON DEQUE
    std::cout<<"\nMON DEQUE\n";
    for(int i=0;i<deque3.size();i++)
        std::cout<<"deque3["<<i<<"] ="<<deque3[i]<<std::endl;
    // push
    deque3.push_back(3);
    //deque1.push_back(a);

    std::cout<<"\n";
    for(int i=0;i<deque3.size();i++)
        std::cout<<"deque3["<<i<<"] ="<<deque3[i]<<std::endl;

    // avec rvalue: impossible à tester pour T=int
    //deque4.push_front(6);
    // avec rvalue: impossible à tester pour T=int


    /*

    // clear
    deque5.clear();
    deque5.resize(10);
    deque4.resize(6,4);



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