#pragma once 
#include<iostream>
#include<stdexcept>
#include<cstring>

/**
 * @brief:目标写出一个和STL一样具有高性能和跨平台的Vector容器
 * 
*/

namespace Sakura
{
namespace Stl
{
template <class T>
class Vector
{
public:
    Vector();
    ~Vector();
    //尾部插入数据
    void push_back(const T &value);
    //尾部弹出数据
    void pop_back();
    //获取容器的大小
    int size() const;
    //获取容器容量
    int capacity() const;
    //打印容器中的数据，方便测试
    void print();
    //自定义容器容量
    void reserve(int n);
    //自定义容器大小
    void resize(int size);
    //获取索引下标表示的值
    T & at(int index);
    //[]运算符重载
    T & operator [] (int index);
    //判断数组是否为空
    bool empty();
    //清空数组中的元素
    void clear();
    //获取数组中第一个元素
    T & front();
    //获取数组中最后一个元素
    T & back();
    //数组交换(数据、大小、容量)
    void swap(Vector<T> &other);
    //返回数组指针
    T * data();
    //运算符重载实现数组的赋值操作
    Vector<T> & operator = (Vector<T> & other);
    //判断容器内部的基本类型
    bool is_basic_type();



//正向迭代器类
class Iterator
{
public:
    Iterator() : m_pointer(nullptr){}
    Iterator(T *pointer) : m_pointer(pointer) {}
    ~Iterator(){}

    bool operator == (const Iterator &other)
    {
        if(m_pointer==other.m_pointer)
        {
            return true;
        }
        return false;
    }
    bool operator != (const Iterator &other)
    {
        if(m_pointer !=other.m_pointer)
        {
            return true;
        }
        return false;
    }

    Iterator & operator = (const Iterator &other)
    {
        m_pointer=other.m_pointer;
        return *this;
    }
    //前置加1
    Iterator operator ++ ()
    {
        m_pointer+=1;
        return *this;
    }
    //后置加1
    Iterator operator ++ (int)
    {
        Iterator it=*this;
        ++(*this);
        return it;
    }
    //迭代器加法运算重载
    Iterator operator + (int value)
    {
        Iterator it=*this;
        it.m_pointer+=value;
        return it;
    }
    //迭代器减法运算重载
    Iterator & operator - (int value)
    {
        Iterator it=*this;
        it.m_pointer-=value;
        return it;
    }
    //迭代器+=运算重载
    Iterator & operator += (int value)
    {
        m_pointer+=value;
        return *this;
    }
    //迭代器-=运算符重载
    Iterator & operator -= (int value)
    {
        m_pointer-=value;
        return *this;
    }
    //两个迭代器相减运算符重载
    int operator - (const Iterator &other) const
    {
        return m_pointer-other.m_pointer;
    }
    //迭代器解引用运算符重载
    T & operator * ()
    {
        return *m_pointer;
    }
    //迭代器指针操作的运算符重载
    T * operator -> ()
    {
        return m_pointer;
    }
private:
    T *m_pointer;
    
};

    //起始迭代器
    Iterator begin();
    //结束迭代器
    Iterator end();
    //查找元素
    Iterator find(const T &value);
    //删除指定元素
    Iterator erase(const Iterator it);
    Iterator erase(const Iterator first,const Iterator last);
    

    /*插入元素*/
    Iterator insert(const Iterator it,const T &value);
    Iterator insert(const Iterator it,int n,const T &value);

private:
//存放数据
T *m_data;
//当前容器大小
int m_size;
//容器总容量
int m_capacity;

};

template <class T>
Vector<T>::Vector() : m_data(nullptr) , m_size(0) , m_capacity(0)
{

}

template <class T>
Vector<T>::~Vector()
{
    if(m_data!=nullptr)
    {
        delete [] m_data;
        m_data=nullptr;
    }
    m_size=0;
    m_capacity=0;
}

/**
 * @brief:尾插法插入数据
 * @param:泛型的数据
 * @return:无
 * @author:SY
*/
template <class T>
void Vector<T>::push_back(const T &value)
{
    if(m_size<m_capacity)
    {
        m_data[m_size]=value;
        m_size++;
        return;
    }
    if(m_capacity == 0)
    {
        m_capacity=1;
    }
    else
    {
        //容量不为0，则二倍扩容
        m_capacity *=2;
    }
    //开辟新的容量的容器
    T *data= new T[m_capacity];
    //将原来容器中的数据移动到新的容器中
    for(int i=0;i<m_size;i++)
    {
        data[i]=m_data[i];
    }
    //将原来容器的位置的内存释放
    if(m_data != nullptr)
    {
        delete [] m_data;
        m_data=nullptr;
    }
    m_data=data;
    m_data[m_size]=value;
    m_size++;
}

/**
 * @brief:尾部弹出数据
 * @param:无
 * @return:无
 * @author:SY
*/
template <class T>
void Vector<T>::pop_back()
{
    if(m_size>0)
    {
        m_size--;
    }
}

/**
 * @brief:获取容器当前大小
 * @param:无
 * @return:返回容器当前大小
 * @author:SY
*/
template <class T>
int Vector<T>::size() const
{
    return m_size;
}

/**
 * @brief:获取容器容量
 * @param:无
 * @return:返回容器容量
 * @author:SY
*/
template <class T>
int Vector<T>::capacity() const
{
    return m_capacity;
}

/**
 * @brief:打印容器的大小、容量以及数据
 * @param:无
 * @return:无
 * @author:SY
*/
template<class T>
void Vector<T>::print()
{
    //打印容器大小以及容量
    std::cout<<"size: "<< m_size << " capacity: "<< m_capacity<<std::endl;
    //打印容器中的数据
    for(int i=0;i<m_size;i++)
    {
        std::cout<<m_data[i]<<" ";
    }
    std::cout<<std::endl;
}

/**
 * @brief:重新分配容器容量
 * @param:输入的容量
 * @return:无
 * @author:SY
*/
template <class T>
void Vector<T>::reserve(int n)
{
    if(m_capacity>=n)
    {
        return;
    }
    //扩容，条件是当容量小于传入的容量大小
    while(m_capacity<n)
    {
        if(m_capacity ==0)
        {
            m_capacity=1;
        }
        else
        {
            m_capacity=n;
        }
    }
    //动态内存申请容量
    T *data=new T[m_capacity];
    for(int i=0;i<m_size;i++)
    {
        data[i]=m_data[i];
    }
    if(m_data!=nullptr)
    {
        delete [] m_data;
        m_data=nullptr;
    }
    m_data=data;
}

/**
 * @brief:重新分配容器大小
 * @param:输入的大小
 * @return:无
 * @author:SY
*/
template <class T>
void Vector<T>::resize(int size)
{
    //容器内部大小大于或等于输入的大小
    if(m_size>=size)
    {
        m_size=size;
        return;
    }
    //容器内部大小小于输入大小并且输入大小小于容器容量
    if(m_size < size && size< m_capacity)
    {
        for(int i=m_size;i<size;i++)
        {
            m_data[i]=T();
        }
        m_size=size;
    }
    //输入大小大于容器容量
    while(m_capacity<size)
    {
        if(m_capacity==0)
        {
            m_capacity=1;
        }
        else
        {
            m_capacity=size;
        }
    }
    //动态申请扩容
    T *data=new T[m_capacity];
    for(int i=0;i<m_size;i++)
    {
        data[i]=m_data[i];
    }
    for(int i=m_size;i<size;i++)
    {
        data[i]=T();
    }
    if(m_data!=nullptr)
    {
        delete [] m_data;
        m_data=nullptr;
    }
    m_data=data;
    m_size=size;
}

/**
 * @brief:获取容器索引下标的值
 * @param:容器索引下标
 * @return:返回容器索引下标的值
 * @author:SY
 * 
*/
template <class T>
T & Vector<T>::at(int index)
{
    //不符合要求的数组下标，抛出异常
    if(index<0 || index>= m_size)
    {
        throw new std::logic_error("vec[] out of range");
    }
    return m_data[index];
}

/**
 * @brief:重载中括号并获取索引下标值
 * @param:索引下标
 * @return:容器索引下标的值
 * @author:SY
*/
template <class T>
T & Vector<T>::operator [] (int index)
{
    return at(index);
}

/**
 * @brief:判断容器是否为空
 * @param:无
 * @return:若容器有数据返回true,否则返回false
 * @author:SY
*/
template <class T>
bool Vector<T>::empty()
{
    if(m_size==0)
    {
        return true;
    }
    return false;
}

/**
 * @brief:清空容器的数据
 * @param:无
 * @return:无
 * @author:SY
*/
template <class T>
void Vector<T>::clear()
{
    m_size=0;
}

/**
 * @brief:获取容器的第一个元素的值
 * @param:无
 * @return:返回容器第一个元素的值
 * @author:SY
*/
template <class T>
T & Vector<T>::front()
{
    if(m_size<=0)
    {
        throw new std::logic_error("vec is empty");
    }
    return m_data[0];
}

/**
 * @brief:获取容器最后一个元素的值
 * @param:无
 * @return:返回容器最后一个元素的值
 * @author:SY
*/
template <class T>
T & Vector<T>::back()
{
    if(m_size<=0)
    {
        throw new std::logic_error("vec is empty");
    }
    return m_data[m_size-1];
}

/**
 * @brief:交换两个容器的数据、大小以及容量
 * @param:另一个容器对象
 * @return:无
 * @author:SY
*/
template <class T>
void Vector<T>::swap(Vector<T> &other)
{
    //存储另外一个数组的临时数据
    T *data=other.m_data;
    int size=other.m_size;
    int capacity=other.m_capacity;

    other.m_data=m_data;
    other.m_size=m_size;
    other.m_capacity=m_capacity;

    m_data=data;
    m_size=size;
    m_capacity=capacity;
}

/**
 * @brief:获取容器的指针
 * @param:无
 * @return:返回容器的指针
 * @author:SY
*/
template <class T>
T * Vector<T>::data()
{
    return m_data;
}

/**
 * @brief:重载等号，让两个容器可以相互赋值
 * @param:另一个容器对象
 * @return:容器的对象
 * @author:SY
*/
template <class T>
Vector<T> & Vector<T>::operator = (Vector<T> & other)
{
    if(m_capacity < other.m_size)
    {
        if(m_data !=nullptr)
        {
            delete [] m_data;
            m_data=nullptr;
            m_size=0;
            m_capacity=0;
        }
        while(m_capacity<other.m_size)
        {
            if(m_capacity==0)
            {
                m_capacity=1;
            }
            else
            {
                m_capacity=other.m_size;
            }
        }
        m_data=new T[m_capacity];
    }
    for(int i=0;i<other.m_size;i++)
    {
        m_data[i]=other.m_data[i];
    }
    m_size=other.m_size;
    m_capacity=other.m_capacity;
    return *this;
}

//起始迭代器
template <class T>
typename Vector<T>::Iterator Vector<T>::begin()
{
    Vector<T>::Iterator it(m_data);
    return it;
}
//结束迭代器
template <class T>
typename Vector<T>::Iterator Vector<T>::end()
{
    Vector<T>::Iterator it(m_data+m_size);
    return it;
}

template <class T>
typename Vector<T>::Iterator Vector<T>::find(const T &value)
{
    for(Vector<T>::Iterator it=begin();it!=end();it++)
    {
        if(*it == value)
        {
            return it;
        }
    }
    return end();
}

template<class T>
bool Vector<T>::is_basic_type()
{
    //判断类型是否为指针
    if(std::is_pointer<T>::value)
    {
        return true;
    }
    return typeid(T) == typeid(bool)      ||
           typeid(T) == typeid(int)       ||
           typeid(T) == typeid(double)    ||
           typeid(T) == typeid(std::string) ||
           typeid(T) == typeid(char) ||
           typeid(T) == typeid(short) ||
           typeid(T) == typeid(unsigned long) ||
           typeid(T) == typeid(unsigned short) ||
           typeid(T) == typeid(unsigned int) ||
           typeid(T) == typeid(unsigned char);
}

template <class T>
typename Vector<T>::Iterator Vector<T>::insert(const Vector<T>::Iterator it,const T &value)
{
    return insert(it,1,value);
}

template <class T>
typename Vector<T>::Iterator Vector<T>::insert(const Vector<T>::Iterator it,int n,const T &value)
{
    //获取插入位置的迭代器
    auto pos=it-begin();
    //插入元素足够存放(无需扩容的情况)  
    if(m_size+n<=m_capacity)
    {
        if(is_basic_type())
        {
            //当内部内存发生重叠使用memmove，拷贝内存，否则使用memcpy
            std::memmove(m_data+pos+n,m_data+pos,(m_size-pos)*sizeof(T));
        }
        else
        {
            for(int i=m_size;i>pos;i--)
            {
                m_data[i+n-1]=m_data[i-1];
            }
        }
        for(int i=0;i<n;i++)
        {
            m_data[pos+i]=value;
        }
        m_size+=n;
        return Vector<T>::Iterator(m_data+pos);   
    }
    //插入元素过多,大于数组容量(扩容)
    while(m_size+n>m_capacity)
    {
        if(m_capacity==0)
        {
            m_capacity=1;
        }
        else
        {
            m_capacity*=2;
        }
    }
    T *data=new T[m_capacity];
    if(is_basic_type())
    {
        std::memcpy(data,m_data,m_size*sizeof(T));
    }
    else
    {
        for(int i=0;i<pos;i++)
        {
            data[i]=m_data[i];
        }
    }
    if(is_basic_type())
    {
        std::memcpy(data+pos+n,m_data+pos,(m_size-pos)*sizeof(T));
    }
    else
    {
        for(int i=pos;i<m_size;i++)
        {
            data[i]=m_data[i];
        }
    }
    for(int i=0;i<n;i++)
    {
        data[pos+i]=value;
    }
    if(m_data!=nullptr)
    {
        delete [] m_data;
        m_data=nullptr;
    }
    m_data=data;
    m_size+=n;
    return Vector<T>::Iterator(m_data+pos);
}

template<class T>
typename Vector<T>::Iterator Vector<T>::erase(const Vector<T>::Iterator it)
{
    //判断删除的元素是否为最后一个
    if(end() - it ==1)
    {
        m_size-=1;
        return end();
    }
    //删除其他位置的元素
    int pos = it - begin();
    if(is_basic_type())
    {
        std::memmove(m_data+pos,m_data+pos+1,(m_size-pos-1)*sizeof(T));
    }
    else
    {
        for(int i=pos;i<m_size;i++)
        {
            m_data[i]=m_data[i+1];
        }
    }
    m_size-=1;
    return it;
}

template<class T>
typename Vector<T>::Iterator Vector<T>::erase(const Vector<T>::Iterator first,
                                              const Vector<T>::Iterator last)
{
    //获取消除元素的第一个区间
    int f=first - begin();
    //获取消除元素的第二个区间
    int l=last - begin();
    //数组长度变化
    int pos = last - first;
    //判断是否为基本类型，提高删除性能
    if(is_basic_type())
    {
        std::memmove(m_data+f,m_data+l,(m_size-l)*sizeof(T));
    }
    else
    {
        //元素向前移动
        for(int i=0;i<m_size-l;i++)
        {
            m_data[f]=m_data[l];
        }
    }
    m_size-=pos;
    return first;
}

}
}