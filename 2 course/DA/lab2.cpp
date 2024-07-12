#include <bits/stdc++.h>

struct Item
{
    std::string key;
    unsigned long long number;
};

void lower(std::string &key)
{
    for (auto &symbol : key)
    {
        if (symbol >= 'A' && symbol <= 'Z')
        {
            symbol = symbol - 'A' + 'a';
        }
    }
}

bool getBitValue(std::string key, int indexBit)
{
    if (indexBit < 0)
        indexBit = 0;
    int charIndex = indexBit / 8;
    char byte = key[charIndex];
    int bitOffset = indexBit % 8;

    return (byte >> (7 - bitOffset)) & 1;
}

struct Node
{
    int id = -1;
    Item object;
    int compareBit;
    Node *leftNode;
    Node *rightNode;
    Node() : compareBit(-1)
    {
        leftNode = this;
        rightNode = this;
        object.key = "";
        object.number = 0;
    }
    Node(int bit, Item element) : compareBit(bit)
    {

        leftNode = this;
        rightNode = this;
        object.key = element.key;
        object.number = element.number;
    }
    Node(int bit, Item element, Node *left, Node *right) : compareBit(bit)
    {

        leftNode = left;
        rightNode = right;
        object.key = element.key;
        object.number = element.number;
    }
    void Init(int bit, Item element, Node *left, Node *right)
    {
        compareBit = bit;
        leftNode = left;
        rightNode = right;
        object.key = element.key;
        object.number = element.number;
    }
    ~Node() {}
};

Node *rightOrLeft(Node *element, std::string &key)
{
    if (getBitValue(key, element->compareBit))
    {
        return element->rightNode;
    }
    else
    {
        return element->leftNode;
    }
}

struct PatrciaTree
{
    Node *header;
    int size;

    PatrciaTree()
    {
        header = new Node();
        size = 0;
    }
    void destroy(Node *node)
    {
        if (node->leftNode->compareBit > node->compareBit)
            destroy(node->leftNode);
        if (node->rightNode->compareBit > node->compareBit)
            destroy(node->rightNode);
        delete node;
    }
    ~PatrciaTree()
    {
        destroy(header);
    }

    bool insert(Item newElement)
    {
        Node *parent = header;
        Node *current = header->leftNode;

        while ((parent->compareBit) < (current->compareBit))
        {

            parent = current;
            current = rightOrLeft(current, newElement.key);
        }
        if (newElement.key == current->object.key)
        {
            return 0;
        }

        int differentIndexBit = 0;
        if (!(newElement.key.size() == 0 or current->object.key.size() == 0))
        {

            while (newElement.key[differentIndexBit] == current->object.key[differentIndexBit])
            {
                ++differentIndexBit;
            }
            differentIndexBit *= 8;
            while (getBitValue(newElement.key, differentIndexBit) == getBitValue(current->object.key, differentIndexBit))
            {
                ++differentIndexBit;
            }
        }

        parent = header;
        Node *placeInsert = header->leftNode;
        while ((parent->compareBit) < (placeInsert->compareBit) && (placeInsert->compareBit) < differentIndexBit)
        {
            parent = placeInsert;
            placeInsert = rightOrLeft(placeInsert, newElement.key);
        }

        try
        {
            current = new Node(differentIndexBit, newElement);
        }
        catch (const std::bad_alloc &e)
        {
            std::cout << "ERROR: fail to allocate \n";
            return 0;
        }
        if (getBitValue(newElement.key, differentIndexBit))
        {
            current->leftNode = placeInsert;
            current->rightNode = current;
        }
        else
        {
            current->leftNode = current;
            current->rightNode = placeInsert;
        }

        if (getBitValue(newElement.key, parent->compareBit))
        {
            parent->rightNode = current;
        }
        else
        {
            parent->leftNode = current;
        }
        ++size;
        return 1;
    }

    Node *find(std::string &key)
    {
        Node *parent = header;
        Node *current = header->leftNode;

        while ((parent->compareBit) < (current->compareBit))
        {

            parent = current;
            current = rightOrLeft(current, key);
        }
        if (key == current->object.key)
        {
            return current;
        }
        return 0;
    }

    bool erase(std::string &key)
    {
        Node *parent = header;
        Node *current = header->leftNode;
        Node *grandParent = nullptr;
        while ((parent->compareBit) < (current->compareBit))
        {
            grandParent = parent;
            parent = current;
            current = rightOrLeft(current, key);
        }
        if (key != current->object.key)
        {
            return 0;
        }
        if (parent == current)
        {
            if (current->rightNode == current)
            {
                if (grandParent->leftNode == current)
                {
                    grandParent->leftNode = current->leftNode;
                }
                else
                {
                    grandParent->rightNode = current->leftNode;
                }
            }
            else
            {
                if (grandParent->leftNode == current)
                {
                    grandParent->leftNode = current->rightNode;
                }
                else
                {
                    grandParent->rightNode = current->rightNode;
                }
            }
            --size;
            delete parent;
        }
        else
        {
            current->object = parent->object;
            std::string keyParent = parent->object.key;
            Node *backPointerNode = parent;
            Node *child;
            child = rightOrLeft(parent, keyParent);
            while (backPointerNode->compareBit < child->compareBit)
            {
                backPointerNode = child;
                child = rightOrLeft(child, keyParent);
            }
            if (getBitValue(keyParent, backPointerNode->compareBit))
            {
                backPointerNode->rightNode = current;
            }
            else
            {
                backPointerNode->leftNode = current;
            }
            Node *newConnection;
            if (getBitValue(key, parent->compareBit))
            {
                newConnection = parent->leftNode;
            }
            else
            {
                newConnection = parent->rightNode;
            }
            if (getBitValue(key, grandParent->compareBit))
            {
                grandParent->rightNode = newConnection;
            }
            else
            {
                grandParent->leftNode = newConnection;
            }
            --size;
            delete parent;
        }
        return 1;
    }

    void saveToFile(const std::string &path)
    {
        std::ofstream fileOut(path, std::ios::binary | std::ios::trunc);
        fileOut.write((const char *)&(size), sizeof(int));
        int index = 0;
        Node **nodes;

        try
        {
            nodes = new Node *[size + 1];
        }
        catch (const std::bad_alloc &e)
        {
            std::cout << "ERROR: fail to allocate \n";
            return;
        }
        streamLine(header, nodes, index);

        Node *node;
        for (int i = 0; i < (size + 1); ++i)
        {
            node = nodes[i];
            fileOut.write(( char *)&(node->object.number), sizeof(unsigned long long));
            fileOut.write(( char *)&(node->compareBit), sizeof(int));
            int len = node->object.key.size();
            fileOut.write(( char *)&(len), sizeof(int));
            fileOut.write(node->object.key.c_str(), len);
            fileOut.write(( char *)&(node->leftNode->id), sizeof(int));
            fileOut.write(( char *)&(node->rightNode->id), sizeof(int));
        }
        delete[] nodes;
        fileOut.close();
    }
    void streamLine(Node *node, Node **nodes, int &index)
    {

        node->id = index;
        nodes[index] = node;
        ++index;
        if (node->leftNode->compareBit > node->compareBit)
        {
            streamLine(node->leftNode, nodes, index);
        }
        if (node->rightNode->compareBit > node->compareBit)
        {
            streamLine(node->rightNode, nodes, index);
        }
    }

    void loadFromFile(const std::string &path)
    {
        std::ifstream fileIn(path, std::ios::binary);
        int loadedSize;
        fileIn.read((char *)&loadedSize, sizeof(int));
        size = loadedSize;
        if (!size){
            return;
        }

        Node **nodes = new Node *[size + 1];

        nodes[0] = header;
        for (int i = 1; i < (size + 1); ++i)
            nodes[i] = new Node();

        int bit,len,idLeft,idRight;
        std::string key = "";
        unsigned long long value;
        Item temp;
        for (int i = 0; i < (size + 1); ++i)
        {
            fileIn.read((char *)&(value), sizeof(unsigned long long));
            fileIn.read((char *)&(bit), sizeof(int));
            fileIn.read((char *)&(len), sizeof(int));
            key.resize(len);
            fileIn.read((char *)key.c_str(), len);

            fileIn.read((char *)&(idLeft), sizeof(int));
            fileIn.read((char *)&(idRight), sizeof(int));
            temp.key = key;
            temp.number = value;
            nodes[i]->Init(bit, temp, nodes[idLeft], nodes[idRight]);
        }

        delete[] nodes;
        fileIn.close();
    }
};

int main()
{
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    std::string request;
    PatrciaTree *myTrie;

    myTrie = new PatrciaTree();

    while (std::cin >> request)
    {
        if (request == "+")
        {
            Item element;
            std::cin >> element.key >> element.number;
            lower(element.key);
            if (myTrie->insert(element))
            {
                std::cout << "OK " << '\n';
                continue;
            }

            std::cout << "Exist" << '\n';
        }
        else if (request == "-")
        {
            std::string key;
            std::cin >> key;
            lower(key);
            if (myTrie->erase(key))
            {
                std::cout << "OK " << '\n';
                continue;
            }
            std::cout << "NoSuchWord" << '\n';
        }
        else if (request == "!")
        {
            std::string inputRequest, path;
            std::cin >> inputRequest >> path;
            if (inputRequest == "Save")
            {
                myTrie->saveToFile(path);
                std::cout << "OK " << '\n';
            }
            else if (inputRequest == "Load")
            {
                delete myTrie;
                myTrie=new PatrciaTree();
                myTrie->loadFromFile(path);
                std::cout << "OK " << '\n';
            }
        }
        else
        {

            lower(request);
            Node *findElement = myTrie->find(request);
            if (findElement)
            {
                std::cout << "OK: " << findElement->object.number << '\n';
                continue;
            }
            std::cout << "NoSuchWord" << '\n';
        }
    }
    delete myTrie;
    return 0;
}