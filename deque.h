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


    deque() :tabLength(0), nbElements(0),firstPtr(-1),lastPtr(-1),firstVal(-1),lastVal(-1) {
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
        firstVal=-1;
        lastVal=-1;
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
        lastVal=(count%chunkLength==0? chunkLength-1 : count%chunkLength-1);
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
            }
        }
    }

    //Constructeur par déplacement
    deque( deque&& other ) : tabLength(other.tabLength), nbElements(other.nbElements), firstPtr(other.firstPtr), lastPtr(other.lastPtr), firstVal(other.firstVal), lastVal(other.lastVal) {

        //Initialisation du tableau
        tab=new T*[tabLength];
        for(int i=0;i<tabLength;i++){
            tab[i]=other.tab[i];
            other.tab[i]=nullptr;
        }

        other.tab= nullptr;
        other.firstVal=-1;
        other.lastVal=-1;
        other.firstPtr=-1;
        other.lastPtr=-1;
        other.nbElements=0;
        other.tabLength=0;
    }

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

        if(init.size()==0){ //Liste vide
            firstPtr=-1;
            lastPtr=-1;
            firstVal=-1;
            lastVal=-1;
        }
        else{
            firstPtr=0;
            lastPtr=tabLength-1;
            firstVal=0;
            if(init.size()%chunkLength==0)
                lastVal=chunkLength-1;
            else
                lastVal=(init.size()%chunkLength)-1;
        }
    }

    ~deque() {
        if(tab!=nullptr) {
            for (int i = 0; i < tabLength; i++) {
                if (tab[i] != nullptr) delete[] tab[i];
            }
        }
        delete[] tab;
    }


    deque& operator=( const deque& other ) {
        int i, j;

        //On vide les valeurs de base
        for (i = firstPtr; i<=lastPtr; i++)
            delete[] tab[i];
        delete[]tab;

        nbElements = other.nbElements;
        firstPtr = other.firstPtr;
        lastPtr = other.lastPtr;
        firstVal = other.firstVal;
        lastVal = other.lastVal;
        tabLength = other.tabLength;

        //On copie les valeurs de other
        tab=new T*[tabLength];
        for (i = firstPtr; i <=lastPtr; i++) {
            tab[i]=new T[chunkLength];
            for (j = 0; j < chunkLength; j++) {
                tab[i][j] = other.tab[i][j];
            }
        }

        return *this;
    }

    deque& operator=( deque&& other ) {
        int i, j;

        //On vide l'objet de base
        for(i=firstPtr;i<=lastPtr;i++)
            delete[] tab[i];
        delete[] tab;

        //On reprend les valeurs des attributs
        nbElements = other.nbElements;
        firstPtr = other.firstPtr;
        lastPtr = other.lastPtr;
        firstVal = other.firstVal;
        lastVal = other.lastVal;
        tabLength = other.tabLength;

        //On fait pointer nos pointeurs sur les chunk de other
        tab= new T*[tabLength];
        for (i = firstPtr; i <=lastPtr; i++) {
            tab[i]=other.tab[i];
            //On coupe le lien entre les pointeurs de other et les chunk
            other.tab[i]= nullptr;
        }

        other.firstVal=-1;
        other.lastVal=-1;
        other.firstPtr=-1;
        other.lastPtr=-1;
        other.nbElements=0;
        other.tabLength=0;

        return *this;
    }
    deque& operator=( std::initializer_list<T> ilist ) {
        int i, j, count=0;

        //On vide l'objet de base
        for(i=firstPtr;i<=lastPtr;i++)
            delete[] tab[i];
        delete[] tab;

        //On récupère les indices
        tabLength= ilist.size() / chunkLength + ilist.size() % chunkLength;
        nbElements=ilist.size();
        if(ilist.size()==0){ //Dans le cas d'une liste vide
            firstPtr=-1;
            lastPtr=-1;
            firstVal=-1;
            lastVal=-1;
        }
        else{
            firstPtr=0;
            lastPtr=tabLength-1;
            firstVal=0;
            if(ilist.size()%chunkLength==0)
                lastVal=chunkLength-1;
            else
                lastVal=(ilist.size()%chunkLength)-1;
        }

        //Reallocation du tableau
        tab=new T*[tabLength];
        for(i=0;i<tabLength;i++){
            tab[i]=new T[chunkLength];
        }

        //Remplissage
        i=0;
        j=0;
        for(auto &element : ilist){
            if(count % chunkLength == 0 && count != 0) {
                i++;
                j = 0;
            }
            tab[i][j]=element;
            count++;
            j++;
        }

        return *this;
    }

    void assign( size_type count, const T& value ) {
        //On vide l'objet courant
        clear();

        //Creation d'un nouvel objet selon les paramètres
        deque<T> nvDeque(count,value);

        //Nouveaux indices
        tabLength=nvDeque.tabLength;
        nbElements=nvDeque.nbElements;
        firstPtr=nvDeque.firstPtr;
        lastPtr=nvDeque.lastPtr;
        firstVal=nvDeque.firstVal;
        lastVal=nvDeque.lastVal;
    }

    template< class InputIt > void assign( InputIt first, InputIt last ) {}

    void assign( std::initializer_list<T> ilist ) {
        //On vide l'objet courant
        clear();

        //Creation d'un nouvel objet selon les paramètres
        deque<T> nvDeque(ilist);

        //Nouveaux indices
        tabLength=nvDeque.tabLength;
        nbElements=nvDeque.nbElements;
        firstPtr=nvDeque.firstPtr;
        lastPtr=nvDeque.lastPtr;
        firstVal=nvDeque.firstVal;
        lastVal=nvDeque.lastVal;
    }

    //Contrairement à operator[], at check si pos se trouve dans les bornes du deque et retour une exception si ce n'est pas le cas
    //Se renseigner sur les exceptions ?? Ou  on verra plus tard ?? =>Je crois qu'on en parle des les derniers CM
    T& at( size_type pos ) {
        if(pos>=0 && pos<nbElements){
            return operator[](pos);
        }
        else
            return dummy; //????????????????????????
    }
    const T& at( size_type pos ) const {
        if(pos>=0 && pos <nbElements)
            return operator[](pos);
        else
            return dummy; //???????????????????????
    }

    T& operator[]( size_type pos ) {
        if(nbElements<1 || pos>=nbElements || pos<0) return dummy;
        int x= (firstPtr + (pos+lastVal)/chunkLength) % tabLength;
        int y= (pos+lastVal) % chunkLength;

        return tab[x][y];
    }
    const T& operator[]( size_type pos ) const {
        if(nbElements<1 || pos>=nbElements || pos<0) return dummy;
        int x= (firstPtr+ (pos+lastVal)/chunkLength) % tabLength;
        int y= (pos+lastVal) % chunkLength;

        return tab[x][y];
    }

    /******* A RESOUDRE : Presence de warning lié au retour manquant dans le cas où les if ne sont pas à true**********/
    T& front() {
        if(firstVal!=-1 && firstPtr!=-1)
            return tab[firstPtr][firstVal];
    }
    const T& front() const {
        if(firstVal!=-1 && firstPtr!=-1)
            return tab[firstPtr][firstVal];
    }

    T& back() {
        if(lastVal!=-1 && lastPtr!=-1)
            return tab[lastPtr][lastVal];
    }
    const T& back() const {
        if(lastVal!=-1 && lastPtr!=-1)
            return tab[lastPtr][lastVal];
    }

    bool empty() const {
        return (tabLength==0 && nbElements==0 && firstPtr==-1 && lastPtr==-1 && firstPtr==-1 && lastVal==-1);
    }

    size_t size() const { return nbElements; }

    void clear() {
        //On vide
        for (int i = firstPtr; i <= lastPtr; i++)
            if (tab[i] != nullptr) delete[] tab[i];
        if (tab != nullptr)
            delete[] tab;
        tab = nullptr;

        //Mise à 0 des attributs
        tabLength = nbElements = 0;
        firstVal = lastVal = firstPtr = lastPtr = -1;
    }

    void push_back( const T& value ) {}

    void push_back( T&& value ) {
        size_t remainingSpace=nbElements%chunkLength; //Si=0, il n'y a plus de place, sinon ça vaut l'indice où sera placé le nouvel élément
        T** nvTab;
        int i,j;

        if(remainingSpace==0) {//Si les tableaux pointés sont déjà tous remplis
            std::cout<<"==0"<<std::endl;
            /*Selon le prof:
             * "Par contre, si lors de  l'ajout d'un nouveau chunk, le tableau de pointeurs est plein,
             * c'est ce dernier qui est réalloué (et donc recopié) dans un nouveau tableau plus grand. L'avantage est qu'il est beaucoup
             * plus rapide de copier un tableau de pointeurs qu'un tableau d'éléments (jamais de deep copy) dès que la taille d'un élément
             * est supérieure ou égale à la taille d'un pointeur."
             */
            //Creation d'un tableau de pointeurs plus grand
            for (i = firstPtr; i <= lastPtr; i++) {
                nvTab[i] = new T[chunkLength];
                nvTab[i] = tab[i];
            }
            nvTab[lastPtr + 1] = new T[chunkLength];

            for (int i = firstPtr; i <= lastPtr; i++) {
                if (tab[i] != NULL)
                    delete[] tab[i];
            }

            tabLength++;
            lastPtr++;
        }
        //Ajout du dernier élément
        tab[lastPtr][remainingSpace]=value;
        std::cout<<"Debut : "<<tab[firstPtr][firstVal]<<" - Fin : "<<tab[lastPtr][remainingSpace]<<std::endl;
        nbElements++;
        lastVal=remainingSpace;
    }

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