#include <cstddef>
#include <iostream>
// 1. Конструктор по умолчанию и при необходимости конструктор
// с параметром.
// 2. Конструктор копии и переопределенный оператор присваивания.
// Реализация этих членов класса позволит корректно работать не только
// с динамически созданными экземплярами коллекции, но и со статиче-
// скими объектами (копирование и присваивание переменной-указателя
// реализовано «системой»).
// 3. Деструктор.
// 4. Метод запроса объема данных, хранимых в коллекции.
// 5. Метод очистки коллекции.
// 6. Метод добавления данных в коллекцию.
// 7. Метод запроса данных из коллекции (если коллекция позволяет,
// то переопределение оператора []).
// 8. Итератор-методы, возвращающие итератор на начало и конец,
// оператор * (получения данных по текущему итератору), а также опера-
// тор инкремента (декремента, если коллекция позволяет).
// 9. Метод резервирования свободного места в коллекции.
template <typename T>
class Cvector {
   private:
    T *m_pArray;  // указатель на массив хранящий пользовательские данные
    unsigned int mnIndex;  // переменная отвечающая за индекс
    unsigned int mnSize;  // переменная отвечающая за размер массива
   public:
    Cvector() {
        m_pArray = new T[10];  // выделение памяти
        mnSize = 10;  // инициализация переменной, отвечающей за размер вектора
        mnIndex = 0;  // обнуление индексной переменной
    }
    Cvector(unsigned int initialsize) {
        m_pArray = new T[initialsize];  // выделение памяти
        mnSize = initialsize;  // инициализация переменной, отвечающей за размер
                               // вектора
        mnIndex = 0;  // обнуление индексной переменной
    }
    Cvector(const Cvector &sourse) {
        mnSize =
            sourse.mnSize;  // инициализация переменной, отвечающей за размер
        mnIndex = sourse.mnIndex;  // инициализация индексной переменной
        m_pArray = new T[mnSize];  // выделение памяти
        for (int i = 0; i < mnSize; i++) {
            m_pArray[i] = sourse.m_pArray[i];
        }
    }
    ~Cvector() { delete m_pArray; }
    size_t Size() { return mnIndex; }
    T &operator[](unsigned int ind) {  // извлечение данных вектора
        if (ind >= 0 & ind < mnIndex) {
            return m_pArray[ind];
        } else {
            throw;
        }
    }
    Cvector &operator=(const Cvector &sourse) {
        mnSize =
            sourse.mnSize;  // инициализация переменной, отвечающей за размер
        mnIndex = sourse.mnIndex;  // инициализация индексной переменной
        m_pArray = new T[mnSize];  // выделение памяти
        for (int i = 0; i < mnSize; i++) {
            m_pArray[i] = sourse.m_pArray[i];
        }
        return *this;
    }
    // Метод для очистки коллекции
    void clear() { *this = Cvector(); }
    // Если массив заполнен, то удваивает размер массива и копирует существующие
    // элементы в новый массив.
    void PushBack(const T &data) {
        if (mnIndex == mnSize) {  // Проверяем, заполнен ли массив
            T *pBuf =
                new T[2 * mnSize];  // Создаем новый массив с удвоенным размером
            for (int i = 0; i < mnSize;
                 i++) {  // Копируем существующие элементы в новый массив
                pBuf[i] = m_pArray[i];
            }
            delete m_pArray;  // Удаляем старый массив
            m_pArray = pBuf;  // Обновляем указатель на новый массив
            mnSize *= 2;  // Обновляем размер массива
        }
        m_pArray[mnIndex] = data;  // Добавляем новый элемент в конец массива
        mnIndex++;  // Обновляем индекс
    }
    void PushBack2(const Cvector &data) {
        if (mnIndex == mnSize) {  // Проверяем, заполнен ли массив
            T *pBuf =
                new T[2 * mnSize];  // Создаем новый массив с удвоенным размером
            for (int i = 0; i < mnSize;
                 i++) {  // Копируем существующие элементы в новый массив
                pBuf[i] = m_pArray[i];
            }
            delete m_pArray;  // Удаляем старый массив
            m_pArray = pBuf;  // Обновляем указатель на новый массив
            mnSize *= 2;  // Обновляем размер массива
        }
        m_pArray[mnIndex] = data;  // Добавляем новый элемент в конец массива
        mnIndex++;  // Обновляем индекс
    }
    void reserve(const T &data) {
        if (data > mnSize) {
            T *pBuf = new T[data];
            for (int i = 0; i < mnSize; i++) {
                pBuf[i] = m_pArray[i];
            }

            delete[] m_pArray;
            m_pArray = pBuf;
            mnSize = data;
        } else {
            throw;
        }
    }

    class Iterator {
        friend class Cvector;
        T *mpPos;  // указатель на текущее положение итератора внутри
                   // массива
       public:
        T &operator*() {
            if (*mpPos) {
                return *mpPos;
            } else {
                throw;
            }
        }
        Iterator operator++(int) {
            Iterator temp = *this;
            mpPos++;
            return temp;
        }
        bool operator!=(const Iterator &pos) {
            if (mpPos != pos.mpPos) {
                return true;
            } else {
                return false;
            }
        }
    };
    Iterator begin() {
        Iterator temp;
        temp.mpPos = m_pArray;
        return temp;
    }
    Iterator end() {
        Iterator temp;
        temp.mpPos = (m_pArray + mnIndex);
        return temp;
    }
};

// void AddHead(const T &data) {
//     Node *pNode = new Node(data);  // создать новый узел с заданными
//     данными pNode->pNext = mpHead;  // установить указатель на следующий
//     элемент
//                             // нового узла на текущую голову списка
//     pHead = pNode;  // установить новый узел в качестве головы
//     mnSize++;  // увеличить размер списка
// }
// void AddTail(const T &data) {
//     Node *pNode = new Node(data);  // создать новый узел с заданными
//     данными pNode->pNext = mpTail;  // установить указатель на следующий
//     элемент
//                             // нового узла на текущий хвост списка
//     pTail = pNode;  // установить новый узел в качестве головы
//     mnSize++;  // увеличить размер списка
// }
// void InsertAt(const T &data, const Iterator &pos) {
//     Node *pNodeA =
//         pos->pTemp;  // временно закидываем указатель элемента А в темп
//     Node *pNodeB = pNodeA->pNext;  // указатель В
//     Node *pNodeC = new Node(data);  // создание нового элемента
//     pNodeC->pNext = pNodeB;  // С перед В
//     pNodeA->pNext = pNodeC;  // А перед С
// }
// strutc Node {
//     Node *pNode;
//     T data;
//     Node(const T &value) {
//         pNext = NULL;
//         data = value
//     }
// }

// bool Search(
//     const T &value)  // Ищет узел с указанным значением в связанном
//     списке.
// {
//     Node *pTemp = new mpHead;
//     while (pTemp) {
//         if (pTemp->data == value) {
//             return true;
//         }
//         pTemp = pTemp->pNext;
//     }
//     else {
//         return false
//     }
// }

int main() {
    // int a, c, choice;
    // Cvector<int>::Iterator It, pos, end;
    // while (1) {
    //     std::cout << "проверяйте:" << std::endl;
    //     std::cin >> choice;
    //     switch (choice) {
    //         case 1:
    //             // Код для случая 1
    //             std::cout << "Вы выбрали узнать размер вектора, лоадинг..."
    //                       << std::endl;
    //             c = vec.Size();
    //             std::cout << "Объем данных хранящихся в коллекци = " << c
    //                       << "\n";
    //             break;
    //         case 2:
    //             // Код для случая 2
    //             std::cout << "Выбран случай, когда вы хотите добавить
    //             элемент. "
    //                       << std::endl;
    //             std::cin >> c;
    //             vec.PushBack(c);
    //             break;
    //         case 3:
    //             // Код для случая 3
    //             std::cout << "Выбран метод очистки" << std::endl;
    //             vec.clear();
    //             break;
    //         case 4:
    //             std::cout << "Выбран метод запроса данных" << std::endl;
    //             c = scanf("Выберите элемент, который хотите вывести:%d", &c);
    //             std::cout << "выводимый элемент ==" << vec[c] << "";
    //         case 5:
    //             std::cout << "Выбран метод вернуться в начало массива"
    //                       << std::endl;
    //             It = vec.begin();
    //             break;
    //         case 6:
    //             std::cout << "Выбран метод вернуться в конец массива"
    //                       << std::endl;
    //             It = vec.end();
    //             break;
    //         case 7:
    //             std::cout << "Выбран метод инкрементации." << std::endl;
    //             It++;
    //             std::cout << "Инкрементация завершена." << std::endl;
    //             break;
    //         case 8:
    //             std::cout << "Выбран оператор *" << std::endl;
    //             std::cout << "/// = " << *It << "\n";
    //             std::cout << "ра завершена." << std::endl;
    //             break;
    //         case 9:
    //             std::cout << "Выбран метод резервирования" << std::endl;
    //             c = scanf("...:%d", &c);
    //             vec.reserve(c);

    //         default:
    //             return 0;
    //     }
    // }
    size_t n;
    std::cin >> n;

    Cvector<Cvector<int>> vec1;  // Cvector<int> vec2(n);
    for (int i = 0; i < n; i++) {
        vec1.PushBack(Cvector<int>(n));
    }
    int y = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            vec1[i][j] = y++;  // rand() % 20;
            std::cout << vec1[i][j] << " ";
        }
        std::cout << std::endl;
    }
}