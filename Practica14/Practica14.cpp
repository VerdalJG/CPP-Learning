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

//a.¿Cuánto espacio ocupa la tabla de funciones virtuales ?
// 
// 
// 
//b.¿Dónde está situada la tabla de funciones virtuales ?
// 
// 
// 
//c.¿Cuánto espacio ocupa adicionalmente un objeto por tener una tabla defunciones virtuales ?
// 
// 
// 
//d.¿Qué pasa si llamo a un método virtual desde el constructor ?
// 
// 
// 
//e.Comparar la llamada a una función virtual con la llamada a una función novirtual.
//¿Cuántos pasos adicionales tienen que realizarse para llamar a unafunción cuando esta es virtual ?
//
//
//