#include <print>
#include <vector>


namespace V1
{
    template <typename T>
    void printElement(
        const std::vector<T>& vec,typename std::vector<T>::size_type index)
    {
        if (index >= std::size(vec))
        {
            std::println("Invalid index");
        }
        else
        {
            std::println("The element has value {}", vec[index]);
        }
    }
}

inline namespace V2
{
    template <typename T>
    void printElement(
        const std::vector<T>& vec, int index)
    {
        if (index < 0 || index >= std::ssize(vec))
        {
            std::println("Invalid index");
        }
        else
        {
            std::println(
                "The element has value {}",
                vec[static_cast<std::vector<T>::size_type>(index)]);
        }
    }
}


int main()
{
    std::vector v1 { 0, 1, 2, 3, 4 };
    printElement(v1, 2);
    printElement(v1, 5);

    std::vector v2 { 1.1, 2.2, 3.3 };
    printElement(v2, 0);
    printElement(v2, -1); // Note warning here

    return 0;
}