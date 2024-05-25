#include <iostream>
#include <string>

template <typename T>
class QueueRing {
   private:
    T* queue;  // Указатель на очередь
    size_t iHead;
    size_t iTail;
    unsigned int size;
    unsigned int count;  // Текущая длина очереди
   public:
    QueueRing(unsigned int initialsize) {
        queue = new T[initialsize];  // выделение памяти
        count = initialsize;  // инициализация переменной, отвечающей за размер
                              // вектора
        size = 0;  // обнуление индексной переменной
        iHead = -1;
        iTail = -1;
    }
    QueueRing(const QueueRing& sourse) {
        count = sourse.count;  // инициализация переменной, отвечающей за размер
        queue = new T[count];  // выделение памяти
        iHead = -1;
        iTail = -1;
        for (int i = 0; i < count; i++) {
            queue[i] = sourse.queue[i];
        }
    }
    QueueRing& operator=(const QueueRing& sourse) {
        count = sourse.count;  // инициализация переменной, отвечающей за размер
        queue = new T[count];  // выделение памяти
        iHead = -1;
        iTail = -1;
        for (int i = 0; i < count; i++) {
            queue[i] = sourse.queue[i];
        }
        return *this;
    }
    void clear() { *this = QueueRing(); }  // ЗАСРАЛИ ПЕРЕДЕЛАЙ
    ~QueueRing() {
        delete[] queue;  // освободить память, выделенную под очередь
    }
    bool isEmpty() { return count == 0; }
    void Add(const T& data) {
        // Проверяем, не является ли очередь пустой
        if (size == 0) {
            // Добавляем данные в очередь
            iTail = 0;
            iHead = 0;
            queue[iTail] = data;
            // Обновляем индекс хвоста
            // Проверяем, достиг ли индекс хвоста максимального значения
            if (iTail == count) {
                // Бросаем исключение, если индекс хвоста вышел за границы
                throw std::out_of_range("Queue is full!");
            }
        } else {
            iTail = (iTail + 1) % count;
            queue[iTail] = data;
        }
        size++;
    }
    /**
    + * Удаляет и возвращает элемент из начала очереди.
    + *
    + * @throws Exception если очередь пуста
    + * @return элемент из начала очереди
    + */
    T Pop() {
        // Проверяем, пуста ли очередь
        if (size == 0) throw std::runtime_error("Пустой");

        // Получаем элемент из начала очереди
        T temp = queue[iHead];
        queue[iHead] = 0;
        // Обновляем индекс начала очереди
        iHead = (iHead + 1) % count;

        // Возвращаем удаленный элемент
        return temp;
    }
    void Print(std::string msg) {
        std::cout << msg << " ";
        for (int i = 0; i < count; i++) {
            std::cout << queue[i] << " ";
        }
        std::cout << std::endl;
    }
    class Iterator {
        friend class QueueRing;
        T* mpPos;  // указатель на текущее положение итератора внутри
                   // массива
       public:
        T& operator*() {
            if (*mpPos) {
                return *mpPos;
            } else {
                throw std::runtime_error("Invalid iterator position");
            }
        }
        Iterator operator++(int) {
            Iterator temp = *this;
            mpPos++;
            return temp;
        }
        bool operator!=(const Iterator& pos) {
            if (mpPos != pos.mpPos) {
                return true;
            } else {
                return false;
            }
        }
    };
    Iterator begin() {
        Iterator temp;
        temp.mpPos = queue;
        return temp;
    }
    Iterator end() {
        Iterator temp;
        temp.mpPos = (queue + iTail);
        return temp;
    }
};

int main() {
    QueueRing<int> Q(4);
    std::cout << std::endl;

    // Добавить элементы в очередь
    Q.Add(25);
    Q.Add(12);
    Q.Add(89);
    Q.Add(123);
    Q.Print("Q.Add(...): ");
    Q.Pop();
    Q.Pop();
    Q.Print("Q.Add(...): ");
    Q.Add(255);
    Q.Print("Q.Add(...): ");
}
