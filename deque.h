//
// Created by asma- on 13/03/2021.
//

#ifndef C_DEQUE_H
#define C_DEQUE_H
#include <cstdio>
#include <functional>
#include <initializer_list>
#define chunkLength 3

template <class T> class deque {
private :
    size_t tabLength; //Longueur du tableau de pointeurs de tableaux
    T** tab;
    size_t nbElements;
    size_t firstPtr; //indice du premier chunk dans le tableau de pointeurs
    size_t lastPtr; // indice du dernier chunk dans le tableau de pointeurs
    size_t firstVal; //indice du premier élément du premier chunk
    size_t lastVal; //indice du dernier élément du premier chunk
public:
    // ne pas toucher
    using value_type = T;
    using size_type = size_t;
    static T dummy;  // pour renvoyer une lvalue lorsque demandé

    // à implémenter
    deque() :tabLength(0), nbElements(0),firstPtr(0),lastPtr(0),firstVal(0),lastVal(0) {
        tab=new T*[tabLength];
    }

    explicit deque(size_type count) : nbElements(count) {
        tabLength= count / chunkLength + count % chunkLength;

        //Initialisation du tableau
        tab=new T*[tabLength];
        for(int i=0;i<tabLength;i++){
            tab[i]=new T[chunkLength];
        }

        //Initialisation des indices
        firstPtr=0;
        lastPtr=(tabLength>0 ? tabLength-1 : 0);
        firstVal=0;
        lastVal=0;
    }

    deque( size_type count, const T&value ) : nbElements(count) {
        tabLength= count / chunkLength + count % chunkLength;

        //Initialisation du tableau
        tab=new T*[tabLength];
        for(int i=0;i<tabLength;i++){
            tab[i]=new T[chunkLength];
        }

        //Ajout des valeurs dans le tableau
        for(int i=0;i<tabLength;i++){
            for(int j=0; j < chunkLength; j++){
                tab[i][j]=value;
            }
        }

        //Initialisation des indices
        firstPtr=0;
        lastPtr=(tabLength>0 ? tabLength-1 : 0);
        firstVal=0;
        lastVal=(count%chunkLength==0? 0 : count%chunkLength-1);
    }

    template< class InputIt > deque( InputIt first, InputIt last) {
        //FAUX ! deque avec tous les éléments de first à last

        /*tabLength = 2;

        tab=new T*[tabLength];

        for(int i=0;i<tabLength;i++){
            tab[i]=new T[chunkLength];
        }

        if (first == NULL || last == NULL){
            std::cout << "Impossible de contruire le deque car une ou plusieurs valeurs sont nulles !" << std::endl;
        }else{
            tab[0][0]=first;
            tab[0][1]=last;
        }*/

    }
    deque( const deque& other ) : tabLength(other.tabLength), nbElements(other.nbElements), firstPtr(other.firstPtr), lastPtr(other.lastPtr), firstVal(other.firstVal), lastVal(other.lastVal) {
        //Initialisation du tableau
        tab=new T*[tabLength];
        for(int i=0;i<tabLength;i++){
            tab[i]=new T[chunkLength];
            for(int j=0; j < chunkLength; j++) {
                tab[i][j] = other.tab[i][j];
                std::cout << "Valeur copié : " << tab[i][j] << std::endl;
            }
        }
    }
    deque( deque&& other ) {}

    deque( std::initializer_list<T> init ) : nbElements(init.size()) {
        int i=0,j=0,count=0;

        //Initialisation du tableau
        tabLength= init.size() / chunkLength + init.size() % chunkLength;
        tab=new T*[tabLength];
        for(i=0;i<tabLength;i++){
            tab[i]=new T[chunkLength];
        }

        //Remplissage
        i=0;
        for(auto &element : init){
            if(count % chunkLength == 0 && count != 0) {
                i++;
                j = 0;
            }
            tab[i][j]=element;
            count++;
            j++;
        }

        //Initialisation des indices
        firstPtr=0;
        lastPtr=tabLength-1;
        firstVal=0;
        lastVal=(init.size()==0 ? 0 : (init.size()%chunkLength)-1);
    }

    ~deque() {
        for(int i=0;i<tabLength;i++){
            delete[] tab[i];
        }
        delete[] tab;
    }

    deque& operator=( const deque& other ) { return *this; }
    deque& operator=( deque&& other ) { return *this; }
    deque& operator=( std::initializer_list<T> ilist ) { return *this; }

    void assign( size_type count, const T& value ) {}
    template< class InputIt > void assign( InputIt first, InputIt last ) {}
    void assign( std::initializer_list<T> ilist ) {}

    T& at( size_type pos ) { return dummy; }
    const T& at( size_type pos ) const { return dummy; }

    T& operator[]( size_type pos ) {
        int x= (firstPtr + (pos+lastVal)/chunkLength) % tabLength;
        int y= (pos+lastVal) % chunkLength;

        return tab[x][y];
    }
    const T& operator[]( size_type pos ) const {
        int x= (firstPtr+ (pos+lastVal)/chunkLength) % tabLength;
        int y= (pos+lastVal) % chunkLength;

        return tab[x][y];
    }

    T& front() { return dummy; }
    const T& front() const { return dummy; }

    T& back() { return dummy; }
    const T& back() const { return dummy; }

    bool empty() const { return false; }

    size_t size() const { return nbElements; }

    void clear() {}


    void push_back( const T& value ) {}
    void push_back( T&& value ) {}

    template< class... Args > void emplace_back( Args&&... args ) {}

    void pop_back() {}

    void push_front( const T& value ) {}
    void push_front( T&& value ) {}

    template< class... Args > void emplace_front( Args&&... args ) {}

    void pop_front() {}

    void resize( size_type count ) {}
    void resize( size_type count, const value_type& value ) {}

    void swap( deque& other ) {}

    friend bool operator==( const deque& lhs, const deque& rhs ) { return true; }
    friend bool operator!=( const deque& lhs, const deque& rhs ) { return true; }
    friend bool operator<(  const deque& lhs, const deque& rhs ) { return true; }
    friend bool operator<=( const deque& lhs, const deque& rhs ) { return true; }
    friend bool operator>(  const deque& lhs, const deque& rhs ) { return true; }
    friend bool operator>=( const deque& lhs, const deque& rhs ) { return true; }

    // iterateur classique
    class iterator {
    public:
        explicit iterator() {}
        iterator(const iterator&) {}
        iterator& operator++() { return *this; }
        iterator operator++(int) { return *this; }
        bool operator==(iterator other) const { return false; }
        bool operator!=(iterator other) const { return false; }
        T& operator*() const { return dummy; };
        //// birectionnel
        // iterator& operator--();
        // iterator operator--(int);
        //// random access
        // bool operator<(const iterator&)  const;
        // bool operator<=(const iterator&) const;
        // bool operator>(const iterator&)  const;
        // bool operator>=(const iterator&) const;
        // iterator& operator+=(const int n)
        // iterator& operator-=(const int n)
        // int& operator[](int n);
        // const int& operator[](int n) const;
    };
    iterator begin() { return iterator(); }
    iterator end() { return iterator(); }

    // iterateur constant
    class const_iterator {
    public:
        explicit const_iterator() {}
        const_iterator(const const_iterator&) {}
        const_iterator(const iterator&) {}
        const_iterator& operator++() { return *this; }
        const_iterator operator++(int) { return *this; }
        bool operator==(const_iterator other) const { return false; }
        bool operator!=(const_iterator other) const { return false; }
        const T& operator*() const { return dummy; };
        //// birectionnel
        // iterator& operator--();
        // iterator operator--(int);
        //// random access
        // bool operator<(const iterator&)  const;
        // bool operator<=(const iterator&) const;
        // bool operator>(const iterator&)  const;
        // bool operator>=(const iterator&) const;
        // iterator& operator+=(const int n)
        // iterator& operator-=(const int n)
        // int& operator[](int n);
        // const int& operator[](int n) const;
    };
    const_iterator cbegin() { return const_iterator(); }
    const_iterator cend() { return const_iterator(); }
    const_iterator begin() const { return const_iterator(); }
    const_iterator end() const { return const_iterator(); }

    // methode necessitant des itérateurs
    iterator insert( const_iterator pos, const T& value ) { return iterator(); }
    iterator insert( const_iterator pos, T&& value ) { return iterator(); }
    iterator insert( const_iterator pos, size_type count, const T& value ) { return iterator(); }
    template< class InputIt > iterator insert( iterator pos, InputIt first, InputIt last) { return iterator(); }
    iterator insert( const_iterator pos, std::initializer_list<T> ilist ) { return iterator(); }

    iterator erase( const_iterator pos ) { return iterator(); }
    iterator erase( const_iterator first, const_iterator last ) { return iterator(); }

    template< class... Args > iterator emplace( const_iterator pos, Args&&... args ) { return iterator(); }

    // autres itérateurs
    /*
    class reverse_iterator {};
    reverse_iterator rbegin(); //
    reverse_iterator rend();   //

    class const_reverse_iterator {};
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;
    */
};

template<class T> void swap( deque<T> &lhs, deque<T> &rhs ) {}

template <class T> T deque<T>::dummy = 0;
#endif //C_DEQUE_H