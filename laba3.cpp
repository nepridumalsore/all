#include <stdio.h>
#include <stdlib.h>
#include <iostream>

template <typename T, typename D, typename K>
class BST
{
public:
    // Структура узла дерева
    struct Node
    {
        D data;                                                                          // Данные, хранящиеся в узле
        K key;                                                                           // Ключ
        Node *left = nullptr;                                                            // Указатель на левое поддерево
        Node *right = nullptr;                                                           // Указатель на правое поддерево
        Node(const K &k, const D &d) : key(k), data(d), left(nullptr), right(nullptr) {} // Конструктор
    };
    Node *root = nullptr;
    size_t mnSize; // Количество узлов в дереве

    BST()
    { // Конструктор по умолчанию
        mnSize = 0;
        root = nullptr;
    }

    // Внутренний итератор для обхода дерева
    typedef struct bstiterator
    {
        Node *node;                             // Указатель на текущий узел итератора
        bstiterator(Node *node) : node(node) {} // Конструктор, инициализирующий указатель на узел

        // Переопределение оператора инкремента для движения по дереву
        bstiterator &operator++()
        {
            if (node->right != nullptr)
            {                       // Если есть правое поддерево
                node = node->right; // Переходим к самому левому узлу в правом поддереве
                while (node->left != nullptr)
                {
                    node = node->left;
                }
            }
            else
            {                                // Если нет правого поддерева
                Node *parent = node->parent; // Получаем родительский узел
                while (node == parent->right)
                {                            // Пока текущий узел - правый потомок своего родителя
                    node = parent;           // Переходим к родителю
                    parent = parent->parent; // Получаем нового родителя
                }
                if (parent == nullptr)
                {                   // Если достигнут корень дерева
                    node = nullptr; // Итератор устанавливается в нулевое состояние
                }
                else
                {
                    node = parent; // Иначе, устанавливаем итератор на родителя (следующий узел в порядке обхода)
                }
            }
            return *this; // Возвращаем ссылку на текущий итератор
        }
    } *BSTPOSITION; // Тип BSTPOSITION - указатель на bstiterator
private:
    BSTPOSITION oIterator; // Позиция итератора в дереве BST
    class iteratorstack
    {
    private:
        BSTPOSITION top = nullptr;    // Текущая позиция итератора
        BSTPOSITION bottom = nullptr; // Начальная позиция итератора
    public:
        Node *m_pTop = nullptr; // Указатель на текущий узел
        iteratorstack()         //
        {
            // Конструктор по умолчанию
            top = nullptr;
            bottom = nullptr;
        }
        iteratorstack(BSTPOSITION top, BSTPOSITION bottom)
        {
            // Конструктор с параметрами
            this->top = top;
            this->bottom = bottom;
        }
        void push(Node *pLeaf)
        {
            if (pLeaf == nullptr)
            {
                // Если переданный узел пуст, то ничего не делаем
                return;
            }

            if (root == nullptr)
            {
                // Если дерево пустое, то делаем переданный узел корнем дерева
                root = pLeaf;
                return;
            }

            // Иначе, ищем место для вставки узла в бинарное дерево поиска
            Node *current = root;
            while (true)
            {
                if (pLeaf->data < current->data)
                {
                    // Если значение вставляемого узла меньше значения текущего узла,
                    // двигаемся влево
                    if (current->left == nullptr)
                    {
                        // Если левого потомка нет, то вставляем узел сюда
                        current->left = pLeaf;
                        break;
                    }
                    else
                    {
                        // Иначе, двигаемся влево и продолжаем поиск места для вставки
                        current = current->left;
                    }
                }
                else if (pLeaf->data > current->data)
                {
                    // Если значение вставляемого узла больше значения текущего узла,
                    // двигаемся вправо
                    if (current->right == nullptr)
                    {
                        // Если правого потомка нет, то вставляем узел сюда
                        current->right = pLeaf;
                        break;
                    }
                    else
                    {
                        // Иначе, двигаемся вправо и продолжаем поиск места для вставки
                        current = current->right;
                    }
                }
                else
                {
                    // Если значение вставляемого узла равно значению текущего узла,
                    // то решите, что делать в этом случае (например, игнорировать
                    // дублирующиеся значения или обновлять данные текущего узла)
                    break;
                }
            }
        }
        Node *Pop()
        { // Метод для удаления узла из стека
            if (root == nullptr)
            {
                // Если дерево пустое, возвращаем nullptr
                return nullptr;
            }

            Node *current = root;
            Node *parent = nullptr;

            // Находим самый правый узел (узел с максимальным значением) в дереве
            while (current->right != nullptr)
            {
                parent = current;
                current = current->right;
            }

            if (parent != nullptr)
            {
                // Если у найденного узла есть родитель, удаляем его правого потомка
                parent->right = current->left;
            }
            else
            {
                // Если у найденного узла нет родителя, обновляем корень дерева
                root = current->left;
            }

            // Возвращаем найденный узел
            return current;
        }
        void clear()
        {
            // Рекурсивно удаляем все узлы в дереве
            clearRecursive(root);

            // Обнуляем корень дерева
            root = nullptr;
        }

        void clearRecursive(Node *node)
        {
            if (node == nullptr)
            {
                // Если узел пустой, выходим из рекурсии
                return;
            }

            // Рекурсивно удаляем левое и правое поддерево
            clearRecursive(node->left);
            clearRecursive(node->right);

            // Удаляем текущий узел
            delete node;
        }
    };
    iteratorstack stack; // Стек для обхода дерева

public:
    BSTPOSITION GetHead()
    {                                   // Метод для получения первого элемента в порядке обхода
        if (!root)                      // Если корень дерева не существует
            return NULL;                // Возвращаем нулевой указатель
        stack.clear();                  // Очищаем стек
        stack.push(root);               // Помещаем корень дерева в стек
        return (BSTPOSITION)&oIterator; // Возвращаем указатель на объект oIterator, приведенный к типу BSTPOSITION
    }
    K GetNext(BSTPOSITION &pos)
    {                      // Метод для получения следующего элемента в порядке обхода
        K tempdata;        // Временная переменная для хранения данных
        if (!stack.m_pTop) // Если стек пуст
            throw;         // Генерируем исключение (ошибка)

        tempdata = stack.m_pTop->Node->key;  // Сохраняем ключ текущего узла во временную переменную
        Node *currnode = stack.m_pTop->Node; // Сохраняем указатель на текущий узел
        stack.Pop();                         // Удаляем верхний элемент из стека
        if (currnode->right)                 // Если есть правое поддерево у текущего узла
            stack.push(currnode->right);     // Помещаем правое поддерево в стек
        if (currnode->left)                  // Если есть левое поддерево у текущего узла
            stack.push(currnode->left);      // Помещаем левое поддерево в стек
        if (!stack.m_pTop)                   // Если стек пуст
            pos = NULL;                      // Устанавливаем позицию в нулевое состояние
        return tempdata;                     // Возвращаем сохраненное значение ключа
    }
    void Add1(Node *node, const K &key, const D &data)
    {
        Node *newnode = new Node(key, data); // Создаем новый узел
        if (!node)                           // Если корень дерева не существует
            node = newnode;                  // Сохраняем указатель на новый узел
        else
            node = newnode; // Сохраняем указатель на новый узел
        if (key < node->key)
            node->left = newnode;
        else
            node->right = newnode;
    }
    void Add(const K &key, const D &data)
    {
        Add1(root, key, data);
    }
};

int main()
{
    BST<int, int> bst;
    bool flag;
    int c, k, d;
    BST<int, int>::BSTPOSITION position;
    while (true)
    {
        std::cout << "\tМеню\n1:Добавить данные\n2:Поиск ключа по данным\n3:Удалить данные\n4:запрос объема\n5:Вывести данные\nДругое - Выход\n";
        std::cout << ">>";
        std::cin >> c;
        std::cout << "\n";
        switch (c)
        {
        case 1:
        {
            std::cout << "Введите ключ и данные\n";
            std::cin >> d;
            std::cin >> k;
            flag = bst.Insert(k, d);
            if (flag == true)
                std::cout << "Kлюч и данные успешно добавлены\n";
            else
                std::cout << "Такой ключ уже существует\n";
        }
        case 2:
        {
            std::cout << "Введите данные\n";
            std::cin >> d;
            try
            {
                k = bst.TLR(50);
                std::cout << "Ключ по этим данным = " << k << "\n";
            }
            catch (const char *error_message)
            {
                std::cout << error_message << std::endl;
            }
        }
        case 3:
        {
            std::cout << "Введите ключ, данные по которому хотите удалить\n";
            std::cin >> k;
            flag = bst.bstDel(k);
            if (flag == true)
                std::cout << "Данные успешно удалены!\n";
            else
                std::cout << "Данных по такому ключю не существует\n";
        }
        case 4:
        {
            k = bst.Size();
            std::cout << "объем данных = " << k << "\n";
        }
        case 5:
        {
            position = bst.GetHead();
            while (position != NULL)
            {
                k = bst.GetNext(position);
                std::cout << "key " << k << std::endl;
            }
        }
        default:
            return 0;
        }
    }
};