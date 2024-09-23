

#ifndef ConexionesComputadora_hpp
#define ConexionesComputadora_hpp

#include <iostream>
using namespace std;
#include "Registro.hpp"
#include "Stack.hpp"
#include "BST.hpp"
#include "BSTConexiones.hpp"
#include "BinaryTree.hpp"
#include "TreeNode.hpp"
//#include "LecturaCSV.hpp"
#include <map>
#include <set>
#include <queue>


//std::vector<Registro> registros = leerArchivoCSV("equipo2.csv");

template <class T>
class ConexionesComputadora
{
private:
    string ip = "";
    string nombre = "";
    Stack<T> *conexionesEntrantes = new Stack<T>();
    LinkedList<T> *conexionesSalientes = new LinkedList<T>();

public:
    /* Constructores */
    ConexionesComputadora() = default;
    ConexionesComputadora(string _ip, string _nombre) : ip(_ip), nombre(_nombre){};

    /* Getters */
    Stack<T> *getConexionesEntrantes();
    LinkedList<T> *getConexionesSalientes();

/*
    Stack<T>* getConexionesEntrantes2() const;
    LinkedList<T>* getConexionesSalientes2() const;
*/

    void llenarConexiones(std::vector<T>);
    int totalConexionesEntrantes();
    int totalConexionesSalientes();
    T ultimaConexionEntrante();
    void tresConexionesConsecutivas(LinkedList<T>*);
    std::map<std::string, int> conexionesPorDia(const std::vector<T>& registros, const std::string& fecha);
    void top(int n, const std::string& fecha, std::vector<T>& registros);
    std::vector<std::string> top5diario(int n, std::vector<std::string>& fechas, std::vector<T>& registros);
    std::vector<int> totalConexionesDiario(int n, std::vector<std::string>& fechas, std::vector<T>& registros);

    void llenarConexiones2(std::vector<T>);

    friend std::ostream &operator<<(std::ostream &os, const ConexionesComputadora &computadora)
    {
        os << "Nombre: " << computadora.nombre;


        // ... (other code)

        return os;
    }
/*
        friend std::ostream &operator<<(std::ostream &os, const ConexionesComputadora &computadora)
    {
        os << "Nombre: " << computadora.nombre;

        computadora.llenarConexiones2(registros);
        LinkedList<Registro> *conexionesSalientes2 = computadora.getConexionesSalientes2();
        Stack<Registro> *conexionesEntrantes2 = computadora.getConexionesEntrantes2();

        int sizeSalientes = conexionesSalientes2->size();
        int sizeEntrantes = conexionesEntrantes2->size();

        os << "Conexiones salientes: " << sizeSalientes;
        os << "Conexiones entrantes: " << sizeEntrantes;

        // ... (other code)

        return os;
    }
*/



};

template <class T>
void ConexionesComputadora<T>::llenarConexiones(std::vector<T> registros)
{
    cout << "Llenando conexiones para IP: " << ip << endl;
    cout << "Total de registros a procesar: " << registros.size() << endl;

    Registro ultimo_registro;
    string eos;
  
    for (auto registro : registros)
    {

        if (registro.getIPorigen2() == ip)
        {
            conexionesSalientes->insert_back(registro);
            ultimo_registro = registro;
            eos = "Saliente";
        }
        else if (registro.getIPdestino() == ip)
        {
            conexionesEntrantes->push(registro);
            ultimo_registro = registro;
            cout << "Entrante: " << registro << endl;
            eos = "Entrante";
        }
      

      
    }
  cout << "Se han llenado con éxito las conexiones para la dirección IP " << ip << endl;
  cout << " " << endl;
  cout << "Última conexión: " << ultimo_registro << endl;
  cout << "Tipo de conexión: " << eos << endl;
  
}

template <class T>
void ConexionesComputadora<T>::llenarConexiones2(std::vector<T> registros)
{
    for (const auto& registro : registros)
    {
        if (registro.getIPorigen2() == ip)
        {
            conexionesSalientes->insert_back(registro);
        }
        else if (registro.getIPdestino() == ip)
        {
            conexionesEntrantes->push(registro);
        }
    }
}



template <class T>
Stack<T> *ConexionesComputadora<T>::getConexionesEntrantes() {
    return conexionesEntrantes;
}

template <class T>
LinkedList<T> *ConexionesComputadora<T>::getConexionesSalientes() {
    return conexionesSalientes;
}
/*
template <class T>
Stack<T> *ConexionesComputadora<T>::getConexionesEntrantes2 const() {
    return conexionesEntrantes;
}

template <class T>
LinkedList<T> *ConexionesComputadora<T>::getConexionesSalientes2 const() {
    return conexionesSalientes;
}
*/


template <class T>
int ConexionesComputadora<T>::totalConexionesEntrantes()
{
    return conexionesEntrantes->size();
}

template <class T>
int ConexionesComputadora<T>::totalConexionesSalientes()
{
    return conexionesSalientes->size();
}

template <class T>
T ConexionesComputadora<T>::ultimaConexionEntrante()
{
    return conexionesEntrantes->top();
}


#include "LinkedList.hpp"

template <class T>
void ConexionesComputadora<T>::tresConexionesConsecutivas(LinkedList<T> * registros)
{
    std::string a = "80";
    std::string b = "443";
    int x = 0;

    for (int i = 0; i < registros->size() - 2; ++i)
    {
        if ((registros->at(i)->getInfo().getIPdestino() == ip) && 
           ((registros->at(i)->getInfo().getPuertoDestino() == a) || (registros->at(i)->getInfo().getPuertoDestino() == b)))
        {
            if ((registros->at(i + 1)->getInfo().getIPdestino() == ip) && 
                ((registros->at(i + 1)->getInfo().getPuertoDestino() == a) || (registros->at(i + 1)->getInfo().getPuertoDestino() == b)) &&
                (registros->at(i + 2)->getInfo().getIPdestino() == ip) && 
                ((registros->at(i + 2)->getInfo().getPuertoDestino() == a) || (registros->at(i + 2)->getInfo().getPuertoDestino() == b)))
            {
                std::cout << "Hubieron 3 conexiones consecutivas del registro: " << *(registros->at(i)) << std::endl;
                x = 1;
                break;
            }
        }
    }

    if (x == 0)
    {
        std::cout << "No hubieron más de tres conexiones consecutivas con un sitio web." << std::endl;
    }
}

/*
template <class T>
std::map<std::string, int> ConexionesComputadora<T>::conexionesPorDia(const std::vector<T>& registros, const std::string& fecha) {
    std::map<std::string, int> conexionesPorSitio;

    for (const auto& registro : registros) {
        if (registro.getFecha() == fecha &&
            registro.getNombreDestino2() != "-" &&
            registro.getNombreDestino2() != "reto.com") {
            // Incrementar el conteo de conexiones entrantes por sitio
            conexionesPorSitio[registro.getNombreDestino()]++;
        }
    }

    return conexionesPorSitio;
}
*/

template <class T>
std::map<std::string, int> ConexionesComputadora<T>::conexionesPorDia(const std::vector<T>& registros, const std::string& fecha) {
    std::map<std::string, int> conexionesPorSitio;

    for (const auto& registro : registros) {
        if (registro.getFecha() == fecha &&
            registro.getNombreDestino2() != "-" &&
            registro.getNombreDestino2().find("reto.com") == std::string::npos) {
            // Incrementar el conteo de conexiones entrantes por sitio
            conexionesPorSitio[registro.getNombreDestino()]++;
        }
    }

    return conexionesPorSitio;
}




template <class T>
void ConexionesComputadora<T>::top(int n, const std::string& fecha, std::vector<T>& registros) {
    auto conexiones = conexionesPorDia(registros, fecha);

BSTConexiones<std::string, int> * sitiosBST = new BSTConexiones<std::string, int>();

    // Insertar elementos del map en el BST
    for (auto& par : conexiones) {
        sitiosBST->insertValue(par);
    }

    // Imprimir los top n elementos
    sitiosBST->printTopN(n);

  
}


template <class T>
std::vector<std::string> ConexionesComputadora<T>::top5diario(int n, std::vector<std::string>& fechas, std::vector<T>& registros) {
  
    std::vector<std::string> top5D;

    for (const auto &fecha : fechas) {
        BSTConexiones<std::string, int> * sitiosBST = new BSTConexiones<std::string, int>();
        auto conexiones = conexionesPorDia(registros, fecha);

        for (auto& par : conexiones) {
            sitiosBST -> insertValue(par);
        }

        sitiosBST->fillTopN(n);
        std::vector<std::string> vec = sitiosBST -> getTop5diario();
        for (const auto &element : vec) {
            //std::cout << element << std::endl;
            top5D.push_back(element);
        }

        delete sitiosBST; // Limpia el árbol para la próxima fecha
    }

    return top5D;
}

template <class T>
std::vector<int> ConexionesComputadora<T>::totalConexionesDiario(int n, std::vector<std::string>& fechas, std::vector<T>& registros) {

    std::vector<int> top5D;

    for (const auto &fecha : fechas) {
        BSTConexiones<std::string, int> * sitiosBST = new BSTConexiones<std::string, int>();
        auto conexiones = conexionesPorDia(registros, fecha);

        for (auto& par : conexiones) {
            sitiosBST -> insertValue(par);
        }

        sitiosBST->fillTotalD(n);
        std::vector<int> vec = sitiosBST -> getTotalConexionesDiario();
        for (const auto &element : vec) {
            //std::cout << element << std::endl;
            top5D.push_back(element);
        }

        delete sitiosBST; // Limpia el árbol para la próxima fecha
    }

    return top5D;
}





#endif