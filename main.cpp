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
    deque<int>   deque7({1,2,3,4,5,6,7});
    deque<int>   deque8({0,1,2,3,4,5,6});
    deque<A>   deque4(deque6);                              //Copie
    deque<A>    deque5(std::move(deque4));                  //Par déplacement
    //A tester encore : first/last

    //Vrai deque
    std::deque<A>   dequea;                                 // défaut
    std::deque<A>   dequeb(13);                           // count
    std::deque<A>   dequec(11,a);                        // count/value
    std::deque<A>   dequef( {1,2,3,4,5,6,7} );            //Liste d'initialisation
    std::deque<A>   dequed(dequef);                         //Copie
    std::deque<int>   dequeg({1,2,3,4,5,6,7});
    std::deque<int>   dequez({0,1,2,3,4,5,6});
    std::deque<A>   dequee( std::move(dequed) );            // Par déplacement
    //td::deque<A>   dequec( dequeb.begin(), dequeb.end() );  // itérateur

    //assign
    //deque1 = deque6;
    //deque2 = std::move(deque1);

    //*****************************************assign : liste d'initialisation*****************************************
    /* A FAIRE QUAND ITERATOR !!!!!!!!!!!!! deque2.assign( deque1.begin(), deque1.end() );*/

    //*****************************************FRONT BACK*****************************************
    const deque<A>&deque6const = deque6;
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
            << dequef.size()  << std::endl;

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
            << "Empty ? " << deque6.empty() << ", "
            << "Size() : " << deque6.size()  << std::endl;

    // clear
    //deque5.clear();
    //std::cout << " Clear deque 5 : " << deque5.size() << std::endl;
    /*deque5.resize(10);
    deque4.resize(6,4);
    // push
    deque4.push_back(2);
    // avec rvalue: impossible à tester pour T=int
    deque4.push_front(6);
    // avec rvalue: impossible à tester pour T=int
    // pop
    deque4.pop_back();
    deque4.pop_front();
    */// tests
    std::cout
            << "Deque 6 == Deque 7 : " << ((deque7 == deque8)?"OUI" : "NON") << std::endl
            << "Deque 6 != Deque 7 : " << ((deque7 != deque8)?"OUI" : "NON") << std::endl
            << "Deque 6 < Deque 7 : " << ((deque7 < deque8)?"OUI" : "NON") << std::endl
            << "Deque 6 <= Deque 7 : " << ((deque7 <= deque8)?"OUI" : "NON") << std::endl
            << "Deque 6 > Deque 7 : " << ((deque7 > deque8)?"OUI" : "NON") << std::endl
            << "Deque 6 >= Deque 7 : " << ((deque7 >= deque8)?"OUI" : "NON") << std::endl;

    std::cout << "VERIFICATIONS :" << std::endl;
    std::cout
            << "Deque 6 == Deque 7 : " << ((dequeg == dequez)?"OUI" : "NON") << std::endl
            << "Deque 6 != Deque 7 : " << ((dequeg != dequez)?"OUI" : "NON") << std::endl
            << "Deque 6 < Deque 7 : " << ((dequeg < dequez)?"OUI" : "NON") << std::endl
            << "Deque 6 <= Deque 7 : " << ((dequeg <= dequez)?"OUI" : "NON") << std::endl
            << "Deque 6 > Deque 7 : " << ((dequeg > dequez)?"OUI" : "NON") << std::endl
            << "Deque 6 >= Deque 7 : " << ((dequeg >= dequez)?"OUI" : "NON") << std::endl;

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