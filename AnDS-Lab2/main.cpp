#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    // Конструктор по умолчанию
    LinkedList() : head(nullptr), tail(nullptr) {}

    // Конструктор копирования
    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr) {
        Node<T>* current = other.head;
        while (current) {
            push_tail(current->data);
            current = current->next;
        }
    }

    // Конструктор, заполняющий список случайными значениями
    LinkedList(int size) : head(nullptr), tail(nullptr) {
        srand(static_cast<unsigned>(time(nullptr)));
        for (int i = 0; i < size; ++i) {
            push_tail(rand() % 100);  // Генерация случайных чисел от 0 до 99
        }
    }

    // Деструктор
    ~LinkedList() {
        clear();
    }

    // Операция присваивания
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            Node<T>* current = other.head;
            while (current) {
                push_tail(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // Добавление элемента в конец списка
    void push_tail(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Добавление другого списка в конец списка
    void push_tail(const LinkedList& other) {
        Node<T>* current = other.head;
        while (current) {
            push_tail(current->data);
            current = current->next;
        }
    }

    // Добавление элемента в начало списка
    void push_head(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
    }

    // Добавление списка в начало списка
    void push_head(const LinkedList& other) {
        LinkedList reversedOther = other;
        reversedOther.reverse();
        push_tail(reversedOther);
    }

    // Удаление элемента из начала списка
    void pop_head() {
        if (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        else {
            throw std::out_of_range("List is empty");
        }
    }

    // Удаление элемента из конца списка
    void pop_tail() {
        if (head) {
            if (head == tail) {
                delete head;
                head = tail = nullptr;
            }
            else {
                Node<T>* temp = head;
                while (temp->next != tail) {
                    temp = temp->next;
                }
                delete tail;
                tail = temp;
                tail->next = nullptr;
            }
        }
        else {
            throw std::out_of_range("List is empty");
        }
    }

    // Удаление всех элементов Node с информационным полем, равным переданному
    void delete_node(const T& value) {
        Node<T>* current = head;
        Node<T>* prev = nullptr;

        while (current) {
            if (current->data == value) {
                if (current == head) {
                    pop_head();
                    current = head;
                }
                else if (current == tail) {
                    pop_tail();
                    current = nullptr;
                }
                else {
                    prev->next = current->next;
                    delete current;
                    current = prev->next;
                }
            }
            else {
                prev = current;
                current = current->next;
            }
        }
    }

    // Операция доступа по индексу (чтение)
    const T& operator[](int index) const {
        Node<T>* current = head;
        for (int i = 0; i < index && current; ++i) {
            current = current->next;
        }
        if (current) {
            return current->data;
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }

    // Операция доступа по индексу (запись)
    T& operator[](int index) {
        Node<T>* current = head;
        for (int i = 0; i < index && current; ++i) {
            current = current->next;
        }
        if (current) {
            return current->data;
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }

    // Очистка списка
    void clear() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    // Реверс списка
    void reverse() {
        Node<T>* prev = nullptr;
        Node<T>* current = head;
        Node<T>* next = nullptr;

        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        head = prev;
    }

    // Вывод списка в виде башни
    void printTowerWithColumn(const std::string& columnName) const {
        Node<T>* current = head;
        while (current) {
            std::cout << "Column " << columnName << ": " << current->data << std::endl;
            current = current->next;
        }
    }
};

// Решение задачи о Ханойской башне
template <typename T>
void hanoiTower(int n, const std::string& sourceColumn, const std::string& auxiliaryColumn, const std::string& destinationColumn,
    LinkedList<T>& source, LinkedList<T>& auxiliary, LinkedList<T>& destination) {
    if (n > 0) {
        hanoiTower(n - 1, sourceColumn, destinationColumn, auxiliaryColumn, source, destination, auxiliary);

        std::cout << "Move disk " << source[0] << " from Column " << sourceColumn << " to Column " << destinationColumn << std::endl;
        destination.push_tail(source[0]);
        source.pop_head();

        std::cout << "Source Tower:" << std::endl;
        source.printTowerWithColumn(sourceColumn);
        std::cout << "Auxiliary Tower:" << std::endl;
        auxiliary.printTowerWithColumn(auxiliaryColumn);
        std::cout << "Destination Tower:" << std::endl;
        destination.printTowerWithColumn(destinationColumn);
        std::cout << "-------------" << std::endl;

        hanoiTower(n - 1, auxiliaryColumn, sourceColumn, destinationColumn, auxiliary, source, destination);
    }
}

int main() {

    LinkedList<int> source(3);
    LinkedList<int> auxiliary;
    LinkedList<int> destination;

    std::cout << "Source Tower:" << std::endl;
    source.printTowerWithColumn("A");
    std::cout << "Auxiliary Tower:" << std::endl;
    auxiliary.printTowerWithColumn("B");
    std::cout << "Destination Tower:" << std::endl;
    destination.printTowerWithColumn("C");
    std::cout << "-------------" << std::endl;

    try {
        hanoiTower(3, "A", "B", "C", source, auxiliary, destination);
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}