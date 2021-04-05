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
    deque4.push_back(std::move(a));          //ravlue possible car T=A
    deque4.push_front(b);
    deque4.push_front(std::move(b));        //ravlue possible car T=A

    std::cout<<"deque4 : ";
    for(auto it=deque4.begin();it!=deque4.end();it++)
        std::cout<<*it<<",";
    std::cout<<std::endl;

    //**********POP**********
    std::cout<<"\n\n**********POP**********"<<std::endl;

    std::cout<<"...deque4.pop_back();...\n...deque4.pop_back();...\n...deque4.pop_front();...\n"<<std::endl;
    deque4.pop_back();
    deque4.pop_back();
    deque4.pop_front();

    std::cout<<"deque4 : ";
    for(auto it=deque4.begin();it!=deque4.end();it++)
        std::cout<<*it<<",";
    std::cout<<std::endl;

    //**********TESTS DE COMPARAISON**********
    std::cout<<"\n\n**********TESTS DE COMPARAISON**********"<<std::endl;
    std::cout
            <<"(deque4 == deque5) ? "<< (deque4 == deque5) << "\n"
            <<"(deque4 != deque5) ? "<< (deque4 != deque5) << "\n"
            <<"(deque4 <  deque5) ?"<< (deque4 <  deque5) << "\n"
            <<"(deque4 <= deque5) ? "<< (deque4 <= deque5) << "\n"
            <<"(deque4 >  deque5) ? "<< (deque4 >  deque5) << "\n"
            <<"(deque4 >= deque5) ?"<< (deque4 >= deque5) << std::endl;


    //**********ITERATEUR**********
    std::cout<<"\n\n**********ITERATEUR**********"<<std::endl;

    deque<A>::iterator it6=deque6.begin();
    deque<A>::iterator it6Bis=deque6.begin();
    it6Bis++;

    //Operateur ++ --
    std::cout<<"\n\nPremier élément de deque6: "<<*(it6++)<<std::endl;
    std::cout<<"Deuxieme élément deque6: "<<*it6<<std::endl;
    std::cout<<"Troisieme élément deque6: "<<*(++it6)<<std::endl;
    std::cout<<"Troisieme élément deque6: "<<*(it6--)<<std::endl;
    std::cout<<"Deuxieme élément deque6: "<<*(it6)<<std::endl;
    std::cout<<"Premier élément deque6: "<<*(--it6)<<std::endl;

    //Comparaison
    std::cout<<"\nit6 : "<<*it6<<" - it6Bis : "<<*it6Bis<<std::endl;
    std::cout<<"it6 == it6Bis ? "<<(it6 == it6Bis)<<std::endl;
    std::cout<<"it6 != it6Bis ? "<<(it6 != it6Bis)<<std::endl;

    //Random access
    std::cout<<"it6 < it6Bis ? "<<(it6 < it6Bis)<<std::endl;
    std::cout<<"it6 <= it6Bis ? "<<(it6 <= it6Bis)<<std::endl;
    std::cout<<"it6 > it6Bis ? "<<(it6 > it6Bis)<<std::endl;
    std::cout<<"it6 >= it6Bis ? "<<(it6 >= it6Bis)<<std::endl;

    //+= -=
    std::cout<<"\nit6 : "<<*it6<<"\n ...it6+=3..."<<std::endl;
    it6+=3;
    std::cout<<"it6 : "<<*it6<<"\n...it6-=3..."<<std::endl;
    it6-=3;
    std::cout<<"it6 : "<<*it6<<std::endl;

    //cbegin et cend de cons_iterator
    std::cout<<"\ndeque6 mais c'est avec des const_iterator :"<<std::endl;
    for(auto it=deque6.cbegin();it!=deque6.cend();it++)
        std::cout<<*it<<",";
    std::cout<<std::endl;



    //**********SWAP**********
    std::cout<<"\n\n**********SWAP**********"<<std::endl;

    std::cout<<"...deque4.swap(deque5);...\n"<<std::endl;

    deque4.swap(deque5);

    std::cout<<"deque4 : ";
    for(auto it=deque4.begin(); it!=deque4.end(); ++it) std::cout << *it << ",";
    std::cout << std::endl;

    std::cout<<"deque5 : ";
    for(int i=0; i<deque5.size(); ++i) std::cout << deque5[i] << ",";
    std::cout << std::endl;

    std::cout<<"\n...swap(deque4,deque5);...\n"<<std::endl;
    swap(deque4,deque5);

    std::cout<<"deque4 : ";
    for(auto it=deque4.begin(); it!=deque4.end(); ++it) std::cout << *it << ",";
    std::cout << std::endl;

    std::cout<<"deque5 : ";
    for(auto it=deque5.begin(); it!=deque5.end(); ++it) std::cout << *it << ",";
    std::cout << std::endl;

    return 0;
}