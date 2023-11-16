#include <iostream>

class CStream
{
public:
    virtual bool Open() { return false; };
    virtual bool Close() { return false; };
    virtual unsigned int Read() { return 1; };
    virtual unsigned int Write() { return 1; };

    void* stream = nullptr;
};

class CFile : public CStream
{
    bool Open() override
    {
        printf("CFile Open!\n");
        return true;
    }


    bool Close() override
    {
        printf("CFile Close!\n");
        return true;
    }


    unsigned int Read() override
    {
        printf("CFile Read!\n");
        return 0;
    }


    unsigned int Write() override
    {
        printf("CFile Write!\n");
        return 0;
    }

};

class CCom : public CStream
{
    bool Open() override
    {
        printf("CCom Open!\n");
        return true;
    }


    bool Close() override
    {
        printf("CCom Close!\n");
        return true;
    }


    unsigned int Read() override
    {
        printf("CCom Read!\n");
        return 0;
    }


    unsigned int Write() override
    {
        printf("CCom Write!\n");
        return 0;
    }
};

class CTCP : public CStream
{
    bool Open() override
    {
        printf("CTCP Open!\n");
        return true;
    }


    bool Close() override
    {
        printf("CTCP Close!\n");
        return true;
    }


    unsigned int Read() override
    {
        printf("CTCP Read!\n");
        return 0;
    }


    unsigned int Write() override
    {
        printf("CTCP Write!\n");
        return 0;
    }
};

int main()
{
    CFile file = CFile();
    CStream* filePtr = &file;
    filePtr->Open();

    CCom com = CCom();
    CStream* comPtr = &com;
    comPtr->Close();

    CTCP tcp = CTCP();
    CStream* tcpPtr = &tcp;
    tcpPtr->Write();
}

// a.Diseñar e implementar(simuladamente) el esqueleto de un sistema jerárquico con funciones virtuales
// que gestione la apertura, cierre, lectura y escritura de streams.
// 
// b.Los streams que deberá contemplar son : i.Ficheros. ii.Puerto serie. iii.Conexión TC
// 
// c.Habrá una clase base CStream y las clases derivadas CFile, CCom, CTcp.
