#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H


class IComponentArray
{
    
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:
    void Add(int index, T component)
    {
        array[index] = component;
    }
    T& Get(int index)
    {
        return array[index];
    }
    
private:
    std::array<T, MAX_ENTITIES> array;
};


#endif

