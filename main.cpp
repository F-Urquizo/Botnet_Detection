#include "ConexionesComputadora.hpp"
#include "LecturaCSV.hpp"
#include "MergeSort.hpp"
#include "Registro.hpp"
#include "Graph.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <map>
#include <string>
#include <stack>

template <class T>
std::map<std::string, std::string> mapDominioIp(const std::vector<T>& registros) {
    std::map<std::string, std::string> mapDominioIp;

    for (const auto& registro : registros) {
        if (registro.getNombreDestino2().find("reto.com") == std::string::npos) {
            if (mapDominioIp.find(registro.getNombreDestino2()) == mapDominioIp.end() && registro.getNombreDestino2() != "-") {
                mapDominioIp[registro.getNombreDestino2()] = registro.getIPdestino();
            }
        }

        if (registro.getNombreOrigen2().find("reto.com") == std::string::npos) {
            if (mapDominioIp.find(registro.getNombreOrigen2()) == mapDominioIp.end() && registro.getNombreOrigen2() != "-") {
                mapDominioIp[registro.getNombreOrigen2()] = registro.getIPorigen2();
            }
        }
    }

    return mapDominioIp;
}

/*
template<class T>
std::map<std::string, ConexionesComputadora<T>> mapIPCC(const std::vector<T>& registros) {
    std::map<std::string, ConexionesComputadora<T>> mapIPCC;

    for (const auto& registro : registros) {
        if (mapIPCC.find(registro.getIPdestino()) == mapIPCC.end()) {
            ConexionesComputadora<T> computadoraD(registro.getIPdestino(), registro.getIPdestino());
            mapIPCC[registro.getIPdestino()] = computadoraD;
        }

        if (mapIPCC.find(registro.getIPorigen2()) == mapIPCC.end()) {
            ConexionesComputadora<T> computadoraO(registro.getIPorigen2(), registro.getIPorigen2());
            mapIPCC[registro.getIPorigen2()] = computadoraO;
        }
    }

    return mapIPCC;
}
*/

template<class T>
std::map<std::string, ConexionesComputadora<T>> mapIPCC(const std::vector<T>& registros) {
    std::map<std::string, ConexionesComputadora<T>> mapIPCC;

    for (const auto& registro : registros) {
        std::string ipDestino = registro.getIPdestino();
        std::string ipOrigen = registro.getIPorigen2();

        // Verifica y crea la instancia para la IP de destino
        auto itDestino = mapIPCC.find(ipDestino);
        if (itDestino == mapIPCC.end() && ipDestino != "-") {
            ConexionesComputadora<T> computadoraD(ipDestino, "NombreDestino");
            itDestino = mapIPCC.emplace(ipDestino, std::move(computadoraD)).first;
        }

        // Verifica y crea la instancia para la IP de origen
        auto itOrigen = mapIPCC.find(ipOrigen);
        if (itOrigen == mapIPCC.end() && ipOrigen != "-") {
            ConexionesComputadora<T> computadoraO(ipOrigen, "NombreOrigen");
            itOrigen = mapIPCC.emplace(ipOrigen, std::move(computadoraO)).first;
        }
    }

    // Llenar todas las conexiones después de crear las instancias
    for (auto& pair : mapIPCC) {
        pair.second.llenarConexiones2(registros);
    }

    return mapIPCC;
}








template <class T, class K>
void GrafoSalientes(std::vector<K>& fechas, std::string verticeBusqueda, Graph<T,K> * grafo){

  auto verticeBuscado = grafo->search(verticeBusqueda);
    if (verticeBuscado == nullptr){
        std::cout << "No se encontró el vertice" << std::endl;
    }
    else{

    auto vectorEdges = verticeBuscado->getEdges();
    
    std::map<std::string, int> edgesFechas;

    for (auto fecha : fechas){
      for (auto edge : *vectorEdges){
        if (edge->getInfo() == fecha){
          edgesFechas[fecha]++;
         }
       }
     }

     std:: cout << "Conexiones salientes de " << verticeBusqueda << " por fecha: " << std::endl;
      for (auto edge : edgesFechas){
        std::cout << edge.first << ": " << edge.second << std::endl;
      }

    std::cout << "Conexiones salientes totales de " << verticeBusqueda << ": " << verticeBuscado->getConexionesSalientes() << std::endl;

   }
}

template <class T, class K>
void GrafoEntrantes(std::vector<K>& fechas, std::string verticeBusqueda, Graph<T,K> * grafo){

  auto verticeBuscado = grafo->search(verticeBusqueda);
    if (verticeBuscado == nullptr){
        std::cout << "El vértice no se encuentra" << std::endl;
    }
    else{

    auto vectorEdges = verticeBuscado->getEdgesEntrantes();
    
    std::map<std::string, int> edgesFechas;

    for (auto fecha : fechas){
      for (auto edge : *vectorEdges){
        if (edge->getInfo() == fecha){
          edgesFechas[fecha]++;
         }
       }
     }

     std:: cout << "Conexiones entrantes de " << verticeBusqueda << " por fecha: " << std::endl;
      for (auto edge : edgesFechas){
        std::cout << edge.first << ": " << edge.second << std::endl;
      }

    std::cout << "Total de conexiones entrantes de " << verticeBusqueda << ": " << verticeBuscado->getConexionesEntrantes() << std::endl;

   }
}

/* Creación de grafo por dia para IP */
/* Conexiones entre ip con red interna solamente*/
template <class T, class K>
void grafoRedI(std::vector<T>& registros, std::vector<K>& fechas, std::string redInterna, std::string ipVertice){

    /* Crear el grafo */
    Graph<std::string, std::string> * grafoIp = new Graph<std::string, std::string>();

    for (int i = 0; i < registros.size() ; i++){

        std::string IpOrigen = registros[i].getIPorigen2();
        /* Verifica si la conexión pertenece a la red interna */
        if (IpOrigen.find(redInterna) != std::string::npos){

            size_t last_dot = IpOrigen.find_last_of(".");
            std::string IpOrigenSub = IpOrigen.substr(last_dot);
            /* std::cout << "IpOrigenSub: " << IpOrigenSub << std::endl; */

            /* Agrega el Vertex al grafo con validación */
            Vertex<std::string, std::string> * verticeIpOrigen = new Vertex<std::string, std::string>(IpOrigenSub);
            
            /* Validar si el vertex ya existe */
            Vertex<std::string, std::string> * vOrigen = grafoIp->search(verticeIpOrigen);
            if (vOrigen == nullptr){
                vOrigen = verticeIpOrigen;
                grafoIp->addVertex(verticeIpOrigen);
            }
            
            
            /* Search busca si vertex existe o si esta en grafo ?*/

            std::string IpDestino = registros[i].getIPdestino();

            if (IpDestino.find(redInterna) != std::string::npos){
            size_t last_dot = IpDestino.find_last_of(".");
            std::string IpDestinoSub = IpDestino.substr(last_dot);
            /* std::cout << "IpDestinoSub: " << IpDestinoSub << std::endl; */

            Vertex<std::string, std::string> * verticeIpDestino = new Vertex<std::string, std::string>(IpDestinoSub);
                
                /* Validar si el vertex ya existe */
                Vertex<std::string, std::string> * vDestino = grafoIp->search(verticeIpDestino);
                if (vDestino == nullptr){
                    vDestino = verticeIpDestino;
                    grafoIp->addVertex(verticeIpDestino);
                }

            grafoIp->addEdge(vOrigen, vDestino, registros[i].getFecha());

            }
        }
    }

    /* std::cout << *grafoIp << std::endl; */
    GrafoSalientes(fechas, ipVertice, grafoIp);
    grafoIp->maxConexionesSalientes();
    GrafoEntrantes(fechas, ipVertice, grafoIp);
    
    delete grafoIp;
}

template <class T, class K>
void grafoSitiosW(std::vector<T>& registros, std::vector<K>& fechas, std::string sitioRaro, std::string sitioConMasconexiones){

  Graph<std::string, std::string> * grafoSitios = new Graph<std::string, std::string>();

  for (int i = 0; i < registros.size() ; i++){
    std::string sitioOrigen = registros[i].getNombreOrigen2();

    if (registros[i].getPuertoDestino() == "443" || registros[i].getPuertoDestino() == "80"){

      Vertex<std::string, std::string> * verticeSitioOrigen = new Vertex<std::string, std::string>(sitioOrigen);

      Vertex<std::string, std::string> * vOrigen = grafoSitios->search(verticeSitioOrigen);

      if (vOrigen == nullptr){
        vOrigen = verticeSitioOrigen;
        grafoSitios->addVertex(vOrigen);
      }

      std::string sitioDestino = registros[i].getNombreDestino2();

      Vertex<std::string, std::string> * verticeSitioDestino = new Vertex<std::string, std::string>(sitioDestino);

      Vertex<std::string, std::string> * vDestino = grafoSitios->search(verticeSitioDestino);

      if (vDestino == nullptr){
        vDestino = verticeSitioDestino;
        grafoSitios->addVertex(vDestino);
      }

      grafoSitios->addEdge(vOrigen, vDestino, registros[i].getFecha());

    }
  }

  //std::cout << * grafoSitios << std::endl;
  GrafoEntrantes(fechas, sitioRaro, grafoSitios);
  GrafoEntrantes(fechas, sitioConMasconexiones, grafoSitios);
  GrafoSalientes(fechas, sitioConMasconexiones, grafoSitios);

  delete grafoSitios;
}

/*
template <class T, class K>
std::vector<Edge<std::string, std::string>*> vectorFinal(std::vector<T>& registros, std::vector<K>& fechas, std::string sitioRaro, std::string sitioConMasConexiones, std::unordered_set<std::string>& ipsUnicas) {
    Graph<std::string, std::string>* grafoSitios = new Graph<std::string, std::string>();
    std::vector<Edge<std::string, std::string>*> resultadoEdges;

    for (int i = 0; i < registros.size(); i++) {
        std::string sitioOrigen = registros[i].getNombreOrigen2();
        std::string sitioDestino = registros[i].getNombreDestino2();

        if (registros[i].getPuertoDestino() == "443" || registros[i].getPuertoDestino() == "80") {
            Vertex<std::string, std::string>* verticeSitioOrigen = new Vertex<std::string, std::string>(sitioOrigen);
            Vertex<std::string, std::string>* vOrigen = grafoSitios->search(verticeSitioOrigen);

            if (vOrigen == nullptr) {
                vOrigen = verticeSitioOrigen;
                grafoSitios->addVertex(vOrigen);
            }

            Vertex<std::string, std::string>* verticeSitioDestino = new Vertex<std::string, std::string>(sitioDestino);
            Vertex<std::string, std::string>* vDestino = grafoSitios->search(verticeSitioDestino);

            if (vDestino == nullptr) {
                vDestino = verticeSitioDestino;
                grafoSitios->addVertex(vDestino);
            }

            // Agregar el edge al grafo
            grafoSitios->addEdge(vOrigen, vDestino, registros[i].getFecha());

            // Verificar si vOrigen es una IP única y vDestino es igual a sitioConMasConexiones
            if (ipsUnicas.count(sitioOrigen) > 0 && sitioDestino == sitioConMasConexiones) {
                resultadoEdges.push_back(new Edge<std::string, std::string>(vOrigen, vDestino, registros[i].getFecha()));
            }
        }
    }

    // Resto del código para manipular el grafo como antes
    GrafoEntrantes(fechas, sitioRaro, grafoSitios);
    GrafoEntrantes(fechas, sitioConMasConexiones, grafoSitios);
    GrafoSalientes(fechas, sitioConMasConexiones, grafoSitios);

    // No elimines el grafo aquí, devuélvelo
    return resultadoEdges;
}
*/

/*
std::unordered_map<std::string, std::vector<std::string>> obtenerFechasSitio(const std::vector<Registro>& registros, const std::unordered_set<std::string>& ipsUnicas, const std::string& sitio) {
    std::unordered_map<std::string, std::vector<std::string>> resultadoMapa;

    for (const auto& ipUnica : ipsUnicas) {
        for (const auto& registro : registros) {
            if (registro.getNombreOrigen2() == ipUnica && registro.getNombreDestino2() == sitio) {
                resultadoMapa[ipUnica].push_back(registro.getFecha());
            }
        }
    }

    return resultadoMapa;
}
*/

int obtenerDia(const std::string& fecha) {
    // Encuentra la posición del primer guion
    size_t posGuion = fecha.find('-');
    
    // Extrae la subcadena correspondiente al día
    std::string diaStr = fecha.substr(0, posGuion);
    
    // Convierte la subcadena a un entero
    int dia;
    std::istringstream(diaStr) >> dia;

    return dia;
}

int main() {

  std::vector<Registro> registros;
  size_t numeroEntradas;

  // Lectura del archivo
  { registros = leerArchivoCSV("equipo2.csv"); }

  /* Actividad 1.3 */

  // Ordenamiento del archivo
  { MergeSort::mergeSort(registros, 0, registros.size() - 1); }

  // Pregunta 1: Cantidad de registros en el archivo
  {
    numeroEntradas = registros.size();
    std::cout << "Número total de entradas en el vector registros: "
              << numeroEntradas << std::endl
              << std::endl;
  }
  // Pregunta 2: Localización del segundo día y conteo de los récords en el
  // mismo:
  {
    int pos_dos;
    for (size_t i = 0; i < numeroEntradas; ++i) {
      if (registros[i].getFecha() != registros[0].getFecha()) {
        pos_dos = i;
        std::cout
            << "Primera entrada del segundo día localizada en la posición " << i
            << " del vector de Registros" << std::endl;

        std::cout << "Fecha del segundo día: " << registros[i].getFecha()
                  << std::endl;

        break;
      }
    }

    int segundo = 0;
    for (size_t i = 0; i < numeroEntradas; ++i) {
      if (registros[i].getFecha() == registros[pos_dos].getFecha()) {
        segundo++;
      }
    }

    // Cantidad de récords del segundo día:

    std::cout << "Cantidad de récords del segundo día: " << segundo << std::endl
              << std::endl;
  }
  // Pregunta 3: Alguna computadora pertenece a Jeffrey, Betty, Katherine,
  // Scott, Benjamin, Samuel o Raymond?
  {
    std::vector<std::string> nombresBuscados = {
        "jeffrey",  "betty",  "katherine", "scott",
        "benjamin", "samuel", "raymond"};

    for (const auto &nombreBuscado : nombresBuscados) {
      bool nombreEncontrado = false;
      for (const auto &registro : registros) {
        if (registro.getNombreOrigen() == nombreBuscado) {
          nombreEncontrado = true;
          break;
        }
      }

      if (nombreEncontrado) {
        std::cout << "El nombre origen '" << nombreBuscado
                  << "' se encuentra en el archivo." << std::endl;
      } else {
        std::cout << "El nombre origen '" << nombreBuscado
                  << "' NO se encuentra en el archivo." << std::endl;
      }
    }
    std::cout << " " << std::endl;
  }
  // Pregunta 4: Localización de la dirección IP de la red interna
  {
    std::cout << "La dirección de red interna es: "
              << registros[3].IPredInterna(registros) << std::endl
              << std::endl;
  }
  // Pregunta 5: Búsqueda de computadora llamada "server.reto.com"
  {
    std::string serv = "server";
    bool nombreEncontrado = false;
    for (const auto &registro : registros) {
      if (registro.getNombreOrigen() == serv) {
        nombreEncontrado = true;
        break;
      }
    }

    if (nombreEncontrado) {
      std::cout << "El nombre origen '" << serv + ".reto.com"
                << "' se encuentra en el archivo." << std::endl
                << std::endl;
    } else {
      std::cout << "El nombre origen '" << serv + ".reto.com"
                << "' NO se encuentra en el archivo." << std::endl
                << std::endl;
    }
  }
  // Pregunta 6: Servicios de correo electrónico
  {

    std::unordered_set<std::string> nombreD;
    for (const auto &registro : registros) {
      const std::string &nDestino = registro.getNombreDestino2();
      if (nDestino != "-" && nDestino == "gmail.com" ||
          nDestino == "outlook.com" || nDestino == "mail.yahoo.com" ||
          nDestino == "hotmail.com" || nDestino == "protonmail.com") {
        nombreD.insert(nDestino);
      }
    }

    std::cout << "Los servicios de correo electrónico que se emplean son los "
                 "siguientes: "
              << std::endl;
    for (const auto &destino : nombreD) {
      std::cout << destino << std::endl;
    }
    std::cout << " " << std::endl;
  }
  // Pregunta 7: Puertos debajo de 1000 en uso
  {
    std::unordered_set<int> puertos;
    for (const auto &registro : registros) {
      if (registro.getPuertoDestino() != "-") {
        int puerto = std::stoi(registro.getPuertoDestino());
        if (puerto < 1000) {
          puertos.insert(puerto); // Insertion in an unordered_set is O(1)
        }
      }
    }

    std::cout << "Puertos destino por debajo de 1000 en uso:" << std::endl;
    for (const auto &puerto : puertos) {
      std::cout << puerto << std::endl;
    }
  }

  /* Actividad 2.2 */

  // Pregunta 1:

  std::cout << "Ingresa una dirección IP (del 1 al 150): ";
  std::string dir;
  std::cin >> dir;
  std::string ipoficial;
  std::string redinterna = registros[3].IPredInterna(registros);
  ipoficial = redinterna + "." + dir;
  std::cout << "IP: " << ipoficial << std::endl;
  std::cout << " " << std::endl;
  ConexionesComputadora<Registro> computadora(ipoficial, "MiNombre");
  //"198.220.57.81"

  // Pregunta 2

  computadora.llenarConexiones(registros);
  std::cout << " " << endl;

  std::cout << *computadora.getConexionesEntrantes()->top() << std::endl;

  // Preguntas 3 y 4
  int tce = computadora.totalConexionesEntrantes();
  int tcs = computadora.totalConexionesSalientes();
  std::cout << "Total de conexiones entrantes: " << tce << std::endl;
  std::cout << "Total de conexiones salientes: " << tcs << std::endl;
  std::cout << " " << std::endl;

  // Pregunta 5

  // computadora.tresConexionesConsecutivas(registros);

  LinkedList<Registro> *conexionesSalientes =
      computadora.getConexionesSalientes();

  computadora.tresConexionesConsecutivas(conexionesSalientes);



  /* Actividad 3.2 */


  // Parte 2
  std::vector<std::string> fechas;


    for (const auto &registro : registros) {
    std::string fecha = registro.getFecha();
    if (find(fechas.begin(), fechas.end(), fecha) == fechas.end()) {
      fechas.push_back(fecha);
    }
  }

  int n = 5; // Número de sitios principales que deseas mostrar


  std::cout << "" << std::endl;

  for (size_t i = 0; i < fechas.size(); ++i) {
    std::cout << n << " sitios con más conexiones para la fecha " << fechas[i]
              << ":" << std::endl;
    computadora.top(n, fechas[i], registros);
    std::cout << "" << std::endl;
  }

/* Contestación de las preguntas */
  
  std::vector<std::string> t5d = computadora.top5diario(n, fechas, registros);


  std::cout << " " << std::endl;


  /* Pregunta 1 */
  std::unordered_map<std::string, int> siteCount;

  for (const auto &site : t5d) {
      siteCount[site]++;
  }

  std::cout << "Sitios que aparecen todos los días: " << std::endl;
  for (const auto &pair : siteCount) {
    if (pair.second == 10)
      std::cout << pair.first << " aparece " << pair.second << " veces (todos los días)." << std::endl;
  }

std::cout << " " << std::endl;
    /* Pregunta 2 */


      std::vector<std::string> sitiosFinales;
      int i = 9;
      int j = 5;

      while (i > 0) {
          std::vector<std::string> sitiosActuales(t5d.begin() + j, t5d.begin() + j + 5);
          std::unordered_map<std::string, int> sitioConteo;

          for (const auto& sitio : t5d) {
              int conteo = 0;
              for (const auto& actual : sitiosActuales) {
                  if (actual == sitio) {
                      conteo++;
                  }
              }
              sitioConteo[sitio] = conteo;
          }

          for (const auto& sitio : t5d) {
              if (sitioConteo[sitio] == i) {
                  sitiosFinales.push_back(sitio);
              }
          }

          i--;
          j = j+5;
            t5d.erase(t5d.begin(), t5d.begin() + 5);
      }

      std::cout << "Sitios que entran a los 5 un día y permanecen ahí:" << std::endl;
      if (sitiosFinales.empty())
        std::cout << "No hay ningún sitio que cumpla con este criterio." << std::endl;
      else {
        for (const auto& sitio : sitiosFinales) {
            std::cout << sitio << std::endl;
        }
      }

  std::cout << "" << std::endl;

  /* Pregunta 3 */
  
  int suma = 0;
  std::vector<int> tCd = computadora.totalConexionesDiario(n, fechas, registros);
  int sizeTCD = tCd.size();
  for (const auto &element : tCd) {
    suma+=element;
  }

  float promedio = suma / sizeTCD;;

  int critero_comparacion = promedio * 1.5;

  int contador = 0;
  std::vector<int> match;
  for (const auto &element : tCd) {
    if (element > critero_comparacion)
    {
      match.push_back(contador);
    }
    contador++;
  }
  std::vector<std::string> t5d2 = computadora.top5diario(n, fechas, registros);




std::cout << " " << std::endl;

  std::cout << "Sitios con una cantidad más alta de trafico que lo normal: " << std::endl;

  std::vector<std::string> traficoAnormal;
  for (const auto &mat : match) {
      // Verificar si el elemento ya existe en traficoAnormal
      if (std::find(traficoAnormal.begin(), traficoAnormal.end(), t5d2[mat]) == traficoAnormal.end()) {
          // Si el elemento no existe, se agrega al vector traficoAnormal
          traficoAnormal.push_back(t5d2[mat]);
      }
  }

    

  for (const auto &traf : traficoAnormal)
    {
      std::cout << traf << std::endl;
    }


    /* Act 4.2 */

  /* Preguntas 1 y 2 */
  std::cout << std::endl;
  std::string octetoA = ".18";
  std::cout << "Dirección IP que se comunica con otras computadoras internas (A): " << redinterna << octetoA << std::endl;
  std::string redinterna2 = redinterna + ".";
  grafoRedI(registros, fechas, redinterna2, octetoA);

  std::cout << std::endl;

  /* Preguntas 3 y 4 */
  std::string sitioB = "86boe9v31ro4yi83dxsj.com";
  //std::string sitioB = "7rszfis6fls3zzwhnvm8.net";
  std::string sitioC = "homedepot.com"; /*verficar este sitio */
  std::cout << "Sitio web extraño (B): " << sitioB << std::endl;
  std::cout << "Sitio web con tráfico anómalo un día (C): " << sitioC << std::endl;
  grafoSitiosW(registros, fechas, sitioB, sitioC);
  
  std::cout << std::endl;


  /* Act 5.2 */

  /* Primer mapa */

  std::map<std::string, std::string> domainIpMap = mapDominioIp(registros);


  std::cout << "Mapa Dominio, IP: " << std::endl;
  for (const auto& pair : domainIpMap) {
      std::cout << "Dominio: " << pair.first << ", IP: " << pair.second << std::endl;
  }

  std::cout << std::endl;


  std::string sitioB2 = "7rszfis6fls3zzwhnvm8.net";

  std::string IPsitioraro1 = domainIpMap[sitioB];
  std::string IPsitioraro2 = domainIpMap[sitioB2];


  
  std::cout << "Sitio raro 1: 86boe9v31ro4yi83dxsj.com" << std::endl;
  std::cout << "Sitio raro 2: 7rszfis6fls3zzwhnvm8.net" << std::endl;
  std::cout << std::endl;

  std::cout << "IP sitio raro 1: " << IPsitioraro1 << std::endl;
  std::cout << "IP sitio raro 2: " << IPsitioraro2 << std::endl;



  std::cout << std::endl;


  /* Segundo mapa */

std::map<std::string, ConexionesComputadora<Registro>> domainIpMap2 = mapIPCC(registros);
  
  std::cout << "Mapa IP, ConexionesComputadora: " << std::endl;

  for (const auto& pair : domainIpMap2) {

      ConexionesComputadora<Registro> computadora = pair.second;
      std::cout << "IP: " << pair.first << ", Conexiones Entrantes: " << computadora.totalConexionesEntrantes() << ", Conexiones Salientes: " << computadora.totalConexionesSalientes() <<std::endl;
      //std::cout << std::endl;
  }
  std::cout << std::endl;


/* Pregunta 3 */
  std::vector<ConexionesComputadora<Registro>> almenosunaEv;
  int almenosunaEi = 0;
  for (const auto& pair : domainIpMap2) {

      ConexionesComputadora<Registro> computadora = pair.second;
      if (pair.first.find(redinterna) != std::string::npos && computadora.totalConexionesEntrantes() > 0)
      {
        almenosunaEv.push_back(pair.second);
        almenosunaEi++;
      }
  }

  std::cout << "Computadoras pertenecientes al dominio reto.com con al menos una conexión entrante: " << almenosunaEi << std::endl;

  
  std::cout << std::endl;


  /* Pregunta 4 */
/*
  std::vector<std::string> cincoIPs;


  int restante = 5;
  for (auto registro : registros)
  {
    if (restante > 0)
    {
      if ((registro.getPuertoDestino() != "68" && registro.getPuertoDestino() != "67") && registro.getIPdestino().find(redinterna) == std::string::npos)
      {
        
        cincoIPs.push_back(registro.getIPdestino());
        restante--;
      }
    }
    else
    {
      break;
    }
  }
  */
/*
std::vector<std::string> cincoIPs;
std::unordered_set<std::string> uniqueIPs;

*/

/*
    // Obtener algunas computadoras que no sean server.reto.com o el servidor DHCP (hasta 10)
    std::vector<std::string> computadorasSeleccionadas;
    size_t cantidadComputadorasSeleccionadas = 0;

    for (const auto& registro : registros) {
        std::string nombreDestino = registro.getNombreDestino2();

        // Verificar que no sea server.reto.com ni servidor DHCP
        if (nombreDestino != "server.reto.com" && registro.getPuertoDestino() != "67" && registro.getPuertoDestino() != "68") {
            // Añadir la computadora si no se ha seleccionado previamente
            if (std::find(computadorasSeleccionadas.begin(), computadorasSeleccionadas.end(), nombreDestino) == computadorasSeleccionadas.end()) {
                computadorasSeleccionadas.push_back(nombreOrigen);
                cantidadComputadorasSeleccionadas++;

                if (cantidadComputadorasSeleccionadas >= 10) {
                    break; // Obtener hasta 10 computadoras
                }
            }
        }
    }
  */

    std::vector<std::string> cincoIPs;
    std::unordered_set<std::string> uniqueIPs;

    int restante = 5;
    for (const auto& registro : registros)
    {
        if (restante > 0)
        {
            if ((registro.getPuertoDestino() != "68" && registro.getPuertoDestino() != "67") && (registro.getIPdestino().find(redinterna) != std::string::npos) && (registro.getNombreDestino2() != "server.reto.com"))
            {
                // Check if the IP is not already in uniqueIPs
                if (uniqueIPs.insert(registro.getIPdestino()).second)
                {
                    cincoIPs.push_back(registro.getIPdestino());
                    restante--;
                }
            }
        }
        else
        {
            break;
        }
    }

    // Imprimir las IPs únicas
    int cincosize = cincoIPs.size();

    //std::cout << cincosize << std::endl;

    std::cout << "IPs de 5 computadoras que no son server.reto.com y no pertenecen al servidor DHCP: " << std::endl;

    for (auto ip : cincoIPs)
    {
      std::cout << ip << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Se adiciona al vector la IP que se sabe que tiene una conexión con los sitios raros para demostrar la funcionalidad del código: " << std::endl;

    std::string IPvirus = "192.168.86.22";
    cincoIPs.push_back(IPvirus);

    for (auto ip : cincoIPs)
    {
      std::cout << ip << std::endl;
    }
    std::cout << std::endl;



    /* OBTENER IPs UNICAS ENTRANTES */

    std::unordered_set<std::string> ipsUnicasEntrantes;

    for (const auto& ip : cincoIPs) {
        ConexionesComputadora<Registro> conexionesComp(ip, "NombreDestino");
        conexionesComp.llenarConexiones2(registros);
        Stack<Registro>* conexionesEntrantes = conexionesComp.getConexionesEntrantes();

        //std::cout << "Conexiones entrantes para la IP " << ip << ":" << std::endl;

        while (!conexionesEntrantes->empty()) {
            Registro registro = conexionesEntrantes->top()->getInfo();
            //std::cout << "Fecha: " << registro.getFecha() << ", IP Origen: " << registro.getIPorigen2() << std::endl;

            ipsUnicasEntrantes.insert(registro.getIPorigen2());
            conexionesEntrantes->pop();
        }
    }

    // Imprimir las IPs únicas de las conexiones entrantes

    std::cout << "Cantidad de IPs únicas entrantes: " << ipsUnicasEntrantes.size() << std::endl;
    std::cout << "IPs únicas de conexiones entrantes:" << std::endl;


    for (const auto& ip : ipsUnicasEntrantes) {
        std::cout << ip << std::endl;
    }

    std::cout << std::endl;

    //std::cout << "hello" << std::endl;

/*
    // Obtener las IPs únicas de las conexiones entrantes
    std::unordered_set<std::string> ipsUnicasEntrantes;

    for (const auto& computadora : computadorasSeleccionadas) {
        ConexionesComputadora<Registro> conexionesComp(registros, computadora);
        std::stack<Registro>* conexionesEntrantes = conexionesComp.getConexionesEntrantes();

        while (!conexionesEntrantes->empty()) {
            ipsUnicasEntrantes.insert(conexionesEntrantes->top().getIPorigen2());
            conexionesEntrantes->pop();
        }
    }

    // Imprimir las IPs únicas de las conexiones entrantes
    std::cout << "IPs únicas de conexiones entrantes:" << std::endl;

    for (const auto& ip : ipsUnicasEntrantes) {
        std::cout << ip << std::endl;
    }


*/
/*
std::string sitioB = "86boe9v31ro4yi83dxsj.com";

for (const auto& ip : ipsUnicasEntrantes) {
    auto verticeIp = grafoSitios->search(ip);
    auto verticeSitioB = grafoSitios->search(sitioB);

    if (verticeIp != nullptr && verticeSitioB != nullptr) {
        if (grafoSitios->hayConexion(verticeIp, verticeSitioB)) {
            std::cout << "Hubo conexión entre la IP " << ip << " y el sitio " << sitioB << std::endl;
        }
    }
}
*/


  //std::vector<Edge<std::string, std::string>*> resultadoEdges = vectorFinal(registros, fechas, sitioB, sitioB2, ipsUnicasEntrantes);
/*
  std::unordered_map<std::string, std::vector<std::string>> fechasSitio = obtenerFechasSitio(registros, ipsUnicasEntrantes, sitioB2); 

      if (fechasSitio.empty()) {
        std::cout << "El mapa está vacío." << std::endl;
    } else {
        std::cout << "El mapa no está vacío." << std::endl;
    }
  
  for (const auto& entry : fechasSitio) {
      const std::string& ipUnica = entry.first;
      const std::vector<std::string>& fechas = entry.second;

      std::cout << "hola" << std::endl;

      std::cout << "IP única: " << ipUnica << std::endl;
      std::cout << "Fechas de conexión al sitio: ";
      for (const auto& fecha : fechas) {
          std::cout << fecha << " ";
      }
      std::cout << std::endl;
  }

  */

  std::vector<Registro> conIPSitioRaro1;
  std::vector<Registro> conIPSitioRaro2;

  for (auto ip : cincoIPs)
  {
    for (auto registro : registros) 
    {
      if (registro.getNombreOrigen2() == sitioB && registro.getIPdestino() == ip)
      {
        conIPSitioRaro1.push_back(registro);
      }

      if (registro.getNombreOrigen2() == sitioB2 && registro.getIPdestino() == ip)
      {
        conIPSitioRaro2.push_back(registro);
      }
    }
  }

  std::cout << "Conexiones entre IPs únicas y sitio raro 86boe9v31ro4yi83dxsj.com: " << std::endl;
  for (auto registro : conIPSitioRaro1)
  {
    std::cout << registro << std::endl;
  }

  std::cout << std::endl;

  std::cout << "Conexiones entre IPs únicas y sitio raro 7rszfis6fls3zzwhnvm8.net: " << std::endl;
  for (auto registro : conIPSitioRaro2)
  {
    std::cout << registro << std::endl;
  }

  std::cout << std::endl;
/*
  std::string fecha = "17-8-2020";

  int dia = obtenerDia(fecha);
    
  std::cout << "Día: " << dia << std::endl;
*/

int maxfecha1 = 100;
std::string puertoProtocolo1;
for (auto registro : conIPSitioRaro1)
{
  std::string fechaS = registro.getFecha();
  int fechaI = obtenerDia(fechaS);
  if (fechaI < maxfecha1)
  {
    maxfecha1 = fechaI;
    puertoProtocolo1 = registro.getPuertoDestino();
  }
}

int maxfecha2 = 100;
std::string puertoProtocolo2;
for (auto registro : conIPSitioRaro2)
{
  std::string fechaS = registro.getFecha();
  int fechaI = obtenerDia(fechaS);
  if (fechaI < maxfecha2)
  {
    maxfecha2 = fechaI;
    puertoProtocolo2 = registro.getPuertoDestino();
  }
}

if (maxfecha1 < 100)
{
  std::cout << "La primera fecha en la que hubo una conexión entre una de las 5 IPs y el sitio " << sitioB << "fue: " << maxfecha1 << "-8-2020" << std::endl << "por el puerto " << puertoProtocolo1 << std::endl;
}
else
{
  std::cout << "No hubo una conexión entre una de las 5 IPs y el sitio " << sitioB << std::endl;
}
std::cout << std::endl;

if (maxfecha2 < 100)
{
std::cout << "La primera fecha en la que hubo una conexión entre una ip única y el sitio " << sitioB2 << "fue: " << maxfecha2 << "-8-2020" << std::endl << "por el puerto " << puertoProtocolo1 << std::endl;
}
else
{
  std::cout << "No hubo una conexión entre una de las 5 IPs y el sitio " << sitioB2 << std::endl;
}

std::cout << std::endl;


  return 0;
}


