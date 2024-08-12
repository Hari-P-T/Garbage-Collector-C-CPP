#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

template <typename T>
struct Trash {
    T* pointer;
    Trash* next;
    Trash(T* input) : pointer(input), next(nullptr) {}
};

void clean();

template <typename T>
class Trash_Stack {
private:
    Trash<T>* head;
    size_t size;

public:
    Trash_Stack() : head(nullptr), size(0) {}

    void push(T* gb) {
        Trash<T>* temp = new Trash<T>(gb);
        temp->next = head;
        head = temp;
        size++;
    }

    bool empty() const {
        return size == 0;
    }

    void pop() {
        if (empty()) {
            cerr << "Stack underflow" << endl << flush;
        } else {
            Trash<T>* temp = head;
            head = head->next;
            free(temp->pointer);
            delete temp;
            size--;
        }
    }

    friend void clean();
};

static Trash_Stack<void> Collector;

void* operator new(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        throw bad_alloc();
    }
    Collector.push(ptr);
    return ptr;
}

void operator delete(void* ptr) noexcept {
    free(ptr);
    ptr = nullptr;
}

void* operator new[](size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        throw bad_alloc();
    }
    Collector.push(ptr);
    return ptr;
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
    ptr = nullptr;
}

void* malloc(size_t size) {
    void* ptr = std::malloc(size);
    if (!ptr) {
        throw bad_alloc();
    }
    Collector.push(ptr);
    return ptr;
}

void* calloc(size_t num, size_t size) {
    void* ptr = std::malloc(num * size);
    if (!ptr) {
        throw bad_alloc();
    }
    std::memset(ptr, 0, num * size);
    return ptr;
}

void* realloc(void* ptr, size_t size) {
    void* new_ptr = std::realloc(ptr, size);
    if (!new_ptr) {
        throw bad_alloc();
    }
    Collector.push(new_ptr);
    return new_ptr;
}

void free(void* ptr) {
    std::free(ptr);
    ptr = nullptr;
}

void clean() {
    cout << "Starting cleanup..." << endl;
    while (!Collector.empty()) {
        Collector.pop();
    }
    cout << "Collector emptied: " << Collector.empty() << endl << flush;
}

int main() {
    atexit(clean);

    int* p1 = new int(10);
    float* p2 = new float(20.2020);
    string* p3 = new string("hola");

    return 0;
}
