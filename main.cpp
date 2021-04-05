#include <iostream>
#include <deque>
#include "classA.h"
#include "deque.h"

int main() {
    // constructions
    A a(2);
    A b(6);

    deque<A>   deque1;                                                      // défaut
    deque<A>   deque2(10,a);                                            // count/value
    deque<A>   deque3(deque2.begin(),deque2.end());                         // itérateur
    deque<A>   deque4( deque2 );                                            //Copie
    deque<A>   deque5( std::move(deque4) );                                 //Déplacement
    deque<A>   deque6( {1,2,3,4,5,6} );                                 //Liste d'initialisation

    //**********OPERATEUR=**********
    std::cout<<"**********OPERATEUR=**********"<<std::endl;

    std::cout<<"deque1 : (vide) ";
    for(auto it=deque1.begin();it!=deque1.end();it++)
        std::cout<<*it<<",";
    std::cout<<std::endl;

    std::cout<<"deque2 : ";
    for(auto it=deque2.begin();it!=deque2.end();it++)
        std::cout<<*it<<",";
    std::cout<<std::endl;

    std::cout<<"deque3 : ";
    for(auto it=deque3.begin();it!=deque3.end();it++)
        std::cout<<*it<<",";
    std::cout<<std::endl;

    deque1 = deque6;
    deque2 = std::move(deque1);
    deque3 = { 4, 5, 6, 7};
    std::cout<<"\n...deque1 = deque6;...\n...deque2 = std::move(deque1);...\n...deque3 = { 4, 5, 6, 7};...\n"<<std::endl;

    std::cout<<"deque1 : (vide) ";                          //A cause de deque2=std::move(deque1)
    for(auto it=deque1.begin();it!=deque1.end();it++)
        std::cout<<*it<<",";
    std::cout<<std::endl;

    std::cout<<"deque2 : ";
    for(auto it=deque2.begin();it!=deque2.end();it++)
        std::cout<<*it<<",";
    std::cout<<std::endl;

    std::cout<<"deque3 : ";
    for(auto it=deque3.begin();it!=deque3.end();it++)
        std::cout<<*it<<",";
    std::cout<<std::endl;

    //**********ASSIGN=**********
    std::cout<<"\n\n**********ASSIGN**********"<<std::endl;
    deque1.assign( 5, a);
    deque2.assign( deque1.begin(), deque1.end() );
    deque3.assign( {8,9,10,11} );

    std::cout<<"\n...deque1.assign( 5, a)...\n...deque2.assign( deque1.begin(), deque1.end() );...\n...deque3.assign( {8,9,10,11} );...\n"<<std::endl;

    std::cout<<"deque1 : ";
    for(auto it=deque1.begin();it!=deque1.end();it++)
        std::cout<<*it<<",";
    std::cout<<std::endl;

    std::cout<<"deque2 : ";
    for(auto it=deque2.begin();it!=deque2.end();it++)
        std::cout<<*it<<",";
    std::cout<<std::endl;

    std::cout<<"deque3 : ";
    for(auto it=deque3.begin();it!=deque3.end();it++)
        std::cout<<*it<<",";
    std::cout<<std::endl;

    //**********ACCES AUX ELEMENTS**********
    std::cout<<"\n\n**********ACCES AUX ELEMENTS**********"<<std::endl;
    std::cout<<"deque6 (parcours avec operateur [] : "<<std::endl;
    for(int i=0;i<deque6.size();i++)
        std::cout<<deque6[i]<<", ";
    std::cout<<std::endl;

    const deque<A>&deque6const = deque6;
    std::cout<<"deque6const (parcours avec operateur at : "<<std::endl;
    for(int i=0;i<deque6const.size();i++)
        std::cout<<deque6const.at(i)<<", ";
    std::cout<<std::endl;

    std::cout
            <<"\nLe premier élément de deque6 : "<<deque6.front() << "\n"
            <<"Le premier élément de deque6const : "<<deque6const.front() << "\n"
            <<"Le dernier élément de deque6 : "<<deque6.back()  << "\n"
            <<"Le dernier élément de deque6const : "<<deque6const.back()  << "\n"
            <<"Test si deque6 est vide : "<<deque6.empty() << std::endl;

    //**********CLEAR & RESIZE**********
    std::cout<<"\n\n**********CLEAR & RESIZE**********"<<std::endl;

    std::cout<<"...deque5.clear();...\n...deque5.resize(10);...\n...deque4.resize(6,4);...\n"<<std::endl;

    deque5.clear();
    deque5.resize(10);
    deque4.resize(6,4);

    std::cout<<"deque5 : ";
    for(auto it=deque5.begin();it!=deque5.end();it++)
        std::cout<<*it<<",";
    std::cout<<std::endl;

    std::cout<<"deque4 : ";
    for(auto it=deque4.begin();it!=deque4.end();it++)
        std::cout<<*it<<",";
    std::cout<<std::endl;

    //**********PUSH**********
    std::cout<<"\n\n**********PUSH**********"<<std::endl;

    std::cout<<"...deque4.push_back(a);...\n...deque4.push_back(std::move(a));...\n...deque4.push_front(b);...\ndeque4.push_front(std::move(b));...\n"<<std::endl;
    deque4.push_back(a);
    deque4.push_back(std::move(a));         //rvalue possible car T=A
    deque4.push_front(b);
    deque4.push_front(std::move(b));        //ravlue possible car T=A

    std::cout<<"deque4 : ";
    for(auto it=deque4.begin();it!=deque4.end();it++)
        std::cout<<*it<<",";
    std::cout<<std::endl;

    //**********POP**********
    std::cout<<"\n\n**********POP**********"<<std::endl;

    std::cout<<"...deque4.pop_back();...\n...deque4.pop_front();...\n"<<std::endl;
    deque4.pop_back();
    //deque4.pop_front();

    std::cout<<"deque4 : ";
    for(auto it=deque4.begin();it!=deque4.end();it++)
        std::cout<<*it<<",";
    std::cout<<std::endl;

    // tests
    /*std::cout
            << (deque4 == deque5) << ", "
            << (deque4 != deque5) << ", "
            << (deque4 <  deque5) << ", "
            << (deque4 <= deque5) << ", "
            << (deque4 >  deque5) << ", "
            << (deque4 >= deque5) << std::endl;

    // iterateurs
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
    std::cout<<"\ndeque4 avant les swap"<<std::endl;
    for(auto it=deque4.begin(); it!=deque4.end(); ++it) std::cout << *it << ",";
    std::cout << std::endl;

     std::cout<<"\ndeque5 avant les swap"<<std::endl;
    for(auto it=deque5.begin(); it!=deque5.end(); ++it) std::cout << *it << ",";
    std::cout << std::endl;

    deque4.swap(deque5);


    std::cout<<"\ndeque4 entre les swap"<<std::endl;
    for(auto it=deque4.begin(); it!=deque4.end(); ++it) std::cout << *it << ",";
    std::cout << std::endl;

    std::cout<<"\ndeque5 entre les swap"<<std::endl;
    for(int i=0; i<deque5.size(); ++i) std::cout << deque5[i] << ",";
    std::cout << std::endl;

    swap(deque4,deque5);

    std::cout<<"\ndeque4 apres les swap"<<std::endl;
    for(auto it=deque4.begin(); it!=deque4.end(); ++it) std::cout << *it << ",";
    std::cout << std::endl;

    std::cout<<"\ndeque5 apres les swap"<<std::endl;
    for(auto it=deque5.begin(); it!=deque5.end(); ++it) std::cout << *it << ",";
    std::cout << std::endl;*/

    //swap(deque1,deque2);


    return 0;
}