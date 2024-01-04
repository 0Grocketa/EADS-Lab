    #ifndef EADS_LAB_SEQUENCE_HPP
    #define EADS_LAB_SEQUENCE_HPP

    template <typename Key, typename Info>
    class Sequence{
    private:
        class Node{
        private:
            friend class Sequence;
            Key key;
            Info info;
            Node* next = nullptr;
            Node() {}
            Node(const Key &key, const Info &info): key(key), info(info){};
            Node* getNext() { return next; }
            const Node* getNext() const { return next; }
            Key& getKey() { return key; }
            const Key& getKey() const { return key; }
            Info& getInfo() { return info; }
            const Info& getInfo() const { return info; }
        };
        Node sentinel;
        int length;
        Node* get_node(const Key& key, unsigned int occurrences=1) {
            Node* current = sentinel.next;
            int count = 0;

            while (current != nullptr) {
                if (current->getKey() == key) {
                    count++;
                    if (count == occurrences) {
                        return current;
                    }
                }
                current = current->next;
            }

            return nullptr;
        }



    public:
        Sequence():length(0){}
        Sequence(const Sequence<Key, Info> &other) : length(0), sentinel() {
            const Node* current = other.sentinel.getNext();
            while (current) {
                push_back(current->getKey(), current->getInfo());
                current = current->next;
            }
        }

        ~Sequence(){
            Node *current = sentinel.next;
            while(current){
                Node* remove = current;
                current = current->next;
                delete remove;
            }
        }
        bool add_node_after(const Key &key, const Info &info, const Key &targetKey, int targetOccurrence) {
            Node* target = get_node(targetKey, targetOccurrence);
            if (target != nullptr) {
                Node* toAdd = new Node(key, info);
                toAdd->next = target->next;
                target->next = toAdd;
                length++;
                return true;
            }
            return false;
        }


        Sequence<Key, Info>& operator=(const Sequence<Key, Info> &other) {
            if (this == &other) {
                return *this;
            }

            clear();

            Node* current = other.sentinel.next;
            while (current != nullptr) {
                push_back(current->getKey(), current->getInfo());
                current = current->next;
            }

            return *this;
        }


        int size()const{
            return this->length;
        }



        void clear() {
            while (pop_front()) {
            }
        }

        bool is_empty()const{
            return size()==0;
        }

        int occurrences(const Key &key)const{
            Node*current = sentinel.next;
            int occurrence = 0;
            while(current){
                if(current->key == key){
                    occurrence++;
                }
                current = current->next;
            }
            return occurrence;
        }

        bool pop_front() {
            if (sentinel.next == nullptr) {
                return false;
            }
            Node* toDelete = sentinel.next;
            sentinel.next = toDelete->next;
            delete toDelete;
            length--;
            return true;
        }

        bool pop_back() {
            if (sentinel.next == nullptr) {
                return false;
            }

            if (sentinel.next->next == nullptr) {
                delete sentinel.next;
                sentinel.next = nullptr;
                length--;
                return true;
            }

            Node* current = sentinel.next;
            while (current->next->next != nullptr) {
                current = current->next;
            }

            delete current->next;
            current->next = nullptr;
            length--;

            return true;
        }

        void push_front(const Key& key, const Info& info) {
            Node* newNode = new Node(key, info);
            newNode->next = sentinel.next;
            sentinel.next = newNode;
            length++;
        }

        void push_back(const Key& key, const Info& info){
            Node* newNode = new Node(key, info);
            Node* current = &sentinel;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
            length++;
        }

        bool remove(const Key &key, int occurrence) {
            Node* current = &sentinel;
            int count = 0;

            while (current->next != nullptr) {
                if (current->next->getKey() == key) {
                    if (count == occurrence) {
                        Node* toDelete = current->next;
                        current->next = toDelete->next;
                        delete toDelete;
                        length--;
                        return true;
                    }
                    count++;
                }
                current = current->next;
            }

            return false;
        }
        
        bool remove_at(int position) {
            if (position < 0 || position >= this->length) {
                return false;
            }

            Node* current = &sentinel;
            int curPos = 0;

            
            while (curPos < position) {
                current = current->next;
                curPos++;
            }

            // Now current points to the node just before the one to be removed
            Node* toDelete = current->next;
            if (toDelete != nullptr) {
                current->next = toDelete->next;
                delete toDelete;
                this->length--;
                return true;
            }

            return false;
        }


        void insert_after(const Key& key, const Info& info, const Key & targetKey, int targetOccurrence) {
            Node* target = get_node(targetKey, targetOccurrence);
            if (target != nullptr) {
                Node* newNode = new Node(key, info);
                newNode->next = target->next;
                target->next = newNode;
                length++;
            }
        }

        bool remove_all(const Key& key) {
            Node* current = &sentinel;
            bool removed = false;

            while (current->next != nullptr) {
                if (current->next->getKey() == key) {
                    Node* toDelete = current->next;
                    current->next = toDelete->next;
                    delete toDelete;
                    length--;
                    removed = true;
                } else {
                    current = current->next;
                }
            }

            return removed;
        }


        bool operator ==(const Sequence<Key, Info> &other)const {
            Node* current = sentinel.next;
            Node* otherCurrent = other.sentinel.next;

            while (current != nullptr && otherCurrent != nullptr) {
                if (current->getKey() != otherCurrent->getKey() || current->getInfo() != otherCurrent->getInfo()) {
                    return false;
                }
                current = current->next;
                otherCurrent = otherCurrent->next;
            }

            return current == nullptr && otherCurrent == nullptr;
        }


        bool operator!=(const Sequence<Key, Info> &other)const {
            return !(*this == other);
        }

        //Check if Key of given occurrence exists in sequence
        bool find_node(const Key &key, int targetOccurrence)const {
            Node* current = sentinel.next;
            int occurrence = 0;
            while (current) {
                if (current->getKey() == key) {
                    occurrence++;
                    if (occurrence == targetOccurrence) {
                        return true;
                    }

                }
                current = current->next;
            }
            return false;
        }



        bool getInfo(Info &info, const Key &key,unsigned int occurrence=1) const {
            const Node* current = sentinel.next;
            int count = 0;
            while (current != nullptr) {
                if (current->getKey() == key) {
                    count++;
                    if (count == occurrence) {
                        info = current->getInfo();
                        return true;
                    }
                }
                current = current->next;
            }
            return false;
        }

        bool getInfo(Info& info, Key& key, int position) const {
            if (position < 1 || position > this->size()) {
                return false;
            }

            const Node* current = sentinel.next;
            unsigned int currentPos = 1;

            while (current != nullptr) {
                if (currentPos == position) {
                    key = current->getKey();
                    info = current->getInfo();
                    return true;
                }
                current = current->next;
                currentPos++;
            }

            return false;
        }



    };





    #endif //EADS_LAB_SEQUENCE_HPP