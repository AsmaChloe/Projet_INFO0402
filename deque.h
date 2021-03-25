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
    int firstPtr; //indice du premier chunk dans le tableau de pointeurs
    int lastPtr; // indice du dernier chunk dans le tableau de pointeurs
    int firstVal; //indice du premier élément du premier chunk
    int lastVal; //indice du dernier élément du premier chunk
public:
    // ne pas toucher
    using value_type = T;
    using size_type = size_t;
    static T dummy;  // pour renvoyer une lvalue lorsque demandé


    deque() :tabLength(0), nbElements(0),firstPtr(-1),lastPtr(-1),firstVal(-1),lastVal(-1) {
        tab=new T*[tabLength];
    }

    explicit deque(size_type count) : nbElements(count) {
        //tabLength= count / chunkLength + count % chunkLength; //A corriger
        tabLength=count/chunkLength;
        if(tabLength*chunkLength<count)
            tabLength++;

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
        //tabLength= count / chunkLength + count % chunkLength; //A corriger
        tabLength=count/chunkLength;
        if(tabLength*chunkLength<count)
            tabLength++;

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
        //tabLength= init.size() / chunkLength + init.size() % chunkLength; //A corriger
        tabLength=init.size()/chunkLength;
        if(tabLength*chunkLength<init.size())
            tabLength++;
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
        if(firstPtr!=-1)
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
        if(firstPtr!=-1) {
            for (i = firstPtr; i <= lastPtr; i++) {
                tab[i] = new T[chunkLength];
                for (j = 0; j < chunkLength; j++) {
                    tab[i][j] = other.tab[i][j];
                }
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
        if(firstPtr!=-1) {
            for (i = firstPtr; i <= lastPtr; i++) {
                tab[i] = other.tab[i];
                //On coupe le lien entre les pointeurs de other et les chunk
                other.tab[i] = nullptr;
            }
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
        //tabLength= ilist.size() / chunkLength + ilist.size() % chunkLength; //A corriger
        tabLength=ilist.size()/chunkLength;
        if(tabLength*chunkLength<ilist.size())
            tabLength++;
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


    T& at( size_type pos ) {
        if(pos>=0 && pos<nbElements){
            return operator[](pos);
        }
        else
            return dummy; /************Ajouter exception : out_of_range**************/
    }
    const T& at( size_type pos ) const {
        if(pos>=0 && pos <nbElements)
            return operator[](pos);
        else
            return dummy; /************Ajouter exception : out_of_range**************/
    }

    T& operator[]( size_type pos ) {
        if(nbElements<1 || pos>=nbElements || pos<0) return dummy;
        int x= (firstPtr + (pos+firstVal)/chunkLength) % tabLength;
        int y= (pos+firstVal) % chunkLength;

        return tab[x][y];
    }
    const T& operator[]( size_type pos ) const {
        if(nbElements<1 || pos>=nbElements || pos<0) return dummy;
        int x= (firstPtr + (pos+firstVal)/chunkLength) % tabLength;
        int y= (pos+firstVal) % chunkLength;

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

    /**
     * Fonction empty pour vérifier si un conteneur est vide ou non
     * @return true ou false
     */
    bool empty() const {
        return (tabLength==0 && nbElements==0 && firstPtr==-1 && lastPtr==-1 && firstPtr==-1 && lastVal==-1);
    }

    /**
     * Fonction size qui permet de savoir la taille d'un deque
     * @return le nombre d'éléments du deque
     */
    size_t size() const { return nbElements; }

    /**
     * Fonction qui supprime le deque (ce qu'il y a à l'intérieur)
     */
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
  
  /**
     * Permet d'ajouter un élément à la fin du conteneur
     * @param value
     */
    void push_back( const T& value ) {
        resize(nbElements+1,value);
    }

     /**
     * Permet d'ajouter un élément à la fin du conteneur
     * @param value
     */
    void push_back(T&& value) {
        const T valeur=value;
        push_back(valeur);
    }

    template< class... Args > void emplace_back( Args&&... args ) {}

    void pop_back() {}

    /**
     * Ajoute un élément au début du conteneur
     * @param value
     */
    void push_front( const T& value ) {
        T** nvTab;
        int i;

        if(firstVal==-1 || (firstPtr==0 && firstVal==0)){ //Si le deque est vide ou complet sur le premier chunk
            //Creation d'un nouveau chunk
            // Si les tableaux pointés sont déjà tous remplis
            tabLength++;

            //Creation d'un nouveau tableau pour la reaoloccation
            nvTab = new T*[tabLength];
            if(firstPtr!=-1) {
                for (i = firstPtr; i <= lastPtr; i++) {
                    nvTab[i+1] = tab[i]; //On reprends les chunk de l'ancien tableau
                    tab[i] = nullptr;
                }
            }
            else{
                //Pour un deque vide
                firstPtr=0;
                firstVal=0;
            }

            //Et on libère la mémoire de l'ancien tableau
            delete[] tab;
            tab = nvTab;

            // Le nouveau chunk
            tab[firstPtr] = new T[chunkLength];
            firstVal=chunkLength-1;
        }
        else{
            if(firstVal==0){ //Si le premier chunk est complet et qu'il n'est pas pointé par tab[0]
                //Remplir le chunk pointé par firstPtr-1
                firstPtr--;
                firstVal=chunkLength-1;
            }
            else{
                //Il y a un trou dans le premier chunk, on le remplit
                firstVal--;
            }
        }
        nbElements++;
        tab[firstPtr][firstVal]=value;
    }

    /**
     * Ajoute un élément au début du conteneur
     * @param value
     */
    void push_front( T&& value ) {
        const T valeur=value;
        push_front(valeur);
    }

    template< class... Args > void emplace_front( Args&&... args ) {}

    void pop_front() {}

    /**
     * Redimensionne le conteneur
     * @param count
     */
    void resize( size_type count ) {
        resize(count,dummy);
    }

    /**
     * Redimensionne le conteneur
     * @param count
     * @param value
     */
    void resize( size_type count, const value_type& value ) {
        T** nvTab;
        int i;
        int remainingSpace;
        int prevLastPtr=lastPtr;
        int prevFirstPtr=firstPtr;

        if(count!=nbElements){
            tabLength=count/chunkLength; //*******VOICI LA VRAI METHODE PR CALCULER LE TAB LENGTH commence ici
            if(tabLength*chunkLength<count)
                tabLength++;
            remainingSpace=tabLength*chunkLength-count; //Dans le chunk, il reste remainingSpace cases vides

            //Creation d'un nouveau tableau pour la reaoloccation
            nvTab = new T*[tabLength];

            if(count<nbElements){//Si on réduit le deque
                nbElements=0;

                //Si il y en a, on reprend les chunk qui ne changent pas, non coupés
                for(i=firstPtr ; i<firstPtr+count/chunkLength ; i++){
                    nvTab[i] = tab[i];
                    nbElements+=chunkLength;
                }
                nvTab[tabLength-1]=new T[chunkLength];

                //Si il y en a, on ajoute les éléments du chunk coupé : le chunk firstPtr+count/chunkLength
                if(count%chunkLength!=0){
                    i=0;
                    while((nbElements<count)==1){
                        nvTab[tabLength-1][i]=tab[firstPtr+count/chunkLength][i];
                        i++;
                        nbElements++;
                    }
                }

                lastVal=chunkLength-remainingSpace-1; // Il y a alors chunkLenght-remainingSpace cases prises => soit l'indice de la derniere case
                lastPtr=tabLength-1;
            }
            else{
                //On reprend tous les chunks
                for(i=firstPtr ; i<=lastPtr ; i++){
                    nvTab[i] = tab[i];
                }

                //Si le deque est vide, on initialise son tableau et on change des attributs
                if(lastPtr==-1 && firstPtr==-1){
                    firstPtr=0;//Le reste des attributs changeront tout seuls par la suite
                    firstVal=0;
                }

                //Si besoin, on remplit le dernier chunk =>Non valide sur un deque vide
                if(lastVal<chunkLength-1 && lastVal!=-1){
                    while(lastVal<chunkLength-1 && nbElements<count){
                        lastVal++;
                        nvTab[lastPtr][lastVal]=value;
                        nbElements++;
                    }
                }

                //Si besoin, on remplit les autres chunks
                if(nbElements<count){
                    while(nbElements!=count){
                        lastPtr++;
                        lastVal=-1;
                        nvTab[lastPtr]=new T[chunkLength];
                        while(lastVal<chunkLength-1 && nbElements<count){
                            lastVal++;
                            nvTab[lastPtr][lastVal]=value;
                            nbElements++;
                        }
                    }
                }
            }
            //On libère la mémoire de l'ancien tableau
            if(prevLastPtr!=-1 && prevFirstPtr!=-1){
                for (i = prevFirstPtr; i <= prevLastPtr; i++) {
                    tab[i] = nullptr;
                }
                delete[] tab;
            }

            tab = nvTab;
        }
    }

    void swap( deque& other ) {}

    /** OPERATEURS **/
    friend bool operator==( const deque& lhs, const deque& rhs ) {
        int i, j, res = true;

        if (lhs.firstPtr == rhs.firstPtr && lhs.lastPtr == rhs.lastPtr){
            i=lhs.firstPtr;
            while(i<=lhs.lastPtr && res==true){
                j=0;
                while(j<chunkLength && res==true){
                    if (lhs.tab[i][j] != rhs.tab[i][j]) {
                        res=false;
                    }
                }
            }
        }
        return res;
    }

    friend bool operator!=( const deque& lhs, const deque& rhs ) {
        return !operator==(lhs,rhs);
    }

    friend bool operator<(  const deque& lhs, const deque& rhs ) {
        int i, j, compt = 0, nbElement = 1, res = false;
        /*if (lhs.firstPtr == rhs.firstPtr && lhs.lastPtr == rhs.lastPtr){
            for(i=lhs.firstPtr;i<=lhs.lastPtr;i++) {
                for(j=0; j<chunkLength; j++) {

                    if (nbElement <= lhs.size()){
                        if (lhs.tab[i][j] < rhs.tab[i][j]) {
                            compt++;
                        }
                    }
                    nbElement++;
                }
            }
            if (compt == lhs.size()){
                res = true;
            }
        }*/
        return res;
    }
    friend bool operator<=( const deque& lhs, const deque& rhs ) {
        return operator==(lhs,rhs) || operator<(lhs,rhs);
    }
    friend bool operator>(  const deque& lhs, const deque& rhs ) {
        return !operator<=(lhs,rhs);
    }
    friend bool operator>=( const deque& lhs, const deque& rhs ) {
        return !operator<(lhs,rhs);
    }

    // iterateur classique
    class iterator {
    public:
        explicit iterator() {

        }
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
    iterator begin() { return tab[firstPtr][firstVal]; }
    iterator end() { return tab[lastPtr][lastVal]; }

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