#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

// Для хранения информации о ключевых словах некоторой программы имеется таблица перекрестных ссылок.Для каждого
// слова задан список номеров строк, где оно встречается, а для каждой строки - число образцов данного слова в строке.Ключевые слова
// расположены по алфавиту.Построить бинарное дерево для поиска ключевых слов.Составить программу определения общего количества вхождений заданного ключевого слова.

//поиск, вставка элемента, удаление элемента, удаление всей динамической структуры


struct TreeNode 
{
    string key;
    int count;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string k) : key(k), count(1), left(nullptr), right(nullptr) {}
};

TreeNode* Push(TreeNode* root, std::string key) 
{
    if (root == nullptr)
        return new TreeNode(key);

    if (key < root->key) 
        root->left = Push(root->left, key);

    else if (key > root->key)
        root->right = Push(root->right, key);
    else 
        // Если ключ уже существует, увеличиваем счетчик
        root->count++;

    return root;
}

TreeNode* Search(TreeNode* root, std::string key) 
{
    if (root == nullptr || root->key == key)
        return root;

    // Рекурсивно ищем в соответствующем поддереве
    if (key < root->key) 
        return Search(root->left, key);
    else 
        return Search(root->right, key);
}

TreeNode* Remove(TreeNode* root, string key) 
{
    if (root == nullptr) 
        return root;

    if (key < root->key)
        root->left = Remove(root->left, key);
    else if (key > root->key)
        root->right = Remove(root->right, key);
    else 
    {
        // Найден узел для удаления
        if (root->count > 1)
            // Если у узла есть более одного вхождения, уменьшаем счетчик
            root->count--;
        else 
        {
            TreeNode* temp = root;
            if (root->left != nullptr && root->right != nullptr) 
            {
                // Если у узла есть два потомка
                TreeNode* minRight = root->right;
                while (minRight->left != nullptr)
                    minRight = minRight->left;
                root->key = minRight->key;
                root->count = minRight->count;
                root->right = Remove(root->right, minRight->key);
            }
            else 
            {
                // У узла максимум один потомок или вообще нет потомков
                if (root->left != nullptr)
                    root = root->left;
                else if (root->right != nullptr) 
                    root = root->right;
                else 
                    root = nullptr;
                delete temp;
            }
        }
    }

    return root;
}


void RemoveAll(TreeNode* root) 
{
    if (root != nullptr) 
    {
        RemoveAll(root->left);
        RemoveAll(root->right);
        delete root;
    }
}

void PrintTree(TreeNode* root, int level = 0) 
{
    if (root != nullptr) 
    {
        cout << root->key << " (" << root->count << " раз)" << endl;
        PrintTree(root->left, level + 1);
        PrintTree(root->right, level + 1);
    }
}

int GetTotalOccurrences(TreeNode* root, std::string key) 
{
    TreeNode* result = Search(root, key);
    return (result != nullptr) ? result->count : 0;
}

int main() 
{
    system("chcp 1251");

    TreeNode* root = nullptr;

    int choice;
    string key;

    do 
    {
        cout << "1. Добавить элемент. \n";
        cout << "2. Найти элемент. \n";
        cout << "3. Удалить элемент. \n";
        cout << "4. Печать дерева. \n";
        cout << "5. Выйти. \n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите ключ для вставки: ";
            cin >> key;
            root = Push(root, key);
            break;
        case 2:
            cout << "Введите ключ для поиска: ";
            cin >> key;
            if (Search(root, key) != nullptr) 
                cout << key << " найден в дереве.\n";
            else 
                cout << key << " не найден в дереве.\n";
            break;
        case 3:
            cout << "Введите ключ для удаления: ";
            cin >> key;
            root = Remove(root, key);
            break;
        case 4:
            cout << "\nБинарное Дерево:\n";
            PrintTree(root);
            break;
        case 5:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Некорректный выбор. Введите число от 1 до 5.\n";
            break;
        }
    } while (choice != 5);

    RemoveAll(root);

    return 0;
}
