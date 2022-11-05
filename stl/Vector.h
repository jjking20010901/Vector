#pragma once 
#include<iostream>
#include<stdexcept>
#include<cstring>

/**
 * @brief:Ŀ��д��һ����STLһ�����и����ܺͿ�ƽ̨��Vector����
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
    //β����������
    void push_back(const T &value);
    //β����������
    void pop_back();
    //��ȡ�����Ĵ�С
    int size() const;
    //��ȡ��������
    int capacity() const;
    //��ӡ�����е����ݣ��������
    void print();
    //�Զ�����������
    void reserve(int n);
    //�Զ���������С
    void resize(int size);
    //��ȡ�����±��ʾ��ֵ
    T & at(int index);
    //[]���������
    T & operator [] (int index);
    //�ж������Ƿ�Ϊ��
    bool empty();
    //��������е�Ԫ��
    void clear();
    //��ȡ�����е�һ��Ԫ��
    T & front();
    //��ȡ���������һ��Ԫ��
    T & back();
    //���齻��(���ݡ���С������)
    void swap(Vector<T> &other);
    //��������ָ��
    T * data();
    //���������ʵ������ĸ�ֵ����
    Vector<T> & operator = (Vector<T> & other);
    //�ж������ڲ��Ļ�������
    bool is_basic_type();



//�����������
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
    //ǰ�ü�1
    Iterator operator ++ ()
    {
        m_pointer+=1;
        return *this;
    }
    //���ü�1
    Iterator operator ++ (int)
    {
        Iterator it=*this;
        ++(*this);
        return it;
    }
    //�������ӷ���������
    Iterator operator + (int value)
    {
        Iterator it=*this;
        it.m_pointer+=value;
        return it;
    }
    //������������������
    Iterator & operator - (int value)
    {
        Iterator it=*this;
        it.m_pointer-=value;
        return it;
    }
    //������+=��������
    Iterator & operator += (int value)
    {
        m_pointer+=value;
        return *this;
    }
    //������-=���������
    Iterator & operator -= (int value)
    {
        m_pointer-=value;
        return *this;
    }
    //����������������������
    int operator - (const Iterator &other) const
    {
        return m_pointer-other.m_pointer;
    }
    //���������������������
    T & operator * ()
    {
        return *m_pointer;
    }
    //������ָ����������������
    T * operator -> ()
    {
        return m_pointer;
    }
private:
    T *m_pointer;
    
};

    //��ʼ������
    Iterator begin();
    //����������
    Iterator end();
    //����Ԫ��
    Iterator find(const T &value);
    //ɾ��ָ��Ԫ��
    Iterator erase(const Iterator it);
    Iterator erase(const Iterator first,const Iterator last);
    

    /*����Ԫ��*/
    Iterator insert(const Iterator it,const T &value);
    Iterator insert(const Iterator it,int n,const T &value);

private:
//�������
T *m_data;
//��ǰ������С
int m_size;
//����������
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
 * @brief:β�巨��������
 * @param:���͵�����
 * @return:��
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
        //������Ϊ0�����������
        m_capacity *=2;
    }
    //�����µ�����������
    T *data= new T[m_capacity];
    //��ԭ�������е������ƶ����µ�������
    for(int i=0;i<m_size;i++)
    {
        data[i]=m_data[i];
    }
    //��ԭ��������λ�õ��ڴ��ͷ�
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
 * @brief:β����������
 * @param:��
 * @return:��
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
 * @brief:��ȡ������ǰ��С
 * @param:��
 * @return:����������ǰ��С
 * @author:SY
*/
template <class T>
int Vector<T>::size() const
{
    return m_size;
}

/**
 * @brief:��ȡ��������
 * @param:��
 * @return:������������
 * @author:SY
*/
template <class T>
int Vector<T>::capacity() const
{
    return m_capacity;
}

/**
 * @brief:��ӡ�����Ĵ�С�������Լ�����
 * @param:��
 * @return:��
 * @author:SY
*/
template<class T>
void Vector<T>::print()
{
    //��ӡ������С�Լ�����
    std::cout<<"size: "<< m_size << " capacity: "<< m_capacity<<std::endl;
    //��ӡ�����е�����
    for(int i=0;i<m_size;i++)
    {
        std::cout<<m_data[i]<<" ";
    }
    std::cout<<std::endl;
}

/**
 * @brief:���·�����������
 * @param:���������
 * @return:��
 * @author:SY
*/
template <class T>
void Vector<T>::reserve(int n)
{
    if(m_capacity>=n)
    {
        return;
    }
    //���ݣ������ǵ�����С�ڴ����������С
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
    //��̬�ڴ���������
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
 * @brief:���·���������С
 * @param:����Ĵ�С
 * @return:��
 * @author:SY
*/
template <class T>
void Vector<T>::resize(int size)
{
    //�����ڲ���С���ڻ��������Ĵ�С
    if(m_size>=size)
    {
        m_size=size;
        return;
    }
    //�����ڲ���СС�������С���������СС����������
    if(m_size < size && size< m_capacity)
    {
        for(int i=m_size;i<size;i++)
        {
            m_data[i]=T();
        }
        m_size=size;
    }
    //�����С������������
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
    //��̬��������
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
 * @brief:��ȡ���������±��ֵ
 * @param:���������±�
 * @return:�������������±��ֵ
 * @author:SY
 * 
*/
template <class T>
T & Vector<T>::at(int index)
{
    //������Ҫ��������±꣬�׳��쳣
    if(index<0 || index>= m_size)
    {
        throw new std::logic_error("vec[] out of range");
    }
    return m_data[index];
}

/**
 * @brief:���������Ų���ȡ�����±�ֵ
 * @param:�����±�
 * @return:���������±��ֵ
 * @author:SY
*/
template <class T>
T & Vector<T>::operator [] (int index)
{
    return at(index);
}

/**
 * @brief:�ж������Ƿ�Ϊ��
 * @param:��
 * @return:�����������ݷ���true,���򷵻�false
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
 * @brief:�������������
 * @param:��
 * @return:��
 * @author:SY
*/
template <class T>
void Vector<T>::clear()
{
    m_size=0;
}

/**
 * @brief:��ȡ�����ĵ�һ��Ԫ�ص�ֵ
 * @param:��
 * @return:����������һ��Ԫ�ص�ֵ
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
 * @brief:��ȡ�������һ��Ԫ�ص�ֵ
 * @param:��
 * @return:�����������һ��Ԫ�ص�ֵ
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
 * @brief:�����������������ݡ���С�Լ�����
 * @param:��һ����������
 * @return:��
 * @author:SY
*/
template <class T>
void Vector<T>::swap(Vector<T> &other)
{
    //�洢����һ���������ʱ����
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
 * @brief:��ȡ������ָ��
 * @param:��
 * @return:����������ָ��
 * @author:SY
*/
template <class T>
T * Vector<T>::data()
{
    return m_data;
}

/**
 * @brief:���صȺţ����������������໥��ֵ
 * @param:��һ����������
 * @return:�����Ķ���
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

//��ʼ������
template <class T>
typename Vector<T>::Iterator Vector<T>::begin()
{
    Vector<T>::Iterator it(m_data);
    return it;
}
//����������
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
    //�ж������Ƿ�Ϊָ��
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
    //��ȡ����λ�õĵ�����
    auto pos=it-begin();
    //����Ԫ���㹻���(�������ݵ����)  
    if(m_size+n<=m_capacity)
    {
        if(is_basic_type())
        {
            //���ڲ��ڴ淢���ص�ʹ��memmove�������ڴ棬����ʹ��memcpy
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
    //����Ԫ�ع���,������������(����)
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
    //�ж�ɾ����Ԫ���Ƿ�Ϊ���һ��
    if(end() - it ==1)
    {
        m_size-=1;
        return end();
    }
    //ɾ������λ�õ�Ԫ��
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
    //��ȡ����Ԫ�صĵ�һ������
    int f=first - begin();
    //��ȡ����Ԫ�صĵڶ�������
    int l=last - begin();
    //���鳤�ȱ仯
    int pos = last - first;
    //�ж��Ƿ�Ϊ�������ͣ����ɾ������
    if(is_basic_type())
    {
        std::memmove(m_data+f,m_data+l,(m_size-l)*sizeof(T));
    }
    else
    {
        //Ԫ����ǰ�ƶ�
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