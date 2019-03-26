#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

struct Node {
    int value;
    NodeP next;
};

struct IList {
    int size = 0;
    NodeP start;

    void append(int v) {
        if (this->size == 0) {
            this->start = (NodeP) malloc(sizeof(Node));
            this->start->value = v;
        } else {
            NodeP temp = this->start;
            while (temp->next != NULL)
                temp = temp->next;

            temp->next = (NodeP) malloc(sizeof(Node));
            temp->next->value = v;
        }

        this->size++;
    };
    int get(int index) {
        if (index > size || size == 0)
            return NULL;

        NodeP target = this->start;
        for (int i = 0; i < index; i++) {
            target = target->next;
        }

        return target->value;
    }
};
