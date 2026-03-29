#include <stdio.h>
#define POOL_SIZE 1024
static unsigned char memory[POOL_SIZE];
int offset = 0;

typedef struct {
    int size;
    int free;
} header;

void* allocate(int size) {
    if (size <= 0) {
        printf("Size cannot be negative or zero");
        return NULL;
    }
    for (int i = 0; i < offset;) {
        header* head = (header*)&memory[i];
        
        if (head->free && head->size >= size) {
            int remaining = head->size - size;

            if (remaining > sizeof(header)+8) {
                header* new_head = (header*)((unsigned char*)head + sizeof(header) + size);
                new_head->size = remaining - sizeof(header);
                new_head->free = 1;
                
                head->size = size;
            }
            
            head->free = 0;
            return (unsigned char*)head + sizeof(header);
        }
        
        i += sizeof(header) + head->size;
    }
    
    if (offset + sizeof(header) + size > POOL_SIZE) return NULL;
    
    header* head = (header*)&memory[offset];
    head->size = size;
    head->free = 0; 

    offset += sizeof(header) + size;
    return (unsigned char*)head + sizeof(header);
}

void deallocate(void* ptr) {
    header* head = (header*)((unsigned char*)ptr - sizeof(header));
    head->free = 1;

    // coalesce forward
    unsigned char* end = (unsigned char*)head + sizeof(header) + head->size;
    if (end < memory + offset) {
        header* next = (header*)end;
        if (next->free) {
            head->size += sizeof(header) + next->size;
        }
    }

    // Coalesce backward
    for (int i = 0; i < offset;) {
        header* prev = (header*)&memory[i];
        unsigned char* prev_end = (unsigned char*)prev + sizeof(header) + prev->size;

        if (prev_end == (unsigned char*)head && prev->free) {
            prev->size += sizeof(header) + head->size;
            break;
        }

        i += sizeof(header) + prev->size;
    }
}

int main() {
    int* buffer = (int*)allocate(1016);
    if (!buffer) {
        printf("memory is full!\n");
        return -1;
    }

    deallocate(buffer);
    int* temp = allocate(sizeof(int));
    if (!temp) {
        printf("memory is full!\n");
        return -1;
    }
    return 0;
}