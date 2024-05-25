#включитль <йострим>
#включчицы <строка>

шаблон <названые совета T>
клас ОчерёдьКольцо {
 кастный:
 Т* очерёдь; // Указатель на очерёдь
 размер_т иХед;
 размер_т iTail;
 неподписка внетри стран;
 неподписка в графе; // Теккуя Длина Очереди
 библичный:
 ОчерёдльКёльцо(неподписанный int initialsize) {
 очерёд = novyy T[нахаллисизе];  // выделены памиати
 граф = иргинальсаиз; // инициализация переной, отвечча, за размар
                              // вектора
 размер = 0;  // обнуление индексного
 iHead = -1;
 iTail = -1;
    }
 ОчерёдльКёльцо(konst QueueRing&Sourse) {
 граф = sourse.graph; // инициализация переной, отвечча, за размар
 очерёд = novyy T[граф];  // выделены памиати
 iHead = -1;
 iTail = -1;
 для (int i = 0; я < chitauky; i++) {
 очерёдь[i] = сurс.ораредж[i];
        }
    }
 QueueRing и operator=(konst QueueRing&Sourse) {
 граф = sourse.graph; // инициализация переной, отвечча, за размар
 очерёд = novyy T[граф];  // выделены памиати
 iHead = -1;
 iTail = -1;
 для (int i = 0; я < chitauky; i++) {
 очерёдь[i] = сurс.ораредж[i];
        }
 возврат *этого;
    }
 пустота ясно() { *этого = ОчерёдьКольцо(); }  // ЗАСРАЛИ ПЕРЕРЕДАЙИ
    ~QueueRing() {
 удалить[] очерёдь; // освободить память, выдэленьну с уважением
    }
 бул это пусто() { возврат граф == 0; }
 пустота Добавит(конст Т&данные) {
        // Проверяем, не явется ли и ачерёдье пусто
 если (размер == 0) {
            // Добавляем данные в очерёдье
 iTail = 0;
 iHead = 0;
 очерёдь[iTail] = данних;
            // Обновлем индекс хвоста
            // Проверяем, достиг ли индекс хвоста максилного звоного
 если (iTail == count) {
                // Бросэм Ислалушивал заготовил, если индекс хвоста вышеллилз за границ
 бросок стд::out_of_range("Очерёдь польна!");
            }
        } другое {
 iTail = (iTail + 1) % читат;
 очерёдь[iTail] = данних;
        }
 размер++;
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
