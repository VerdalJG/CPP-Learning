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

// d.¿Qué pasa si llamo a un método virtual desde el constructor ?
// 
//   Se llama el metodo adecuado de su propia clase si existe. Si no existe en la clase derivada
//   y solo existe en la clase base, pues se llama en la base (mirar clases A y B). Esto es porque
//   se crea la clase base primero, se llama el constructor, y el Print() de la clase C aún no existe.
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

// a.¿Cuánto espacio ocupa la tabla de funciones virtuales ?
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


// b.¿Dónde está situada la tabla de funciones virtuales ?
// 
//   La 
// 
// c.¿Cuánto espacio ocupa adicionalmente un objeto por tener una tabla de funciones virtuales ?
// 
//   Ocupa 8 bytes de espacio en 64 bit, y 4 bytes en 32 bit, el tamaño de un puntero
// 
// e.Comparar la llamada a una función virtual con la llamada a una función novirtual.
// ¿Cuántos pasos adicionales tienen que realizarse para llamar a una función cuando esta es virtual ?
//
//
//