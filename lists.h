#ifndef LISTS_H
#define LISTS_H

#include <iostream>
#include <stdlib.h>

template <class T>
struct LinkedListNode {
    public:
        T value;
        struct LinkedListNode* next;

        LinkedListNode(T value) {
            this->value = value;
        }
        ~LinkedListNode() {
            if (this->next != NULL)
                free(this->next);
        }
};

template <class T>
struct LinkedList {
    private:
        int length = 0;
        struct LinkedListNode<T> *start   = NULL,
                       *end     = NULL;

    public:
        LinkedList() {
        }
        ~LinkedList() {
            this->clear();
        }

        int size() {
            return this->length;
        }
        void add(T v, int index) {
            if (index >= length) {
                this->append(v);
            } else {
                struct LinkedListNode<T> *n_start = (struct LinkedListNode<T>*) malloc(sizeof(struct LinkedListNode<T>)),
                                         *temp = n_start;
                n_start->next = this->start;

                for (int i = 0; i < index; i++)
                    temp = temp->next;

                struct LinkedListNode<T>* t = (struct LinkedListNode<T>*) malloc(sizeof(struct LinkedListNode<T>));
                t->value = v;
                t->next = temp->next;
                temp->next = t;

                this->start = n_start->next;
            }

            this->length++;
        }
        void append(T v) {
            if (length == 0) {
                this->start = (struct LinkedListNode<T>*) malloc(sizeof(struct LinkedListNode<T>));
                this->start->value = v;
                this->start->next = NULL;

                this->end = this->start;
            } else {
                this->end->next = (struct LinkedListNode<T>*) malloc(sizeof(struct LinkedListNode<T>));
                this->end->next->value = v;
                this->end->next->next = NULL;

                this->end = this->end->next;
            }

            this->length++;
        }
        int get(T index) {
            if (index > this->length || this->length == 0)
                return NULL;

            struct LinkedListNode<T>* target = this->start;
            for (int i = 0; i < index; i++) {
                target = target->next;
            }

            return target->value;
        }
        void remove(int index) {
            if (index > length || length == 0)
                return;

            struct LinkedListNode<T>* target = this->start;
            for (int i = 0; i < index-1; i++) {
                target = target->next;
            }

            target->next = target->next->next;
            this->length--;
        }
        void removeValue(T v) {
            struct LinkedListNode<T> *n_start = (struct LinkedListNode<T>*) malloc(sizeof(struct LinkedListNode<T>)),
                                     *cu = n_start;
            n_start->next = this->start;

            while (cu->next != NULL) {
                if (cu->next->value == v) {
                    cu->next = cu->next->next;
                    this->length--;
                } else {
                    cu = cu->next;
                }
            }

            this->start = n_start->next;
        }
        void clear() {
            if (this->length>0)
                deleteAll(this->start);
        }
        void deleteAll(struct LinkedListNode<T>* cu) {
            if (cu->next != NULL) {
                deleteAll(cu->next);
            }
            free(cu);
            this->length--;
        }
        int index(T v) {
            struct LinkedListNode<T>* cu = this->start;
            int i = 0;

            while (cu != NULL && cu->value != v) {
                cu = cu->next;
                i++;
            }

            if (cu->value != v)
                return -1;
            return i;
        }
        bool contains(T v) {
            struct LinkedListNode<T>* cu = this->start;
            while(cu->next != NULL && cu->value != v) {
                cu = cu->next;
            }

            if (cu->value != v)
                return false;
            return true;
        }
        void sort(bool (*comp)(T, T)) {
            struct LinkedListNode<T>* temp_n = (struct LinkedListNode<T>*) malloc(sizeof(struct LinkedListNode<T>));
            temp_n->next = this->start;

            struct LinkedListNode<T> *co = temp_n,
                           *be_cu = this->start;

            for (int i = 1; i < this->length; i++) {
                co = temp_n;
                bool same = false;

                for (int j = 0; j < i; j++) {
                    if (!comp(co->next->value, be_cu->next->value)) {
                        struct LinkedListNode<T>* h = be_cu->next;
                        be_cu->next = be_cu->next->next;

                        struct LinkedListNode<T>* h2 = co->next;
                        co->next = h;
                        h->next = h2;

                        same = true;
                        break;
                    }
                    co = co->next;
                }

                if (!same)
                    be_cu = be_cu->next;
            }

            this->start = temp_n->next;
        }
        void filter(bool (*fi)(T)) {
            struct LinkedListNode<T> *n_start = (struct LinkedListNode<T>*) malloc(sizeof(struct LinkedListNode<T>)),
                           *cu = n_start;
            cu->next = this->start;

            while (cu->next != NULL) {
                if (!fi(cu->next->value)) {
                    cu->next = cu->next->next;
                    this->length--;
                } else {
                    cu = cu->next;
                }
            }

            this->start = n_start->next;
        }
        void map(T (*m)(T)) {
            struct LinkedListNode<T>* cu = this->start;
            while (cu != NULL) {
                cu->value = m(cu->value);
                cu = cu->next;
            }
        }
        T reduce(T (*r)(T, T)) {
            struct LinkedListNode<T>* cu = this->start->next;
            if (this->length == 0)
                return NULL;

            T ret = this->start->value;
            while (cu != NULL) {
                ret = r(ret, cu->value);
                cu = cu->next;
            }

            return ret;
        }
        std::string toString() {
            std::stringstream ret;
            ret << "[";
            struct LinkedListNode<T>* target = this->start;
            for (int i = 0; i < this->length; i++) {
                ret << target->value << (i < this->length-1 ? ", " : "");
                target = target->next;
            }
            ret << "]";
            return ret.str();
        }

};

#endif // LISTS_H
