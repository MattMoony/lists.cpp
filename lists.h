#ifndef LISTS_H
#define LISTS_H

#include <iostream>
#include <stdlib.h>

template <class T>
struct Node {
    T value;
    struct Node* next;
};

template <class T>
struct List {
    private:
        int length = 0;
        struct Node<T>* start = NULL;

    public:
        List() {
        }
        ~List() {
        }

        int size() {
            return this->length;
        }
        void add(T v, int index) {
            if (index > length) {
                this->append(v);
            } else {
                struct Node<T>* temp = this->start;
                for (int i = 0; i < index; i++)
                    temp = temp->next;

                struct Node<T>* t = (struct Node<T>*) malloc(sizeof(struct Node<T>));
                t->value = v;
                t->next = temp->next;
                temp->next = t;
            }

            this->length++;
        }
        void append(T v) {
            if (length == 0) {
                this->start = (struct Node<T>*) malloc(sizeof(struct Node<T>));
                this->start->value = v;
                this->start->next = NULL;
            } else {
                struct Node<T>* temp = this->start;
                while (temp->next != NULL)
                    temp = temp->next;

                temp->next = (struct Node<T>*) malloc(sizeof(struct Node<T>));
                temp->next->value = v;
                temp->next->next = NULL;
            }

            this->length++;
        }
        int get(T index) {
            if (index > this->length || this->length == 0)
                return NULL;

            struct Node<T>* target = this->start;
            for (int i = 0; i < index; i++) {
                target = target->next;
            }

            return target->value;
        }
        void remove(int index) {
            if (index > length || length == 0)
                return;

            struct Node<T>* target = this->start;
            for (int i = 0; i < index-1; i++) {
                target = target->next;
            }

            target->next = target->next->next;
            this->length--;
        }
        void clear() {
            deleteAll(this->start);
        }
        void deleteAll(struct Node<T>* cu) {
            if (cu->next != NULL) {
                deleteAll(cu->next);
            }
            free(cu);
            this->length--;
        }
        int index(T v) {
            struct Node<T>* cu = this->start;
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
            struct Node<T>* cu = this->start;
            while(cu->next != NULL && cu->value != v) {
                cu = cu->next;
            }

            if (cu->value != v)
                return false;
            return true;
        }
        void sort(bool (*comp)(T, T)) {
            std::cout << "Comp: " << comp(this->start->value, this->start->next->value) << std::endl;
        }

        std::string toString() {
            std::stringstream ret;
            ret << "[";
            struct Node<T>* target = this->start;
            for (int i = 0; i < this->length; i++) {
                ret << target->value << (i < this->length-1 ? ", " : "");
                target = target->next;
            }
            ret << "]";
            return ret.str();
        }

};

#endif // LISTS_H
