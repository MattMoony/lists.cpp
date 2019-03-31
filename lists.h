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

        /**
         * @brief   "size" returns the length of the list.
         * @return  (int) length of the list
         */
        int size() {
            return this->length;
        }
        /**
         * @brief   "add" adds a value to the list at
         *          the specified position.
         * @param   (T) the value.
         * @param   (int) the index
         */
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
        /**
         * @brief   "addAll" adds all elements of an array
         *          beginning from the specified index.
         * @param   (T*) reference to the array
         * @param   (int) the array's length
         * @param   (int) the beginning index
         */
        void addAll(T* v, int len, int index) {
            if (index >= length) {
                this->appendAll(v, len);
            } else {
                struct LinkedListNode<T> *n_start = (struct LinkedListNode<T>*) malloc(sizeof(struct LinkedListNode<T>)),
                                         *temp = n_start;
                n_start->next = this->start;

                for (int i = 0; i < index; i++)
                    temp = temp->next;

                struct LinkedListNode<T> *next_nd = temp->next;

                for (int i = 0; i < len; i++) {
                    temp->next = (struct LinkedListNode<T>*) malloc(sizeof(struct LinkedListNode<T>));
                    temp = temp->next;

                    temp->value = v[i];
                    temp->next = NULL;

                    this->length++;
                }

                temp->next = next_nd;
            }
        }
        /**
         * @brief   "append" adds a value to the end of the list.
         * @param   (T) the value
         */
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
        /**
         * @brief   "appendAll" adds all values of an array to
         *          end of the list.
         * @param   (T*) reference to the array
         * @param   (int) the array's length
         */
        void appendAll(T *v, int len) {
            struct LinkedListNode<T>* cu = (struct LinkedListNode<T>*) malloc(sizeof(struct LinkedListNode<T>));
            cu->value = v[0];
            cu->next = NULL;

            this->start = cu;
            this->length++;

            for (int i = 1; i < len; i++) {
                cu->next = (struct LinkedListNode<T>*) malloc(sizeof(struct LinkedListNode<T>));
                cu = cu->next;

                cu->value = v[i];
                cu->next = NULL;

                this->length++;
            }

            this->end = cu;
        }
        /**
         * @brief   "get" returns the list's value at
         *          the given index
         * @param   (int) the index
         * @return  (T) the value
         */
        T get(int index) {
            if (index > this->length || this->length == 0)
                return NULL;

            struct LinkedListNode<T>* target = this->start;
            for (int i = 0; i < index; i++) {
                target = target->next;
            }

            return target->value;
        }
        /**
         * @brief   "remove" removes the value at the
         *          specified index.
         * @param   (int) the index
         */
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
        /**
         * @brief   "removeValue" removes all occurrences
         *          of the specified value from the list.
         * @param   (T) the value
         */
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
        /**
         * @brief   "clear" deletes all values from the list.
         */
        void clear() {
            if (this->length>0)
                deleteAll(this->start);
        }
        /**
         * @brief   "deleteAll": the recursive delete function
         * @param   (struct LinkedListNode<T>*) the current node
         */
        void deleteAll(struct LinkedListNode<T>* cu) {
            if (cu->next != NULL) {
                deleteAll(cu->next);
            }
            free(cu);
            this->length--;
        }
        /**
         * @brief   "index" returns the index of the specified
         *          element.
         * @param   (T) v: the value/element
         * @return  (int) the index. (-1 if not in list)
         */
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
        /**
         * @brief   "contains" returns boolean value of
         *          whether in list or not.
         * @param   (T) v: the value
         * @return  true, if in list, else false.
         */
        bool contains(T v) {
            struct LinkedListNode<T>* cu = this->start;
            while(cu->next != NULL && cu->value != v) {
                cu = cu->next;
            }

            if (cu->value != v)
                return false;
            return true;
        }
        /**
         * @brief   "sort" sorts the list using the given
         *          comparator.
         * @param   (bool)(*comp)(T, T): the function pointer
         *          to a comparator function.
         *          Comparator should return true, if the first
         *          value should stand before the second one.
         */
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
        /**
         * @brief   "filter" filters the list using the
         *          specified function pointer.
         * @param   (bool)(*fi)(T): the decisive function.
         *          Should return true, if the value should
         *          be included in the list.
         */
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
        /**
         * @brief   "map" applies a function to all elements
         *          of the list.
         * @param   (T)(*m)(T): the function-to-be-applied.
         */
        void map(T (*m)(T)) {
            struct LinkedListNode<T>* cu = this->start;
            while (cu != NULL) {
                cu->value = m(cu->value);
                cu = cu->next;
            }
        }
        /**
         * @brief   "reduce" uses a function to compress all
         *          nodes' values into a single value.
         * @param   (T)(*r)(T, T): Does something with the
         *          two given values, and returns the result.
         * @return  (T): the final value
         */
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
        /**
         * @brief   "toString" parses the list into a std::string.
         * @return  (std::string): the list in the following format:
         *          [v1, v2, v3, ..., vx, v(x+1)]
         */
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
