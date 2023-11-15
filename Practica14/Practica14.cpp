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
//   d.¿Qué pasa si llamo a un método virtual desde el constructor?
// 
//   Se llama el metodo adecuado de su propia clase si existe. Si no existe en la clase derivada
//   y solo existe en la clase base, pues se llama en la base (mirar clases A y B). Esto es porque
//   se crea la clase base primero, se llama el constructor, y el Print() de la clase C aún no existe.
// 

        Print();
    }

    virtual ~A()
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

    virtual ~B()
    {

    }

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
};


int main()
{

// a.¿Cuánto espacio ocupa la tabla de funciones virtuales ?
// 
//   Depurando con el puntero a puntero a funcion "vt", podemos ver que la tabla de funciones tiene
//   punteros a las funciones virtuales de su clase, por lo tanto, la tabla ocupa 4 o 8 multiplicado
//   por la cantidad de funciones virtuales. Luego dependiendo del compilador puede haber unos bytes
//   de padding.
// 

// c.¿Cuánto espacio ocupa adicionalmente un objeto por tener una tabla de funciones virtuales ?
// 
//   Ocupa 8 bytes de espacio en 64 bit, y 4 bytes en 32 bit, el tamaño de un puntero.
// 

    unsigned int sizeA = static_cast<int>(sizeof(A));
    unsigned int sizeB = static_cast<int>(sizeof(B));
    unsigned int sizeC = static_cast<int>(sizeof(C));
    printf("Size A: %u\n", sizeA);
    printf("Size B: %u\n", sizeB);
    printf("Size C: %u\n", sizeC);

    

// e.Comparar la llamada a una función virtual con la llamada a una función novirtual.
// ¿Cuántos pasos adicionales tienen que realizarse para llamar a una función cuando esta es virtual?
//
//  Funcion virtual:
//  - aPtr llama a Print() desde A
//     - Como Print() es virtual, llama a Print() en la vTable
//        - Desde la vTable se llama a la version derivada de Print(), lo cual es C::Print()
//            - Se ejecuta Print2()
// 
//  Funcion no virtual:
//  - aPtr llama a Print2() desde A
//     - Se ejecuta Print2()
//  
//  La diferencia es de 2 pasos, se usa el vfPtr para ir a la tabla de funciones virtuales, y luego
//  para llegar a la funcion de la clase derivada.
//
    C oC = C();
    A* aPtr = &oC;

    aPtr->Print2();
    aPtr->Print();

    void (**vt)() = *reinterpret_cast<void(***)()>(aPtr);
    
    int iterator = 0;

    while (*(vt + iterator) != NULL)
    {
        printf("Iterator: %d\n", iterator);
        iterator++;
    }
    unsigned int sizeVt = static_cast<int>(sizeof(*vt));
    printf("Size of table: %d\n", sizeVt);
}


// b.¿Dónde está situada la tabla de funciones virtuales ?
// 
//   La tabla de funciones virtuales están situadas en una parte de memoria read-only, ya que son estaticas para todas las instancias
//   de una clase. Para acceder a ellas, se debe usar el puntero añadido a los objetos de clases virtuales "__vfptr"
// 

