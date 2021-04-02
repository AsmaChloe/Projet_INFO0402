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

    /**
     * Constructeur par défaut. Construit un conteneur vide.
     */
    deque() :tabLength(0), nbElements(0),firstPtr(-1),lastPtr(-1),firstVal(-1),lastVal(-1) {
        tab=new T*[tabLength];
    }

    /**
     * Constructeur qui crée le conteneur avec count instances
     * @param count
     */
    explicit deque(size_type count) : nbElements(count) {
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

    /**
     * Constructeur qui crée le conteneur avec count instances mise à la valeur value
     * @param count
     * @param value
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

    template< class InputIt > deque( InputIt first, InputIt last) {
        int count=0;
        nbElements=0;
        InputIt it=first;

        //On compte le nombre d'éléments se trouvant entre first et last
        while (it!=last){
            it++;
            nbElements++;
        }

        //Tab length
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
        lastVal=firstVal;

        //Ajout des valeurs dans le tableaux;
        while(count<nbElements && lastPtr<tabLength){
            tab[lastPtr][lastVal]=*first;
            first++;
            count++;
            if(lastVal==chunkLength-1){
                lastVal=0;
                lastPtr++;
            }
            else{
                lastVal++;
            }
        }

    }

    /**
     * Conctructeur par copie
     * @param other
     */
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

    /**
     * Constructeur par déplacement
     * @param other
     */
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

    /**
     * Constructeur qui crée un conteneur à partir d'une liste d'initialisation
     */
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

    /**
     * Destructeur
     */
    ~deque() {
        if(tab!=nullptr) {
            for (int i = 0; i < tabLength; i++) {
                if (tab[i] != nullptr) delete[] tab[i];
            }
        }
        delete[] tab;
    }

    /**
     * Cette méthode copie le contenu de other dans l'objet courant
     * @param other
     * @return
     */
    deque& operator=( const deque& other ) {
        int i, j;

        //On réalloue l'objet
        this->resize(other.nbElements);

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

    /**
     * Cette méthode copie le contenu de other dans l'objet courant
     * @param other
     * @return
     */
    deque& operator=( deque&& other ) {
        int i, j;

        //On réalloue l'objet
        this->resize(other.nbElements);

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

    /**
     * Cette méthode copie le contenu de la liste d'initialisation dans l'objet courant
     * @param ilist
     * @return
     */
    deque& operator=( std::initializer_list<T> ilist ) {
        int i, j, count=0;
        //On redimensionne le deque selon la liste
        this->resize(ilist.size());

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

    /**
     * Cette méthode remplit l'objet courant avec count copies de valeur value
     * @param count
     * @param value
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
     * Cette méthode remplit l'objet courant avec les valeurs de l'itérateur first jusqu'à l'itérateur last(exclu)
     * @tparam InputIt
     * @param first
     * @param last
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
     * Cette méthode remplit l'objet courant avec les valeurs de la liste d'initialisation
     * @param ilist
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
     * Cette méthode retourne le pos-ème élément du conteneur. La validité de l'indice pos est vérifié.
     * @param pos
     * @return
     */
    T& at( size_type pos ) {
        if(pos>=0 && pos<nbElements){
            return operator[](pos);
        }
        else
            return dummy; /************Ajouter exception : out_of_range**************/
    }

    /**
     * Cette méthode retourne le pos-ème élément du conteneur. La validité de l'indice pos est vérifié.
     * @param pos
     * @return
     */
    const T& at( size_type pos ) const {
        if(pos>=0 && pos <nbElements)
            return operator[](pos);
        else
            return dummy; /************Ajouter exception : out_of_range**************/
    }

    /**
     * Cette méthode retourne le pos-ème élément du conteneur. La validité de l'indice pos n'est pas vérifié.
     * @param pos
     * @return
     */
    T& operator[]( size_type pos ) {
        if(nbElements<1 || pos>=nbElements || pos<0) return dummy;
        int x= (firstPtr + (pos+firstVal)/chunkLength) % tabLength;
        int y= (pos+firstVal) % chunkLength;

        return tab[x][y];
    }

    /**
     * Cette méthode retourne le pos-ème élément du conteneur. La validité de l'indice pos n'est pas vérifié.
     * @param pos
     * @return
     */
    const T& operator[]( size_type pos ) const {
        if(nbElements<1 || pos>=nbElements || pos<0) return dummy;
        int x= (firstPtr + (pos+firstVal)/chunkLength) % tabLength;
        int y= (pos+firstVal) % chunkLength;

        return tab[x][y];
    }

    /******* A RESOUDRE : Presence de warning lié au retour manquant dans le cas où les if ne sont pas à true**********/
    /**
     * Cette méthode retourne le premier élément du conteneur
     * @return
     */
    T& front() {
        if(firstVal!=-1 && firstPtr!=-1)
            return tab[firstPtr][firstVal];
    }

    /**
     * Cette méthode retourne le premier élément du conteneur
     * @return
     */
    const T& front() const {
        if(firstVal!=-1 && firstPtr!=-1)
            return tab[firstPtr][firstVal];
    }

    /**
     * Cette méthode retourne le dernier élément du conteneur
     * @return
     */
    T& back() {
        if(lastVal!=-1 && lastPtr!=-1)
            return tab[lastPtr][lastVal];
    }

    /**
     * Cette méthode retourne le dernier élément du conteneur
     * @return
     */
    const T& back() const {
        if(lastVal!=-1 && lastPtr!=-1)
            return tab[lastPtr][lastVal];
    }

    /**
     * La méthode empty vérifie si un conteneur est vide ou non
     * @return true ou false
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
     * Cette méthode supprime le contenu du deque
     */
    void clear() {
        //On vide
        if(firstPtr!=-1 && lastPtr==-1){
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
     * @param value
     */
    void push_back( const T& value ) {
        resize(nbElements+1,value);
    }

     /**
     * Cette méthode permet d'ajouter un élément à la fin du conteneur
     * @param value
     */
    void push_back(T&& value) {
        const T valeur=value;
        push_back(valeur);
    }

    template< class... Args > void emplace_back( Args&&... args ) {}                /***************A FAIRE**************/

    /**
     * Cette méthode retire un élément à la fin du deque
     */
    void pop_back() {
        //On ne vérifie pas si le deque est vide => selon la documentation on a un undefined behaviour si le conteneur est vide.
        resize(nbElements-1);
    }

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
     * Cette méthode ajoute un élément au début du conteneur
     * @param value
     */
    void push_front( T&& value ) {
        const T valeur=value;
        push_front(valeur);
    }

    template< class... Args > void emplace_front( Args&&... args ) {}                        /***************A FAIRE**************/

    /**
     * Cette méthode retire le premier élément du conteneur
     */
    void pop_front() {
        tab[firstPtr][firstVal]=dummy;

        //Si la premier valeur se trouve au bout d'un chunk
        if(firstVal==chunkLength-1) {
            firstVal = 0;
            firstPtr++;
            tabLength--;
        }
        else
            firstVal++;

        nbElements--;
    }

    /**
     * Cette méthode redimensionne le conteneur
     * @param count
     */
    void resize( size_type count ) {
        resize(count,dummy);
    }

    /**
     * Cette méthode redimensionne le conteneur
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
            tabLength=count/chunkLength;
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

                //Si il y en a, on ajoute les éléments du chunk coupé : le chunk firstPtr+count/chunkLength
                if(count%chunkLength!=0){
                    nvTab[tabLength-1]=new T[chunkLength]; //Creation d'un chunk vierge

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

    /**
     * Cette méthode inverse le contenu de l'objet courant avec l'objet passé en paramètre
     * @param other
     */
    void swap( deque& other ){
        deque<T>tmp=(*this);
        *this=other;
        other=tmp;
    }

    /**
     * Cet méthode retourne si deux conteneurs sont égaux
     * @param lhs
     * @param rhs
     * @return
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
     * @param lhs
     * @param rhs
     * @return
     */
    friend bool operator!=( const deque& lhs, const deque& rhs ) {
        return !operator==(lhs,rhs);
    }

    /**
     * Cette méthode retourne si le conteneur à gauche de l'égalité est strictement inférieur au conteneur à droite.
     * @param lhs
     * @param rhs
     * @return
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
     * @param lhs
     * @param rhs
     * @return
     */
    friend bool operator<=( const deque& lhs, const deque& rhs ) {
        return operator==(lhs,rhs) || operator<(lhs,rhs);
    }

    /**
     * Cette méthode retourne si le conteneur à gauche de l'égalité est strictement supérieur au conteneur à droite.
     * @param lhs
     * @param rhs
     * @return
     */
    friend bool operator>(  const deque& lhs, const deque& rhs ) {
        return !operator<=(lhs,rhs);
    }

    /**
     * Cette méthode retourne si le conteneur à gauche de l'égalité est supérieur ou égal au conteneur à droite.
     * @param lhs
     * @param rhs
     * @return
     */
    friend bool operator>=( const deque& lhs, const deque& rhs ) {
        return !operator<(lhs,rhs);
    }

    //**********************************IERATEUR CLASSIQUES**********************************
    class iterator {
    public:
        //Attributs
        T** currentChunk; // pointeur sur le chunk courant
        int currentIndex; // l'indice de l'élément courant dans le chunk courant

        /**
         * Constructeur par défaut
         */
        explicit iterator() : currentChunk(nullptr), currentIndex(0) {}

        /**
         * Constructeur par copie
         * @param other
         */
        iterator(const iterator& other) : currentChunk(other.currentChunk), currentIndex(other.currentIndex){}

        /**
         * Contructeur à partir d'un tableau 2D et d'un index
         * @param conteneur
         */
        iterator(T** tab, int index){
            currentChunk = tab;
            currentIndex = index;
        }

        /**
         * Cette méthode déplace l'itérateur d'un cran vers l'avant. Elle est appelée lors d'une préincrémentation.
         * @return
         */
        iterator& operator++() {
            //Préincrémentation
            if (currentIndex == (chunkLength - 1)) currentChunk++;
            currentIndex = (currentIndex + 1) % chunkLength;
            return *this;
        }

        /**
         * Cette méthode déplace l'itérateur d'un crans vers l'avant. Elle est appelée lors d'une postincrémentation.
         * @param n
         * @return
         */
        iterator operator++(int) { //======> A vérifier sur documention si operator++ fait attention sur les nouveaux indices sont valides ou non
            //Postincrémentation => on retourne le pointeur actuel et ensuite on l'incrémente
            iterator tmpIt = *this;
            if (currentIndex == (chunkLength - 1)) currentChunk++;
            currentIndex = (currentIndex + 1) % chunkLength;
            return tmpIt;
        }

        /**
         * Cette méthode retourne si deux itérateurs sont égaux, c'est à dire s'ils pointent sur le même élément
         * @param other
         * @return
         */
        bool operator==(iterator other) const {
            if(currentChunk!=other.currentChunk || currentIndex!=other.currentIndex)
                return false;
            return true;
        }

        /**
         * Cette méthode retourn si deux itérateurs ne sont pas égaux, c'est à dire s'ils ne pointent pas sur le même élément
         * @param other
         * @return
         */
        bool operator!=(iterator other) const { return !operator==(other); }

        /**
         * Cette méthode retourne la valeur pointé par l'itérateur
         * @return
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
         * @return
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
         * @param other
         * @return
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
         * @param other
         * @return
         */
        bool operator<=(const iterator& other) const{
            return operator<(other) || operator==(other);
        }

        /**
         * Cette méthode retourne si l'itérateur courant est strictement supérieur à l'itérateur other.
         * @param other
         * @return
         */
        bool operator>(const iterator& other)  const{
            return !operator<=(other);
        }

        /**
         * Cette méthode retourne si l'itérateur courant est supérieur ou égal à l'itérateur other.
         * @param other
         * @return
         */
        bool operator>=(const iterator& other) const{
            return !operator<(other);
        }

        /**
         * Cette méthode avance l'itérateur de n crans.
         * @param n
         * @return
         */
        iterator& operator+=(const int n){
            for(int i=0;i<n;i++)
                this->operator++();
            return *this;
        }

        /**
         * Cette méthode recule l'itérateur de n crans.
         * @param n
         * @return
         */
        iterator& operator-=(const int n){
            for(int i=0;i<n;i++)
                this->operator--();
            return *this;
        }

        /**
         * Cette méthode retourne le nieme élément du conteneur
         * @param n
         * @return
         */
        int& operator[](int n) {
            *this+=n-1;
            return *this;
        }
    };

    /**
     * Cette fonction retourne un itérateur pointant sur le premier élément du conteneur
     * @return
     */
    iterator begin() {
        iterator tmpIt;
        tmpIt.currentChunk = tab + firstPtr;
        tmpIt.currentIndex = firstVal;
        return tmpIt;
    }

    /**
     * Cette fonction retourne un itérateur pointant sur l'élément après le dernier élément du conteneur
     * @return
     */
    iterator end() {
        if(firstVal==-1) return this->begin(); //Si le deque est vide, selon la document, begin()=end()

        iterator tmpIt;
        tmpIt.currentChunk = tab + lastPtr;
        tmpIt.currentIndex = lastVal;
        tmpIt++;

        return tmpIt;
    }

    //**********************************IERATEUR CONSTANTS**********************************
    class const_iterator {
    public:
        //Attributs
        T** currentChunk; // pointeur sur le chunk courant
        int currentIndex; // l'indice de l'élément courant dans le chunk courant

        /**
        * Constructeur par défaut
         */
        explicit const_iterator() : currentChunk(nullptr), currentIndex(0) {}

        /**
         * Constructeur par copie d'un const_iterator
         * @param other
         */
        const_iterator(const const_iterator& other) : currentChunk(other.currentChunk), currentIndex(other.currentIndex){}

        /**
         * Constructeur par copie d'un iterator
         * @param other
         */
        const_iterator(const iterator& other) : currentChunk(other.currentChunk), currentIndex(other.currentIndex){}

       /**
        * Cette méthode déplace l'itérateur d'un cran vers l'avant. Elle est appelée lors d'une préincrémentation.
        * @return
        */
        const_iterator& operator++() {
            //Préincrémentation
            if (currentIndex == (chunkLength - 1)) currentChunk++;
            currentIndex = (currentIndex + 1) % chunkLength;
            return *this;
        }

        /**
         * Cette méthode déplace l'itérateur d'un crans vers l'avant. Elle est appelée lors d'une postincrémentation.
         * @return
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
         * @param other
         * @return
         */
        bool operator==(const_iterator other) const {
            if(currentChunk!=other.currentChunk || currentIndex!=other.currentIndex)
                return false;
            return true;
        }

        /**
         * Cette méthode retourn si deux itérateurs ne sont pas égaux, c'est à dire s'ils ne pointent pas sur le même élément
         * @param other
         * @return
         */
        bool operator!=(const_iterator other) const { return !operator==(other); }

        /**
         * Cette méthode retourne la valeur pointé par l'itérateur
         * @return
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
        * @return
        */
        const_iterator operator--(int){
            //Postincrémentation
            const_iterator tmpIt = *this;
            if (currentIndex == 0) currentChunk--;
            currentIndex = (currentIndex - 1) % chunkLength;
            return tmpIt;
        }

        //***********************RANDOM ACCESS***********************

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
         * @param other
         * @return
         */
        bool operator<=(const const_iterator& other) const{
            return operator<(other) || operator==(other);
        }

        /**
         * Cette méthode retourne si l'itérateur courant est inférieur ou égal à l'itérateur other.
         * @param other
         * @return
         */
        bool operator>(const const_iterator& other)  const{
            return operator<(other) || operator==(other);
        }

        /**
         * Cette méthode retourne si l'itérateur courant est supérieur ou égal à l'itérateur other.
         * @param other
         * @return
         */
        bool operator>=(const const_iterator& other) const{
            return !operator<(other);
        }

        /**
         * Cette méthode avance l'itérateur de n crans.
         * @param n
         * @return
         */
        const_iterator& operator+=(const int n){
            for(int i=0;i<n;i++)
                this->operator++();
            return *this;
        }

        /**
         * Cette méthode recule l'itérateur de n crans.
         * @param n
         * @return
         */
        const_iterator& operator-=(const int n){
            for(int i=0;i<n;i++)
                this->operator--();
            return *this;
        }

        /**
         * Cette méthode retourne le nieme élément du conteneur
         * @param n
         * @return
         */
        int& operator[](int n) {
            *this+=n;
            return *(*this);
        }

        /**
         * Cette méthode retourne le nieme élément du conteneur. Element de type const.
         * @param n
         * @return
         */
        const int& operator[](int n) const{
            const int res=operator[](n);
            return res;
        }
    };
    const_iterator cbegin() { return const_iterator(); }
    const_iterator cend() { return const_iterator(); }

    /**
     * Cette fonction retourne un itérateur pointant sur le premier élément du conteneur
     */
    const_iterator begin() const {
        const_iterator tmpIt;
        tmpIt.currentChunk = tab + firstPtr;
        tmpIt.currentIndex = firstVal;
        return tmpIt;
    }
    /**
     * Cette fonction retourne un itérateur pointant sur l'élément après le dernier élément du conteneur
     * @return
     */
    const_iterator end() const {
        if(firstVal==-1) return this->begin(); //Si le deque est vide, selon la document, begin()=end()

        iterator tmpIt;
        tmpIt.currentChunk = tab + lastPtr;
        tmpIt.currentIndex = lastVal;
        tmpIt++;

        return tmpIt;
    }

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
    deque<T>tmp=(lhs);
    lhs=rhs;
    rhs=tmp;
}

template <class T> T deque<T>::dummy = 0;
#endif //C_DEQUE_H