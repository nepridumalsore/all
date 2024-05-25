#включитль <йострим>
#включитль <стэк>
#включчицы <очерёретж>
#включчицы <лимити>
шаблон <названые Типа К., Нацвани Д>
клас БСТ
{
 трактура Узель // это узель дерева
    {
 Узел *плевой, *право;
 К. Клюлович;
 Д данные;
 Узель(конст К&к, конст Д&дат) // конструктор узла дерева
        {
 ключич = к;
 данные =;
 плевой = НУЛИ;
 pRight = НЮЛИ;
        }
    };
 Узел *m_pRoot; // корень дерева
 размир_т м_нРазмер; // сколько элементов в дореве
 Узел *BSTInsert(Узел *pNode, конст К&к, конст Д&дат, бул&инс)
    {
 если (pNode == НЮРЛИ)
        {
 pNode = novyyy Узелли(к, датат);
 m_nSize++;
 ins = iscstinnyy;
 возврат пУзел;
        }
 другое
        {
 std::okchereretdg<Uzelj *> окшеридность;
 пока (стинный)
            {
 очерёдь.толкать(пУзел);
 если (пузелл->клулувич == к)
                {
 йнс = логни;
 возврат очерёдь.перёдня();
                }
 другое
                {
 если (pNode->kluluch > k)
                    {
 если (pNode->Pleleviy == НЮРЕЛИ)
                        {
 pNode->Plelevizi = novyyy Узели(к, датат);
 m_nSize++;
 ins = isstinnyy;
 возврат очерёдь.перёдня();
                        }
 другое
                        {
 pNode = pNode->PLEVI;
                        }
                    }
 другое
                    {
 если (pNode->pПраво == НУЛИ)
                        {
 pNode->pПраво = новой Узель(к, датат);
 m_nSize++;
                            ins = true;
                            return queue.front();
                        }
                        pNode = pNode->pRight;
                    }
                }
            }
        }
    }
    void tlr(Node *pNode, void (*process)(const K &k, const D &d)) // итеративный обход.
    {
        std::stack<Node *> nodeStack; // Создаем стек для хранения узлов дерева
        Node *curr = pNode;           // Устанавливаем текущий узел на переданный узел
        nodeStack.push(curr);
        while (!nodeStack.empty())
        {
            curr = nodeStack.top();
            nodeStack.pop();
            if (process)
            {
                process(curr->key, curr->data);
            }
            if (curr->pRight != NULL)
            {
                nodeStack.push(curr->pRight);
            }
            if (curr->pLeft != NULL)
            {
                nodeStack.push(curr->pLeft);
            }
        }
    }
    void clearRecursive(Node *node)
    {
        if (node == nullptr)
        {
            // Если узел пустой, выходим из рекурсии
            return;
        }

        // Рекурсивно удаляем левое и правое поддерево
        clearRecursive(node->pLeft);
        clearRecursive(node->pRight);

        // Удаляем текущий узел
        delete node;
    }
    int sizeRecursive(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return 1 + sizeRecursive(node->pLeft) + sizeRecursive(node->pRight);
    }
    Node *find(Node *node, const K &key)
    {
        if (node == NULL)
        {
            return node;
        }
        while (node != NULL)
        {
            if (node->key < key)
            {
                node = node->pRight;
            }
            else if (node->key > key)
            {
                node = node->pLeft;
            }
            else
            {
                return node;
            }
        }
        return NULL;
    }
    void replace(Node *rightNode, Node *leftNode)
    {
        if (rightNode->pLeft != NULL)
        {
            replace(rightNode->pLeft, leftNode);
            return;
        }
        rightNode->pLeft = leftNode;
    }
    Node *del(Node *t, K k, bool &deleted)
    {
        if (t == NULL)
        {
            deleted = false;
            return t;
        }
        if (k < t->key)
        {
            t->pLeft = del(t->pLeft, k, deleted);
            return t;
        }
        else if (k > t->key)
        {
            t->pRight = del(t->pRight, k, deleted);
            return t;
        }
        deleted = true;
        if (t->pLeft == NULL && t->pRight == NULL)
        {
            delete t;
            return NULL;
        }
        if (t->pLeft == NULL)
        {
            Node *temp = t->pRight;
            delete t;
            return temp;
        }
        if (t->pRight == NULL)
        {
            Node *temp = t->pLeft;
            delete t;
            return temp;
        }
        Node *temp = t->pRight;
        replace(t->pRight, t->pLeft);
        if (t == m_pRoot)
        {
            m_pRoot = temp;
        }
        delete t;
        m_nSize--;
        return temp;
    }

public:
    D contains(const K &key, const D &data)
    {
        Node *pNode = find(m_pRoot, key);
        bool contains = false;
        if (pNode && pNode->key == key)
        {
            contains = true;
            return pNode->data;
        }
        return D{}; // Возвращаем значение типа D, конструируя его по умолчанию, если ключ не найден
    }
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
    } *BSTPOSITION;             // Тип BSTPOSITION - указатель на bstiterator
    BSTPOSITION oIterator;      // Объявляем объект oIterator, приведенный к типу BSTPOSITION
    std::stack<Node *> itstack; // Объявляем стек для хранения узлов дерева

    BSTPOSITION GetHead()
    {                    // Метод для получения первого элемента в порядке обхода
        if (!m_pRoot)    // Если корень дерева не существует
            return NULL; // Возвращаем нулевой указатель
        while (itstack.size() != 0)
        {
            itstack.pop();
        }                               // Очищаем стек
        itstack.push(m_pRoot);          // Помещаем корень дерева в стек
        return (BSTPOSITION)&oIterator; // Возвращаем указатель на объект oIterator, приведенный к типу BSTPOSITION
    }
    K GetNext(BSTPOSITION &pos)
    {                        // Метод для получения следующего элемента в порядке обхода
        K tempdata;          // Временная переменная для хранения данных
        if (!itstack.size()) // Если стек пуст
            throw;           // Генерируем исключение (ошибка)

        tempdata = itstack.top()->key;      // Сохраняем ключ текущего узла во временную переменную
        Node *currnode = itstack.top();     // Сохраняем указатель на текущий узел
        itstack.pop();                      // Удаляем верхний элемент из стека
        if (currnode->pRight)               // Если есть правое поддерево у текущего узла
            itstack.push(currnode->pRight); // Помещаем правое поддерево в стек
        if (currnode->pLeft)                // Если есть левое поддерево у текущего узла
            itstack.push(currnode->pLeft);  // Помещаем левое поддерево в стек
        if (itstack.empty())                // Если стек пуст
            pos = NULL;                     // Устанавливаем позицию в нулевое состояние
        return tempdata;                    // Возвращаем сохраненное значение ключа
    }
    BST() // конструктор дерева
    {
        m_pRoot = NULL;
        m_nSize = 0;
    }
    ~BST()
    {
        destroySubtree(m_pRoot);
    }
    int Size()
    {
        return sizeRecursive(m_pRoot);
    }
    void destroySubtree(Node *node)
    {
        if (node != nullptr)
        {
            destroySubtree(node->pLeft);
            destroySubtree(node->pRight);
            delete node;
        }
    }
    BST(const BST &bst) // конструктор копирования
    {
        m_pRoot = bst.m_pRoot;
        m_nSize = bst.m_nSize;
    }
    void clear() // функция очистки дерева
    {
        // Рекурсивно удаляем все узлы в дереве
        clearRecursive(m_pRoot);

        // Обнуляем корень дерева
        m_pRoot = nullptr;
    }
    bool deleteNode(const K &k)
    {
        bool deleted = false;
        m_pRoot = del(m_pRoot, k, deleted);
        if (deleted)
        {
            m_nSize--;
        }
        return deleted;
    }

    bool Insert(const K &k, const D &dat) // функция обертка для вставки. Нужна потому что при вставке нужен корень,
                                          // а давать к нему доступ снаружи нельзя, по этому вызываем отсюда приватную функцию вставки, в которую
                                          // переадим корень
    {
        bool ins;
        m_pRoot = BSTInsert(m_pRoot, k, dat, ins); // тут указатель на корень нам доступен (мы внутри класса)
        return ins;
    }
    void TLR(void (*process)(const K &k, const D &d) = NULL)
    {
        tlr(m_pRoot, process);
    }
};
template <typename K, typename D>
void BSTProcess(const K &k, const D &d) // шаблонная функция для обхода. Она просто выводит ключ и данные в консоль
{
    std::cout << "key " << k << " "
              << " Data " << d << "\n";
}

int main()
{
    BST<int, int> bst;
    bool flag;
    int c, k, d, num;
    BST<int, int>::BSTPOSITION position;
    for (int i = 75; i < 115; i++)
    {
        bst.Insert(i, i);
    }
    while (true)
    {
        std::cout << "\tМеню\n1:Добавление данных\n2:Поиск данных по ключу\n3:Удаление данных\n4:Запрос объема\n5:Итератор\n6:Вывод данных\nДругое - Выход\n";
        std::cout << ">>";
        std::cin >> c;
        std::cout << "\n";
        switch (c)
        {
        case 1:
        {
            std::cout << "Введите ключ и данные\n";
            std::cin >> k;
            std::cin >> d;
            if (std::cin.fail())
            {
                std::cout << "Неправильный ввод! Пожалуйста, введите целые числа.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            flag = bst.Insert(k, d);
            if (flag == true)
                std::cout << "Kлюч и данные успешно добавлены\n";
            else if (flag == false)
                std::cout << "Такой ключ уже существует\n";
            break;
        }
        case 2:
        {
            std::cout << "Введите ключ\n";
            std::cin >> k;
            try
            {
                d = bst.contains(k, d);
                if (d)
                {
                    std::cout << "Такой ключ существует. Вот его данные =  "
                              << d
                              << "\n";
                }
                else
                {
                    std::cout << "Такого ключа не существует = "
                              << k
                              << "\n";
                }
            }
            catch (const char *error_message)
            {
                std::cout << error_message << std::endl;
            }
            break;
        }
        case 3:
        {
            std::cout << "Введите ключ, данные по которому хотите удалить\n";
            std::cin >> k;
            flag = bst.deleteNode(k);
            if (flag == true)
                std::cout << "Данные успешно удалены!\n";
            else
                std::cout << "Данных по такому ключю не существует\n";
            break;
        }
        case 4:
        {
            k = bst.Size();
            std::cout << "объем данных = " << k << "\n";
            break;
        }
        case 5:
            position = bst.GetHead();
            while (position != NULL)
            {
                num = bst.GetNext(position);
                std::cout << "Ключ " << num << std::endl;
            }
            break;
        case 6:
        {
            bst.TLR(BSTProcess<int>);
            break;
        }
        default:
            return 0;
        }
    }
};
