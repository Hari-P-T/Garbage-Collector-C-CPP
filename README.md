# 🧹 Garbage Collector for C/C++

A **lightweight, thread-safe memory management system** for C/C++ programs that automatically tracks and cleans up dynamically allocated memory using a stack-based approach.

---

## 📖 Overview

**Garbage Collector C/C++** provides an easy way to manage memory safely in native C/C++ projects. It wraps standard dynamic allocation functions (`malloc`, `calloc`, `realloc`) with custom versions that automatically track and free all allocated memory at program exit—eliminating leaks and reducing the risk of dangling pointers.

---

## 📦 Features

- ✅ **Automatic Memory Cleanup** using a stack-based tracking system  
- 🧵 **Thread-Safe** with internal mutex protection  
- 🔁 Replacements for `malloc`, `calloc`, and `realloc`  
- 📉 Reduces memory leaks in large or long-running applications  
- 📦 Easy to integrate into any C/C++ project  

---

## 📁 Project Structure

```
Garbage-Collector-C-CPP/
├── include/
│   └── collector.h         # Public API header
├── src/
│   └── collector.c         # Implementation of memory manager
├── test/
│   └── main.c              # Example usage and test case
├── Makefile                # Build automation
└── README.md               # This file
```

---

## 🚀 Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/Hari-P-T/Garbage-Collector-C-CPP.git
   cd Garbage-Collector-C-CPP
   ```

2. **Build the project** using the provided Makefile:
   ```bash
   make
   ```

---

## 🛠 Usage

Run the compiled test program:
```bash
./test/collector_test
```

Example output:
```
Starting cleanup...
Collector emptied: 1
```

### ✅ Integrating into Your Project

1. Include the header:
   ```c
   #include "collector.h"
   ```

2. Use the safe allocators:
   ```c
   void* ptr = custom_malloc(size);
   void* array = custom_calloc(num, size);
   ptr = custom_realloc(ptr, new_size);
   ```

3. Register automatic cleanup:
   ```c
   atexit(clean);  // Ensures all tracked memory is freed at exit
   ```

4. Optionally, use `custom_free(ptr)` to manually release memory earlier if needed.

---

## 🧪 Example

```c
#include <stdio.h>
#include "collector.h"

int main() {
    atexit(clean);  // Automatically cleanup on exit

    int* data = (int*)custom_calloc(10, sizeof(int));
    for (int i = 0; i < 10; i++) {
        data[i] = i * 2;
    }

    data = (int*)custom_realloc(data, 20 * sizeof(int));

    char* msg = (char*)custom_malloc(100);
    snprintf(msg, 100, "Hello, Collector!");

    printf("%s\n", msg);
    return 0;
}
```

---

## 🤝 Contributing

We welcome contributions!

1. Fork the repository  
2. Create a new branch: `git checkout -b feature/MyFeature`  
3. Commit your changes: `git commit -m "Add MyFeature"`  
4. Push your branch: `git push origin feature/MyFeature`  
5. Open a pull request  

---

## 📜 License

Distributed under the **MIT License**. See [`LICENSE`](LICENSE) for details.

---

## 🙋 Contact

**Hari P T**  
📧 [hariptlinux@gmail.com](mailto:hariptlinux@gmail.com)  
🔗 [LinkedIn](https://in.linkedin.com/in/hari-p-t-5b585b253)  
📂 [Project Repo](https://github.com/Hari-P-T/Garbage-Collector-C-CPP)
