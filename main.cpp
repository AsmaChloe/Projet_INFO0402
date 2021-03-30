#include <iostream>
#include "classA.h"
#include "deque.h"
#include <deque>

int main() {
    const A a=2;
    const A aBis=4;
    // constructions
    deque<A>   deque1;                                       // défaut
    deque<A>   deque2(13);                             // count
    deque<A>   deque3(2, a);                           // count/value
    deque<A>   deque6( {1,2,3,4,5,6,7} );               //Liste d'initialisation
    deque<A>   deque66( {0,1,2,3,4,5} );                //Liste d'initialisation bis
    deque<A>   deque4(deque6);                              //Copie
    deque<A>   deque5(std::move(deque4));                   //Par déplacement
    deque<A>   deque7(deque6.begin(),deque6.end());         //first/last

    //Vrai deque
    std::deque<A>   dequea;                                 // défaut
    std::deque<A>   dequeb(13);                          // count
    std::deque<A>   dequec(2,a);                         // count/value
    std::deque<A>   dequef( {1,2,3,4,5,6,7} );           //Liste d'initialisation
    std::deque<A>   dequeff( {0,1,2,3,4,5} );            //Liste d'initialisation bis
    std::deque<A>   dequed(dequef);                         //Copie
    std::deque<A>   dequee( std::move(dequed) );            // Par déplacement
    std::deque<A>   dequeg( dequef.begin(), dequef.end() ); // first/last

    /**********TEST CONSTRUCTEUR PAR ITERATEUR*************/
    std::cout<<"***************VRAI DEQUE***************"<<std::endl;
    for(auto it=dequeg.begin();it!=dequeg.end();it++)
        std::cout<<*it<<", ";

    std::cout<<"\ndequeg.assign(dequeff.begin(), dequeff.end())\n";
    dequeg.assign(dequeff.begin(), dequeff.end());

    for(auto it=dequeg.begin();it!=dequeg.end();it++)
        std::cout<<*it<<", ";
    std::cout<<"\n";

    std::cout<<"***************MON DEQUE***************"<<std::endl; //=>CASSE !!!!!!!!!!!
    for(auto it=deque7.begin();it!=deque7.end();it++)
        std::cout<<*it<<", ";

    std::cout<<"\ndeque7.assign(deque66.begin(), dequeff.end())\n";
    deque7.assign(dequeff.begin(), dequeff.end());

    for(auto it=deque7.begin();it!=deque7.end();it++)
        std::cout<<*it<<", ";
    std::cout<<"\n";
    for(int it=0;it<deque7.size();it++)
        std::cout<<deque7[it]<<", ";
    std::cout<<"\n";

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
    std::cout<<"***************VRAI DEQUE***************\n";
    int count=0;
    std::cout<<"Voici dequec : "<<std::endl;
    for (auto it = dequec.begin(); it != dequec.end(); it++) {
        std::cout << *it << ", ";
        count++;
    }
    std::cout<<"\n compte : "<<count;
    count=0;

    std::cout<<"\n\nVoici dequef : "<<std::endl;
    for (auto it = dequef.begin(); it != dequef.end(); it++) {
        std::cout << *it << ", ";
        count++;
    }
    std::cout<<"\n compte : "<<count;
    count=0;

    std::cout<<"\n\nVoici dequeff : "<<std::endl;
    for (auto it = dequeff.begin(); it != dequeff.end(); it++) {
        std::cout << *it << ", ";
        count++;
    }
    std::cout<<"\n compte : "<<count;
    count=0;

    std::deque<A>::iterator iteBegin=dequeff.begin();
    std::cout << "\nIterator pointant sur le premier élément de dequeff : "
              << *iteBegin << std::endl;

    std::cout << "Iterator pointant sur le 2 élément de dequeff : "
              << *(++iteBegin) << std::endl;

    iteBegin++;
    std::cout << "Iterator pointant sur le 3 élément de dequeff : "
              << *(iteBegin) << std::endl;

    std::cout << "Iterator pointant (encore) sur le 2e élément de dequeff : "
              << *(--iteBegin) << std::endl;
    iteBegin--;
    std::cout << "Iterator pointant (encore) sur le 1er élément de dequeff : "
              << *iteBegin << std::endl;

    std::deque<A>::iterator iteEnd = dequeff.end();
    std::cout << "Iterator pointant sur le dernier élément de dequeff : "
              << *iteEnd << std::endl;

    std::cout<<"\n\nComparaison dans dequeff"<<std::endl;
    iteBegin=dequeff.begin();
    iteEnd=dequeff.begin();
    iteEnd++;

    std::cout<<"iteBegin < iteEnd ? "<<(iteBegin<iteEnd)<<std::endl;
    std::cout<<"iteBegin <= iteEnd ? "<<(iteBegin<=iteEnd)<<std::endl;
    std::cout<<"iteBegin > iteEnd ? "<<(iteBegin>iteEnd)<<std::endl;
    std::cout<<"iteBegin >= iteEnd ? "<<(iteBegin>=iteEnd)<<std::endl;

    std::cout<<"\n\n+= et -= dans sur iteBegin"<<std::endl;
    std::cout<<"iteBegin = "<<*iteBegin<<std::endl;
    iteBegin+=3; //0=>3
    std::cout<<"...iteBegin+=3;..."<<std::endl;
    std::cout<<"iteBegin = "<<*iteBegin<<std::endl;
    iteBegin-=3; //3=>0
    std::cout<<"...iteBegin-=3;..."<<std::endl;
    std::cout<<"iteBegin = "<<*iteBegin<<std::endl;

    //MON DEQUE
    std::cout<<"\n\n***************MON DEQUE***************\n";
    std::cout<<"Voici deque3 : "<<std::endl;
    for (auto itt = deque3.begin(); itt != deque3.end(); itt++) {
        std::cout << *itt << ", ";
        count++;
    }
    std::cout<<"\n compte : "<<count;
    count=0;

    std::cout<<"\n\nVoici deque6 : "<<std::endl;
    for (auto itt = deque6.begin(); itt != deque6.end(); itt++) {
        std::cout << *itt << ", ";
        count++;
    }
    std::cout<<"\n compte : "<<count;
    count=0;

    std::cout<<"\n\nVoici deque66 : "<<std::endl;
    for (auto itt = deque66.begin(); itt != deque66.end(); itt++) {
        std::cout << *itt << ", ";
        count++;
    }
    std::cout<<"\n compte : "<<count;

    //deque<A>::iterator itt=deque66.begin();
    /*for(int i=0;i<deque66.size();i++){
        std::cout<<*itt<<" - "<<&itt<<", ";
        itt++;
    }*/

    deque<A>::iterator it5Begin=deque66.begin();
    std::cout << "\nIterator pointant sur le premier élément de deque66 : "
              << *it5Begin << std::endl;

    std::cout << "Iterator pointant sur le 2 élément de deque66 : "
              << *(++it5Begin) << std::endl;

    it5Begin++;
    std::cout << "Iterator pointant sur le 3 élément de deque66 : "
              << *(it5Begin) << std::endl;

    std::cout << "Iterator pointant (encore) sur le 2e élément de deque66 : "
              << *(--it5Begin) << std::endl;
    it5Begin--;
    std::cout << "Iterator pointant (encore) sur le 1er élément de deque66 : "
              << *it5Begin << std::endl;

    deque<A>::iterator it5End = deque66.end();
    /*std::cout << "Iterator pointant sur le dernier élément de deque66 : "         MARCHE PAS
              << *it5End << std::endl;*/

    std::cout<<"\n\nComparaison dans deque66"<<std::endl;
    it5Begin=deque66.begin();
    it5End=deque66.begin();
    it5End++;

    std::cout<<"it5Begin < it5End ? "<<(it5Begin<it5End)<<std::endl;
    std::cout<<"it5Begin <= it5End ? "<<(it5Begin<=it5End)<<std::endl;
    std::cout<<"it5Begin > it5End ? "<<(it5Begin>it5End)<<std::endl;
    std::cout<<"it5Begin >= it5End ? "<<(it5Begin>=it5End)<<std::endl;

    std::cout<<"\n\n+= et -= dans sur it5Begin"<<std::endl;
    std::cout<<"it5Begin = "<<*it5Begin<<std::endl;
    it5Begin+=3; //3=>4
    std::cout<<"...it5Begin+=3;..."<<std::endl;
    std::cout<<"it5Begin = "<<*it5Begin<<std::endl;
    it5Begin-=3; //3=>0
    std::cout<<"...it5Begin-=3;..."<<std::endl;
    std::cout<<"it5Begin = "<<*it5Begin<<std::endl;

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