#include <iostream>

class A
{
public:

    virtual void Print()
    {
        printf("Implementation of Print A\n");
    }

    void Print2()
    {
        printf("Implementation of Print2 A\n");
    }

    virtual void Execute()
    {
        printf("Implementation of Execute A\n");
    }

    virtual void DoSomething()
    {
        printf("Implementation of DoSomething A\n");
    }

    A() 
    {
        Print();
    }

    ~A()
    {

    }
    int a;
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

    virtual void Execute() override
    {
        printf("Implementation of Execute B\n");
    }

    virtual void DoSomething() override
    {
        printf("Implementation of DoSomething B\n");
    }
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

    void Print() override
    {
        printf("Implementation of Print C\n");
    }

    void Execute() override
    {
        printf("Implementation of Execute C\n");
    }

    void DoSomething() override
    {
        printf("Implementation of DoSomething C\n");
    }

    int i = 1;
    //int* iPtr = &i;
};


int main()
{

// a.¿Cuánto espacio ocupa la tabla de funciones virtuales ?
// 
//   
// 

// c.¿Cuánto espacio ocupa adicionalmente un objeto por tener una tabla de funciones virtuales ?
// 
//   Ocupa 8 bytes de espacio en 64 bit, y 4 bytes en 32 bit, el tamaño de un puntero
// 

    unsigned int sizeA = static_cast<int>(sizeof(A));
    unsigned int sizeB = static_cast<int>(sizeof(B));
    unsigned int sizeC = static_cast<int>(sizeof(C));
    printf("Size A: %u\n", sizeA);
    printf("Size B: %u\n", sizeB);
    printf("Size C: %u\n", sizeC);

    C oC = C();
    A* cPtr = &oC;

// e.Comparar la llamada a una función virtual con la llamada a una función novirtual.
// ¿Cuántos pasos adicionales tienen que realizarse para llamar a una función cuando esta es virtual ?
//
//
    cPtr->Print();

    void (**vt)() = *reinterpret_cast<void(***)()>(cPtr);
    unsigned int sizeVt = static_cast<int>(sizeof(vt) / 4);
    printf("Size of table: %d", sizeVt);
}


// b.¿Dónde está situada la tabla de funciones virtuales ?
// 
//   La 
// 

