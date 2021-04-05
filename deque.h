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
    /**
     * Tableau 2D, le deque
     */
    T** tab;

    /**
     * Longueur du tableau de pointeurs
     */
    size_t tabLength;

    /**
     * Nombre d'éléments contenus dans le deque
     */
    size_t nbElements;

    /**
     * Indice du premier chunk dans le tableau de pointeurs
     */
    int firstPtr;

    /**
     * Indice du dernier chunk dans le tableau de pointeurs
     */
    int lastPtr;

    /**
     * Indice du premier élément du premier chunk
     */
    int firstVal;

    /**
     * Indice du dernier élément du premier chunk
     */
    int lastVal;

public:
    // ne pas toucher
    using value_type = T;
    using size_type = size_t;
    static T dummy;  // pour renvoyer une lvalue lorsque demandé

    /**
     * Constructeur par défaut. Construit un conteneur vide.
     */
    deque() :tabLength(0), nbElements(0),firstPtr(-1),lastPtr(-1),firstVal(-1),lastVal(-1), tab(nullptr) {}

    /**
     * Construit le conteneur avec count instances de T initialisées par dummy.
     * @param count - Le nombre d'éléments
     */
    explicit deque(size_type count) {
        deque(count,dummy);
    }

    /**
     * Construit le conteneur avec count copies de value.
     * @param count - Le nombre d'éléments
     * @param value - La valeur d'initialisation des éléments du conteneur
     */
    deque( size_type count, const T&value ) : nbElements(count) {
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

    /**
     * Construit le conteneur avec les éléments de [first, last).
     * @tparam InputIt
     * @param first - Début de la plage d'éléments à copier
     * @param last - fin de la plage d'élément à copier
     */
    template< class InputIt > deque( InputIt first, InputIt last) {
        int count=0;
        nbElements=0;
        InputIt it=first;

        //On compte le nombre d'éléments se trouvant entre first et last
        while (it!=last){
            it++;
            nbElements++;
        }

        //Definition du tabLength
        tabLength=nbElements/chunkLength;
        if(tabLength*chunkLength<nbElements)
            tabLength++;

        //Initialisation du tableau
        tab=new T*[tabLength];
        for(int i=0;i<tabLength;i++){
            tab[i]=new T[chunkLength];
        }

        //Initialisation des indices
        firstPtr=0;
        firstVal=0;
        lastPtr=firstPtr;
        lastVal=firstVal-1; //On va un cran plus loin => nous evite de faire un tour en trop

        //Ajout des valeurs dans le tableaux;
        while(count!=nbElements && lastPtr<tabLength){

            if(lastVal==chunkLength-1){ //Si on est au bout du chunk
                lastVal=0;
                lastPtr++;
            }
            else{
                lastVal++;
            }

            tab[lastPtr][lastVal]=*first;
            first++; //On déplace l'itérateur
            count++;
        }
    }

    /**
     * Constructeur par copie. Construit le conteneur avec la copie des éléments de other.
     * @param other - Autre conteneur à copier
     */
    deque( const deque& other ) : tabLength(other.tabLength), nbElements(other.nbElements), firstPtr(other.firstPtr), lastPtr(other.lastPtr), firstVal(other.firstVal), lastVal(other.lastVal) {
        //Initialisation du tableau
        tab=new T*[tabLength];
        for(int i=firstPtr;i<=lastPtr;i++){
            tab[i]=new T[chunkLength];
            for(int j=0; j < chunkLength; j++) {
                tab[i][j] = other.tab[i][j];
            }
        }
    }

    /**
     * Constructeur par déplacement. Construit le conteneur avec le contenu de other en déplaçant les éléments.
     * @param other - Autre conteneur à copier, on videra son contenu
     */
    deque( deque&& other ) : tabLength(other.tabLength), nbElements(other.nbElements), firstPtr(other.firstPtr), lastPtr(other.lastPtr), firstVal(other.firstVal), lastVal(other.lastVal) {

        //Initialisation du tableau
        tab=new T*[tabLength];
        for(int i=firstPtr;i<=lastPtr;i++){
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

    /**
     * Construit le conteneur avec le contenu de la liste d'initialisation init.
     * @param init - Liste d'initialisation utilisée pour initialiser les éléments du conteneur
     */
    deque( std::initializer_list<T> init ) : nbElements(init.size()) {
        int i=0,j=0,count=0;


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

    /**
     * Destructeur
     */
    ~deque() {
        if(tab!=nullptr && firstPtr!=-1 && lastPtr!=-1) {
            for (int i = firstPtr; i <= lastPtr; i++) {
                if (tab[i] != nullptr) {
                    delete[] tab[i];
                    tab[i] = nullptr;
                }
            }
        }
        if(tab!=nullptr) {
            delete[] tab;
            tab = nullptr;
        }
    }

    /**
     * Cette méthode copie le contenu de other dans l'objet courant
     * @param other - le conteneur source
     * @return *this
     */
    deque& operator=( const deque& other ) {
        int i, j,k=0;

        //On réalloue l'objet
        this->resize(other.tabLength*chunkLength);

        //On copie les indices
        firstPtr=other.firstPtr;
        lastPtr=other.lastPtr;
        firstVal=other.firstVal;
        lastVal=other.lastVal;

        tabLength=other.tabLength;
        nbElements=other.nbElements;

        //On copie les valeurs de other
        if(firstPtr!=-1) {
            for (i = firstPtr; i <= lastPtr; i++) {
                for (j = 0; j < chunkLength; j++) {
                    tab[i][j] = other[k];
                    k++;
                }
            }
        }
        return *this;
    }

    /**
     * Cette méthode déplace le contenu de other dans l'objet courant. Other sera vidé.
     * @param other - le conteneur source, vidé de son contenu.
     * @return *this
     */
    deque& operator=( deque&& other ) {
        clear();
        deque<T> tmp_deque(std::move(other));
        *this = tmp_deque;
        return *this;
    }

    /**
     * Cette méthode copie le contenu de la liste d'initialisation dans l'objet courant
     * @param ilist - Liste d'initialisation avec les valeurs à copier
     * @return *this
     */
    deque& operator=( std::initializer_list<T> ilist ) {
        clear();
        deque<T> tmp_deque(ilist);
        *this = tmp_deque;
        return *this;

    }

    /**
     * Cette méthode remplace le contenu du conteneur avec count éléments de valeur value
     * @param count - nombre d'éléments
     * @param value - la valeur des éléments
     */
    void assign( size_type count, const T& value ) {
        //On vide l'objet courant
        clear();

        //Creation d'un nouvel objet selon les paramètres
        deque<T> nvDeque(count,value);

        //Notre objet courant devient le nouvel objet
        *this=nvDeque;
    }

    /**
     * Cette méthode remplace les éléments du conteneurs avec les valeurs comprises dans la place [first, last[
     * @tparam InputIt
     * @param first - Début de la plage d'éléments à copier
     * @param last - fin de la plage d'élément à copier
     */
    template< class InputIt > void assign( InputIt first, InputIt last ) {
        //On vide l'objet courant
        clear();

        //Creation d'un nouvel objet selon les paramètres
        deque<T> nvDeque(first,last);

        //Notre objet courant devient le nouvel objet
        *this=nvDeque;
    }

    /**
     * Cette méthode remplace les éléments du conteneurs avec les valeurs de la liste d'initialisation ilist
     * @param ilist - liste d'initialisation avec les valeurs à prendre
     */
    void assign( std::initializer_list<T> ilist ) {
        //On vide l'objet courant
        clear();

        //Creation d'un nouvel objet selon les paramètres
        deque<T> nvDeque(ilist);

        //Notre objet courant devient le nouvel objet
        *this=nvDeque;
    }

    /**
     * Cette méthode renvoie l'élément à la position pos. La vérification des limites est effectuée.
     * @param pos - position de l'élément
     * @return - L'élément à la position pos
     */
    T& at( size_type pos ) {
        if(pos>=0 && pos<nbElements){
            return operator[](pos);
        }
        else {
            std::cout << "Position invalide" << std::endl; //On aurait pu gérer ça avec une exception out_of_range
            return dummy;
        }
    }

    /**
     * Cette méthode renvoie l'élément à la position pos. La vérification des limites est effectuée. Sur un conteneur const.
     * @param pos - position de l'élément
     * @return - L'élément à la position pos
     */
    const T& at( size_type pos ) const {
        if(pos>=0 && pos <nbElements)
            return operator[](pos);
        else {
            std::cout << "Position invalide" << std::endl; //On aurait pu gérer ça avec une exception out_of_range
            return dummy;
        }
    }

    /**
     * Cette méthode renvoie l'élément à la position pos. La validité de pos n'est pas vérifiée.
     * @param pos - la position de l'élément
     * @return l'élément à la position pos
     */
    T& operator[]( size_type pos ) {
        if(nbElements<1 || pos>=nbElements || pos<0) return dummy;
        int x= (firstPtr + (pos+firstVal)/chunkLength) % tabLength;
        int y= (pos+firstVal) % chunkLength;

        return tab[x][y];
    }

    /**
     * Cette méthode renvoie l'élément à la position pos. La validité de pos n'est pas vérifiée. Sur un conteneur const.
     * @param pos - la position de l'élément
     * @return l'élément à la position pos
     */
    const T& operator[]( size_type pos ) const {
        if(nbElements<1 || pos>=nbElements || pos<0) return dummy;
        int x= (firstPtr + (pos+firstVal)/chunkLength) % tabLength;
        int y= (pos+firstVal) % chunkLength;

        return tab[x][y];
    }

    /**
     * Cette méthode renvoie une référence au premier élément dans le conteneur .
     * @return le premier élément du conteneur
     */
    T& front() {
        if(firstVal!=-1 && firstPtr!=-1)
            return tab[firstPtr][firstVal];
    }

    /**
     * Cette méthode renvoie une référence au premier élément dans le conteneur . Dans un conteneur constant.
     * @return le premier élément du conteneur
     */
    const T& front() const {
        if(firstVal!=-1 && firstPtr!=-1)
            return tab[firstPtr][firstVal];
    }

    /**
     * Cette méthode retourne référence au dernier élément dans le conteneur .
     * @return le dernier élément du conteneur
     */
    T& back() {
        if(lastVal!=-1 && lastPtr!=-1)
            return tab[lastPtr][lastVal];
    }

    /**
     * Cette méthode retourne référence au dernier élément dans le conteneur . Dans un conteneur constant.
     * @return le dernier élément du conteneur
     */
    const T& back() const {
        if(lastVal!=-1 && lastPtr!=-1)
            return tab[lastPtr][lastVal];
    }

    /**
     * La méthode empty vérifie si un conteneur est vide ou non
     * @return true si il est vide, false s'il ne l'est pas
     */
    bool empty() const {
        return (tabLength==0 && nbElements==0 && firstPtr==-1 && lastPtr==-1 && firstPtr==-1 && lastVal==-1);
    }

    /**
     * La méthode size retourne la taille du conteneur
     * @return le nombre d'éléments du deque
     */
    size_t size() const { return nbElements; }

    /**
     * Cette méthode supprime tous les éléments du conteneur.
     */
    void clear() {
        //On vide
        if(firstPtr!=-1 && lastPtr!=-1){
            for (int i = firstPtr; i <= lastPtr; i++)
                if (tab[i] != nullptr) delete[] tab[i];
            if (tab != nullptr)
                delete[] tab;
            tab = nullptr;
        }


        //Mise à 0 des attributs
        tabLength = nbElements = 0;
        firstVal = lastVal = firstPtr = lastPtr = -1;
    }

      /**
     * Cette méthode permet d'ajouter un élément à la fin du conteneur
     * @param value - l'élément à ajouter, une lvalue
     */
    void push_back( const T& value ) {
        resize(nbElements+1,value);
    }

     /**
     * Cette méthode permet d'ajouter un élément à la fin du conteneur
     * @param value - l'élément à ajouter, une rvalue
     */
    void push_back(T&& value) {
        const T valeur=value;
        push_back(valeur);
    }

    /**
     * Ajoute un nouvel élément à la fin du récipient. Contrairement à push_back, il n'y a pas de copie ou les opérations de déplacement.
     * @tparam Args
     * @param args - arguments à transmettre au constructeur de l'élément
     */
    template< class... Args > void emplace_back( Args&&... args ) {
        push_back(args...);
    }

    /**
     * Cette méthode retire un élément à la fin du deque
     */
    void pop_back() {
        //On ne vérifie pas si le deque est vide => selon la documentation on a un undefined behaviour si le conteneur est vide.
        if(nbElements<1) return;
        lastVal--;
        if(lastVal==-1){
            lastPtr--;
            lastVal=chunkLength-1;
        }
        nbElements--;
    }

    /**
     * Ajoute un élément au début du conteneur
     * @param value - l'élément à ajouter, ici une lvalue
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
                firstVal=chunkLength-1;
                lastPtr++;
            }
            else{
                //Pour un deque vide
                firstPtr=lastPtr=firstVal=lastVal=0;
            }

            //Et on libère la mémoire de l'ancien tableau
            delete[] tab;
            tab = nvTab;

            // Le nouveau chunk
            tab[firstPtr] = new T[chunkLength];
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
     * Cette méthode ajoute un élément au début du conteneur
     * @param value - l'élément à ajouter, ici une rvalue
     */
    void push_front( T&& value ) {
        const T valeur=value;
        push_front(valeur);
    }

    /**
     * Ajoute un nouvel élément au début du récipient. Contrairement à push_front, il n'y a pas de copie ou les opérations de déplacement.
     * @tparam Args
     * @param args
     */
    template< class... Args > void emplace_front( Args&&... args ) {
        push_front(args...);
    }

    /**
     * Cette méthode retire le premier élément du conteneur
     */
    void pop_front() {
        tab[firstPtr][firstVal]=dummy;

        //Si la premier valeur se trouve au bout d'un chunk
        if(firstVal==chunkLength-1) {
            firstVal = 0;
            firstPtr++;
        }
        else
            firstVal++;

        nbElements--;
    }

    /**
     * Cette méthode redimensionne le conteneur pour contenir count éléments. Si on augmente la taille, on ajoute des éléments de valeurs dummy. Si on réduit la taille, on garde ses count premier éléments.
     * @param count - Le nombre d'élément à avoir après la redimension
     */
    void resize( size_type count ) {
        resize(count,dummy);
    }

    /**
     * * Cette méthode redimensionne le conteneur pour contenir count éléments. Si on augmente la taille, on ajoute des éléments de valeurs value. Si on réduit la taille, on garde ses count premier éléments.
     * @param count - Le nombre d'élément à avoir après la redimension
     * @param value - La valeur des éléments à ajouter
     */
    void resize( size_type count, const value_type& value ) {
        T** nvTab;
        int i;
        int prevLastPtr=lastPtr;
        int prevFirstPtr=firstPtr;

        if(count!=nbElements){
            tabLength=count/chunkLength;
            if(tabLength*chunkLength<count)
                tabLength++;

            //Creation d'un nouveau tableau pour la reaoloccation
            nvTab = new T*[tabLength];
            if(count<nbElements){//Si on réduit le deque
                nbElements=0;

                //Si il y en a, on reprend les chunk qui ne changent pas, non coupés
                for(i=firstPtr ; i<firstPtr+count/chunkLength ; i++){
                    nvTab[i] = tab[i];

                    if(i==firstPtr){ //Il se peut que le premier chunk ne soit pas complet
                        nbElements+=chunkLength-firstVal;
                        lastVal=chunkLength-1;
                    }
                    else{
                        nbElements+=chunkLength;
                        lastVal=(lastVal+chunkLength)%chunkLength;
                    }
                }

                //Si il y en a, on ajoute les éléments du chunk coupé : le chunk firstPtr+count/chunkLength
                if(count%chunkLength!=0){
                    nvTab[tabLength-1]=new T[chunkLength]; //Creation d'un chunk vierge

                    i=0;
                    while(nbElements<count){

                        nvTab[tabLength-1][i]=tab[firstPtr+count/chunkLength][i];
                        lastVal=i;
                        i++;
                        nbElements++;

                    }

                }

                lastPtr=tabLength-1;
            }
            else{
                //On reprend tous les chunks
                if(firstPtr!=-1 && lastPtr!=-1)
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

    /**
     * Cette méthode échange le contenu de l'objet courant avec l'objet passé en paramètre other.
     * @param other - objet à échanger avec l'objet courant
     */
    void swap( deque& other ){
        deque<T>tmp(std::move(*this));
        *this=std::move(other);
        other=tmp;
    }

    /**
     * Cet méthode retourne si deux conteneurs sont égaux
     * @param lhs - conteneur de gauche
     * @param rhs - conteneur de droite
     * @return true si c'est vrai, false si c'est faux
     */
    friend bool operator==( const deque& lhs, const deque& rhs ) {
        int i, j, res = true;

        if(lhs.size() != rhs.size()){
            return false;
        }

        if (lhs.firstPtr == rhs.firstPtr && lhs.lastPtr == rhs.lastPtr){
            i=lhs.firstPtr;
            while(i<=lhs.lastPtr && res==true){
                j=0;
                while(j<chunkLength && res==true){
                    if (lhs.tab[i][j] != rhs.tab[i][j]) {
                        res=false;
                    }
                    j++;
                }
                i++;
            }
        }
        return res;
    }

    /**
     * Cette méthode retourne si deux conteneurs sont différents
     * @param lhs - conteneur de gauche
     * @param rhs - conteneur de droite
     * @return true si c'est vrai, false si c'est faux
     */
    friend bool operator!=( const deque& lhs, const deque& rhs ) {
        return !operator==(lhs,rhs);
    }

    /**
     * Cette méthode retourne si le conteneur à gauche de l'égalité est strictement inférieur au conteneur à droite.
     * @param lhs - conteneur de gauche
     * @param rhs - conteneur de droite
     * @return true si c'est vrai, false si c'est faux
     */
    friend bool operator<(  const deque& lhs, const deque& rhs ) {
        int i;
        i=0;

        while(i<lhs.size() && i<rhs.size()){
            if(lhs[i]<rhs[i])
                return true;
            else if (lhs[i]>rhs[i])
                return false;
            else
                i++;
        }

        if(i==lhs.size())
            if(i==rhs.size()) //C'est les meme deque
                return false;
            else
                return true; //rhs est plus long, donc lhs est plus petit
        else //lhs est plus long, lhs est pas plus petit
            return false;
    }

    /**
     * Cette méthode retourne si le conteneur à gauche de l'égalité est inférieur ou égal au conteneur à droite.
     * @param lhs - conteneur de gauche
     * @param rhs - conteneur de droite
     * @return true si c'est vrai, false si c'est faux
     */
    friend bool operator<=( const deque& lhs, const deque& rhs ) {
        return operator==(lhs,rhs) || operator<(lhs,rhs);
    }

    /**
     * Cette méthode retourne si le conteneur à gauche de l'égalité est strictement supérieur au conteneur à droite.
     * @param lhs - conteneur de gauche
     * @param rhs - conteneur de droite
     * @return true si c'est vrai, false si c'est faux
     */
    friend bool operator>(  const deque& lhs, const deque& rhs ) {
        return !operator<=(lhs,rhs);
    }

    /**
     * Cette méthode retourne si le conteneur à gauche de l'égalité est supérieur ou égal au conteneur à droite.
     * @param lhs - conteneur de gauche
     * @param rhs - conteneur de droite
     * @return true si c'est vrai, false si c'est faux
     */
    friend bool operator>=( const deque& lhs, const deque& rhs ) {
        return !operator<(lhs,rhs);
    }

    //**********************************IERATEUR CLASSIQUES**********************************
    /**
     * La classe iterator permet de parcourir un conteneur
     */
    class iterator {
    public:
        //Attributs
        /**
         * Pointeur sur le chunk courant
         */
        T** currentChunk;
        /**
         * L'indice de l'élément courant dans le chunk courant
         */
        int currentIndex;

        /**
         * Constructeur par défaut
         */
        explicit iterator() : currentChunk(nullptr), currentIndex(0) {}

        /**
         * Constructeur par copie
         * @param other - itérator à copier
         */
        iterator(const iterator& other) : currentChunk(other.currentChunk), currentIndex(other.currentIndex){}

        /**
         * Cette méthode déplace l'itérateur d'un cran vers l'avant. Elle est appelée lors d'une préincrémentation.
         * @return *this
         */
        iterator& operator++() {
            //Préincrémentation
            if (currentIndex == (chunkLength - 1)) currentChunk++;
            currentIndex = (currentIndex + 1) % chunkLength;
            return *this;
        }

        /**
         * Cette méthode déplace l'itérateur d'un crans vers l'avant. Elle est appelée lors d'une postincrémentation.
         * @return tmpIt, l'iterator courant avant incrémentation
         */
        iterator operator++(int) {
            //Postincrémentation => on retourne le pointeur actuel et ensuite on l'incrémente
            iterator tmpIt = *this;
            if (currentIndex == (chunkLength - 1)) currentChunk++;
            currentIndex = (currentIndex + 1) % chunkLength;
            return tmpIt;
        }

        /**
         * Cette méthode retourne si deux itérateurs sont égaux, c'est à dire s'ils pointent sur le même élément
         * @param other - iterator à comparer
         * @return true si c'est vrai, false si c'est faux
         */
        bool operator==(iterator other) const {
            if(currentChunk!=other.currentChunk || currentIndex!=other.currentIndex)
                return false;
            return true;
        }

        /**
         * Cette méthode retourn si deux itérateurs ne sont pas égaux, c'est à dire s'ils ne pointent pas sur le même élément
         * @param other - iterator a comparer
         * @return trie si c'est vrai, false si c'est faux
         */
        bool operator!=(iterator other) const { return !operator==(other); }

        /**
         * Cette méthode retourne la valeur pointé par l'itérateur
         * @return return l'élément pointé par l'itérateur
         */
        T& operator*() const {
            if (currentIndex==-1) return dummy;
            return *(*currentChunk + currentIndex);
        }


        //***********************BIDIRECTIONNEL***********************
        /**
         * Cette méthode recule l'itérateur d'un cran vers l'arrière. Elle est appelée lors d'une préincrémentation.
         */
        iterator& operator--(){
            //Préincrémentation
            if (currentIndex == 0) currentChunk--;
            currentIndex = (currentIndex - 1) % chunkLength;
            return *this;
        }

        /**
         * Cette méthode recule l'itérateur d'un cran vers l'arrière. Elle est appelée lors d'une postincrémentation.
         * @return tmpIt - l'itérator avant l'incrémentation
         */
        iterator operator--(int){
            //Postincrémentation
            iterator tmpIt = *this;
            if (currentIndex == 0) currentChunk--;
            currentIndex = (currentIndex - 1) % chunkLength;
            return tmpIt;
        }

        //***********************RANDOM ACCESS***********************
        /**
         * Cette méthode retourne si l'itérateur courant est strictement inférieur à l'itérateur other.
         * @param other - l'iterator à comparer
         * @return true c'est c'est vrai, false si c'est faux
         */
        bool operator<(const iterator& other)  const{
            if(*currentChunk<*other.currentChunk)
                return true;
            else if(*currentChunk>*other.currentChunk)
                return  false;
            else
            if(currentIndex<other.currentIndex)
                return true;
            else
                return false;
        }

        /**
         * Cette méthode retourne si l'itérateur courant est inférieur ou égal à l'itérateur other.
         * @param other - l'iterator à comparer
         * @return true c'est c'est vrai, false si c'est faux
         */
        bool operator<=(const iterator& other) const{
            return operator<(other) || operator==(other);
        }

        /**
         * Cette méthode retourne si l'itérateur courant est strictement supérieur à l'itérateur other.
         * @param other - l'iterator à comparer
         * @return true c'est c'est vrai, false si c'est faux
         */
        bool operator>(const iterator& other)  const{
            return !operator<=(other);
        }

        /**
         * Cette méthode retourne si l'itérateur courant est supérieur ou égal à l'itérateur other.
         * @param other - l'iterator à comparer
         * @return true c'est c'est vrai, false si c'est faux
         */
        bool operator>=(const iterator& other) const{
            return !operator<(other);
        }

        /**
         * Cette méthode avance l'itérateur de n crans.
         * @param n - le nombre de sauts à effecter
         * @return *this
         */
        iterator& operator+=(const int n){
            for(int i=0;i<n;i++)
                this->operator++();
            return *this;
        }

        /**
         * Cette méthode recule l'itérateur de n crans.
         * @param n - le nombre de sauts à effectuer
         * @return *this
         */
        iterator& operator-=(const int n){
            for(int i=0;i<n;i++)
                this->operator--();
            return *this;
        }

        /**
         * Cette méthode retourne le nieme élément du conteneur
         * @param n - la position de l'élément
         * @return l'élément à la position n
         */
        int& operator[](int n) {
            *this+=n-1;
            return *this;
        }
    };

    /**
     * Cette fonction retourne un itérateur pointant sur le premier élément du conteneur
     * @return tmpIt - l'itérateur pointant sur le premier élément de l'objet courant
     */
    iterator begin() {
        iterator tmpIt;
        tmpIt.currentChunk = tab + firstPtr;
        tmpIt.currentIndex = firstVal;
        return tmpIt;
    }

    /**
     * Cette fonction retourne un itérateur pointant sur l'élément après le dernier élément du conteneur
     * @return tmpIt - l'itérateur pointant sur un élément après le dernier élément de l'objet courant
     */
    iterator end() {
        if(firstVal==-1) return this->begin(); //Si le deque est vide, selon la document, begin()=end()

        iterator tmpIt=begin();

        tmpIt+=this->size();

        return tmpIt;
    }

    //**********************************IERATEUR CONSTANTS**********************************
    /**
     * La classe const_iterator permet de parcourir un conteneur constant
     */
    class const_iterator {
    public:
        //Attributs
        /**
         * Pointeur sur le chunk courant
         */
        T** currentChunk;

        /**
         * l'indice de l'élément courant dans le chunk courant
         */
        int currentIndex;

        /**
        * Constructeur par défaut
         */
        explicit const_iterator() : currentChunk(nullptr), currentIndex(0) {}

        /**
         * Constructeur par copie
         * @param other - itérator à copier
         */
        const_iterator(const const_iterator& other) : currentChunk(other.currentChunk), currentIndex(other.currentIndex){}

        /**
         * Constructeur par copie d'un iterateur de type iterator
         * @param other - iterateurr à copier
         */
        const_iterator(const iterator& other) : currentChunk(other.currentChunk), currentIndex(other.currentIndex){}

        /**
         * Cette méthode déplace l'itérateur d'un cran vers l'avant. Elle est appelée lors d'une préincrémentation.
         * @return *this
         */
        const_iterator& operator++() {
            //Préincrémentation
            if (currentIndex == (chunkLength - 1)) currentChunk++;
            currentIndex = (currentIndex + 1) % chunkLength;
            return *this;
        }

        /**
         * Cette méthode déplace l'itérateur d'un crans vers l'avant. Elle est appelée lors d'une postincrémentation.
         * @return tmpIt, l'iterator courant avant incrémentation
         */
        const_iterator operator++(int)  {
            //Postincrémentation => on retourne le pointeur actuel et ensuite on l'incrémente
            const_iterator tmpIt = *this;
            if (currentIndex == (chunkLength - 1)) currentChunk++;
            currentIndex = (currentIndex + 1) % chunkLength;
            return tmpIt;
        }

        /**
         * Cette méthode retourne si deux itérateurs sont égaux, c'est à dire s'ils pointent sur le même élément
         * @param other - iterator à comparer
         * @return true si c'est vrai, false si c'est faux
         */
        bool operator==(const_iterator other) const {
            if(currentChunk!=other.currentChunk || currentIndex!=other.currentIndex)
                return false;
            return true;
        }

        /**
         * Cette méthode retourn si deux itérateurs ne sont pas égaux, c'est à dire s'ils ne pointent pas sur le même élément
         * @param other - iterator a comparer
         * @return trie si c'est vrai, false si c'est faux
         */
        bool operator!=(const_iterator other) const { return !operator==(other); }

        /**
         * Cette méthode retourne la valeur pointé par l'itérateur
         * @return return l'élément pointé par l'itérateur
         */
        const T& operator*() const {
            if (currentIndex==-1) return dummy;
            return *(*currentChunk + currentIndex);
        };

        //***********************BIDIRECTIONNEL***********************
        /**
        * Cette méthode recule l'itérateur d'un cran vers l'arrière. Elle est appelée lors d'une préincrémentation.
        */
        const_iterator& operator--(){
            //Préincrémentation
            if (currentIndex == 0) currentChunk--;
            currentIndex = (currentIndex - 1) % chunkLength;
            return *this;
        }

        /**
         * Cette méthode recule l'itérateur d'un cran vers l'arrière. Elle est appelée lors d'une postincrémentation.
         * @return tmpIt - l'itérator avant l'incrémentation
         */
        const_iterator operator--(int){
            //Postincrémentation
            const_iterator tmpIt = *this;
            if (currentIndex == 0) currentChunk--;
            currentIndex = (currentIndex - 1) % chunkLength;
            return tmpIt;
        }

        //***********************RANDOM ACCESS***********************
        /**
         * Cette méthode retourne si l'itérateur courant est strictement inférieur à l'itérateur other.
         * @param other - l'iterator à comparer
         * @return true c'est c'est vrai, false si c'est faux
         */
        bool operator<(const const_iterator& other)  const{
            if(*currentChunk<*other.currentChunk)
                return true;
            else if(*currentChunk>*other.currentChunk)
                return  false;
            else
            if(currentIndex<other.currentIndex)
                return true;
            else
                return false;
        }

        /**
         * Cette méthode retourne si l'itérateur courant est inférieur ou égal à l'itérateur other.
         * @param other - l'iterator à comparer
         * @return true c'est c'est vrai, false si c'est faux
         */
        bool operator<=(const const_iterator& other) const{
            return operator<(other) || operator==(other);
        }

        /**
         * Cette méthode retourne si l'itérateur courant est strictement supérieur à l'itérateur other.
         * @param other - l'iterator à comparer
         * @return true c'est c'est vrai, false si c'est faux
         */
        bool operator>(const const_iterator& other)  const{
            return operator<(other) || operator==(other);
        }

        /**
         * Cette méthode retourne si l'itérateur courant est supérieur ou égal à l'itérateur other.
         * @param other - l'iterator à comparer
         * @return true c'est c'est vrai, false si c'est faux
         */
        bool operator>=(const const_iterator& other) const{
            return !operator<(other);
        }

        /**
         * Cette méthode avance l'itérateur de n crans.
         * @param n - le nombre de sauts à effecter
         * @return *this
         */
        const_iterator& operator+=(const int n){
            for(int i=0;i<n;i++)
                this->operator++();
            return *this;
        }

        /**
         * Cette méthode recule l'itérateur de n crans.
         * @param n - le nombre de sauts à effectuer
         * @return *this
         */
        const_iterator& operator-=(const int n){
            for(int i=0;i<n;i++)
                this->operator--();
            return *this;
        }

        /**
         * Cette méthode retourne le nieme élément du conteneur
         * @param n - la position de l'élément
         * @return l'élément à la position n
         */
        int& operator[](int n) {
            *this+=n;
            return *(*this);
        }

        /**
         * Cette méthode retourne le nieme élément du conteneur. Dans operateur constant.
         * @param n - la position de l'élément
         * @return l'élément à la position n
         */
        const int& operator[](int n) const{
            const int res=operator[](n);
            return res;
        }
    };

    /**
     * Cette fonction retourne un itérateur de type const_iterator pointant sur le premier élément du conteneur
     * @return tmpIt - l'itérateur pointant sur le premier élément de l'objet courant
     */
    const_iterator cbegin() const{
        const_iterator tmpIt;
        tmpIt.currentChunk = tab + firstPtr;
        tmpIt.currentIndex = firstVal;
        return tmpIt;
    }

    /**
     * Cette fonction retourne un itérateur de type const_iterator pointant sur l'élément après le dernier élément du conteneur
     * @return tmpIt - l'itérateur pointant sur un élément après le dernier élément de l'objet courant
     */
    const_iterator cend() const{
        if(firstVal==-1) return this->cbegin(); //Si le deque est vide, selon la document, cbegin()=cend()

        iterator tmpIt;
        tmpIt.currentChunk = tab + lastPtr;
        tmpIt.currentIndex = lastVal;
        tmpIt++;

        return tmpIt; }

    /**
     * Cette fonction retourne un itérateur de type const_iterator pointant sur le premier élément du conteneur
     * @return tmpIt - l'itérateur pointant sur le premier élément de l'objet courant
     */
    const_iterator begin() const { return this->cbegin();}

    /**
     * Cette fonction retourne un itérateur de type const_iterator pointant sur l'élément après le dernier élément du conteneur
     * @return tmpIt - l'itérateur pointant sur un élément après le dernier élément de l'objet courant
     */
    const_iterator end() const { return cend();}

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

template<class T> void swap( deque<T> &lhs, deque<T> &rhs ) {
    lhs.swap(rhs);
    /*deque<T>tmp=(lhs);
    lhs=rhs;
    rhs=tmp;*/
}

template <class T> T deque<T>::dummy = 0;
#endif //C_DEQUE_H