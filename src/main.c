/*
* A simple fixed-size hash table in C.
*
* This is a learning exercise
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dict_item {
	char* key;
	char* value;
	struct dict_item* next;
} dict_item_t;

typedef struct bucket {
	dict_item_t* item;
	dict_item_t* last_item;
	unsigned long size;
} bucket_t;

typedef struct dict {
	bucket_t* buckets;
	unsigned long size;	
} dict_t;

unsigned long hash_gen(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

void dict_init(dict_t* dict, unsigned long size) {
	dict->size = size;
	dict->buckets = malloc(size * sizeof(bucket_t));
}

void dict_set(dict_t* dict, char* key, char* value) {
	bucket_t* bucket = &dict->buckets[hash_gen(key) % dict->size];
	dict_item_t* new_item = malloc(sizeof(dict_item_t));
	new_item->key = key;
	new_item->value = value;
	if (bucket->size == 0) {
		bucket->item = new_item;
	} else {
		bucket->last_item->next = new_item;
	}
	bucket->last_item = new_item;
	bucket->size += 1;
}

char* dict_get(dict_t* dict, char* key) {
	bucket_t* bucket = &dict->buckets[hash_gen(key) % dict->size];
	if (bucket->size == 0) {
		return "";
	}

	for (dict_item_t* item = bucket->item; item != NULL; item = item->next) {
		if (strcmp(item->key, key) == 0) {
			return item->value;
		}
	}

	return "";
}

int main() {
	dict_t dict;
	dict_init(&dict, 10);

	dict_set(&dict, "name", "test");
	dict_set(&dict, "password", "myStrongAndSecurePassword");
	dict_set(&dict, "age", "20");

	printf("name: %s\n", dict_get(&dict, "name"));
	printf("password: %s\n", dict_get(&dict, "password"));
	printf("age: %s\n", dict_get(&dict, "age"));

	return 0;
}
