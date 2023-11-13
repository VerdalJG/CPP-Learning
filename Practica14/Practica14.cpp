#include <iostream>

class A
{
public:
    A() 
    {
        Print();
    }

    ~A()
    {

    }

    virtual void Print()
    {
        printf("Implementation of Print A\n");
    }

    virtual void Print2()
    {
        printf("Implementation of Print2 A\n");
    }
};

class B : public A
{
public:
    B()
    {
        Print();
    }

    ~B()
    {

    }

    /*virtual void Print() override
    {
        printf("Implementation of Print B\n");
    }*/
};

class C : public B
{
public:
    C()
    {

// d.�Qu� pasa si llamo a un m�todo virtual desde el constructor ?
// 
//   Se llama el metodo adecuado de su propia clase si existe. Si no existe en la clase derivada
//   y solo existe en la clase base, pues se llama en la base (mirar clases A y B). Esto es porque
//   se crea la clase base primero, se llama el constructor, y el Print() de la clase C a�n no existe.
// 
        Print();
    }

    ~C()
    {

    }

    virtual void Print() override
    {
        printf("Implementation of Print C\n");
    }

    int i = 1;
    int* iPtr = &i;
};


int main()
{

// a.�Cu�nto espacio ocupa la tabla de funciones virtuales ?
// 
//   
// 

    unsigned int sizeA = static_cast<int>(sizeof(A));
    unsigned int sizeB = static_cast<int>(sizeof(B));
    unsigned int sizeC = static_cast<int>(sizeof(C));
    printf("Size A: %u\n", sizeA);
    printf("Size B: %u\n", sizeB);
    printf("Size C: %u\n", sizeC);

    C oC = C();
    A* cPtr = &oC;

    

    

    printf("C Pointer: %p\n", cPtr);
}


// b.�D�nde est� situada la tabla de funciones virtuales ?
// 
//   La 
// 
// c.�Cu�nto espacio ocupa adicionalmente un objeto por tener una tabla de funciones virtuales ?
// 
//   Ocupa 8 bytes de espacio en 64 bit, y 4 bytes en 32 bit, el tama�o de un puntero
// 
// e.Comparar la llamada a una funci�n virtual con la llamada a una funci�n novirtual.
// �Cu�ntos pasos adicionales tienen que realizarse para llamar a una funci�n cuando esta es virtual ?
//
//
//