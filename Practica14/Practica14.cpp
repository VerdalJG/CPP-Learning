#include <iostream>

class A
{
    /*virtual void Print()
    {
        printf("Implementation of Print A");
    }

    virtual void Print2()
    {
        printf("Implementation of Print2 A");
    }*/
    
    virtual void Print3()
    {
        printf("Implementation of Print3 A");
    }
//private:
//    int bomba = 222;
};

class B : public A
{
    /*virtual void Print()
    {
        printf("Implementation of Print B");
    }
public:
    int bomba2;*/
};

class C : public B
{
    /*virtual void Print()
    {
        printf("Implementation of Print C");
    }
    int bomba3;*/
};


int main()
{
    unsigned int sizeA = static_cast<int>(sizeof(A));
    unsigned int sizeB = static_cast<int>(sizeof(B));
    unsigned int sizeC = static_cast<int>(sizeof(C));
    printf("Size A: %u\n", sizeA);
    printf("Size B: %u\n", sizeB);
    printf("Size C: %u\n", sizeC);
}

//a.�Cu�nto espacio ocupa la tabla de funciones virtuales ?
// 
// 
// 
//b.�D�nde est� situada la tabla de funciones virtuales ?
// 
// 
// 
//c.�Cu�nto espacio ocupa adicionalmente un objeto por tener una tabla defunciones virtuales ?
// 
// 
// 
//d.�Qu� pasa si llamo a un m�todo virtual desde el constructor ?
// 
// 
// 
//e.Comparar la llamada a una funci�n virtual con la llamada a una funci�n novirtual.
//�Cu�ntos pasos adicionales tienen que realizarse para llamar a unafunci�n cuando esta es virtual ?
//
//
//