#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std;

template <typename T>
struct Trash {
    T* pointer;
    Trash* next;
    Trash(T* input) : pointer(input), next(nullptr) {
        cout << "struct Trash() been called\n";
    }
};

void clean();

template <typename T>
class Trash_Stack {
private:
    Trash<T>* head;
    size_t size;

public:
    Trash_Stack() : head(nullptr), size(0) {
        cout << "class Trash_Stack() been called\n";
    }

    void push(T* gb) {
        Trash<T>* temp = new Trash<T>(gb);
        temp->next = head;
        head = temp;
        size++;
        cout << "class Trash_Stack's push() been called\n";
    }

    bool empty() const {
        return size == 0;
    }

    void pop() {
        if (empty()) {
            cerr << "Stack underflow" << endl;
        } else {
            Trash<T>* temp = head;
            head = head->next;
            free(temp->pointer);
            delete temp;
            size--;
            cout << "class Trash_Stack's pop() been called\n"; // Corrected log message
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
    cout << "overloaded new() been called\n";
    return ptr;
}

void operator delete(void* ptr) noexcept {
    std::free(ptr);
    cout << "overloaded delete() been called\n";
}

void* operator new[](size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        throw bad_alloc();
    }
    Collector.push(ptr);
    cout << "overloaded new[]() been called\n";
    return ptr;
}

void operator delete[](void* ptr) noexcept {
    std::free(ptr);
    cout << "overloaded delete[]() been called\n";
}

void* malloc(size_t size) {
    void* ptr = std::malloc(size);
    if (!ptr) {
        throw bad_alloc();
    }
    Collector.push(ptr);
    cout << "overloaded malloc() been called\n";
    return ptr;
}

void free(void* ptr) {
    std::free(ptr);
    cout << "overloaded free() been called\n";
}

void clean() {
    cout << "Starting cleanup..." << endl;
    while (!Collector.empty()) {
        Collector.pop();
    }
    cout << "Collector emptied: " << Collector.empty() << endl;
}

int main() {
    try {
        cerr << "main() has started\n";
        int* p1 = new int(10);
        cout << "Allocated p1\n";
        float* p2 = new float(20.2020);
        cout << "Allocated p2\n";
        string* p3 = new string("hola");
        cout << "Allocated p3\n";
        clean();
        cout << "Cleanup completed\n";
    } catch (const bad_alloc& e) {
        cerr << "Memory allocation failed: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
    }
    return 0;
}
