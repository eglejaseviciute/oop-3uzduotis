/**
 * @file myLib.h
 * @brief Pagrindinių bibliotekų ir naudingų funkcijų antraštės failas
 * 
 * Šis failas apima įvairias standartines C++ bibliotekas ir apibrėžia dažniausiai naudojamus
 * duomenų tipus, funkcijas ir makrokomandas. Jis taip pat apima svarbiausias funkcijas,
 * kuriomis gali naudotis kita programos dalis.
 * 
 */

#ifndef MYLIB_H
#define MYLIB_H


#include <iostream> ///< Įtraukia funkcijas ir tipus įvesties ir išvesties operacijoms
#include <vector>   ///< Įtraukia standartinį konteinerį 'vector'
#include <string>   ///< Įtraukia string tipą ir su juo susijusias funkcijas
#include <limits>   ///< Įtraukia standartinius limitus, pvz., 'numeric_limits'
#include <iomanip>  ///< Įtraukia funkcijas, susijusias su įvesties/rašymo formatu
#include <algorithm>///< Įtraukia algoritmus, tokius kaip 'sort', 'find' ir kt.
#include <cstdlib>  ///< Įtraukia funkcijas, susijusias su atsitiktiniais skaičiais ir procesų valdymu
#include <fstream>  ///< Įtraukia įvesties/išvesties funkcijas su failais
#include <sstream>  ///< Įtraukia stringstream funkcijas
#include <cctype>   ///< Įtraukia funkcijas simbolių apdorojimui
#include <chrono>   ///< Įtraukia laiką susijusias funkcijas
#include <functional>///< Įtraukia funkcijų objektus ir lambda funkcijas
#include <map>      ///< Įtraukia žemėlapių konteinerį (key-value poros)
#include <stdexcept>///< Įtraukia standartines išimtis
#include <numeric>  ///< Įtraukia funkcijas, susijusias su skaičiavimais, pvz., 'accumulate'


using std::endl;
using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::numeric_limits;
using std::streamsize;
using std::left;
using std::right;
using std::setw;
using std::setprecision;
using std::fixed;
using std::getline;
using std::map;
using std::stoi;
using std::invalid_argument;
using std::out_of_range;
using std::ifstream;
using std::runtime_error;
using std::stringstream;
using std::to_string;
using std::ofstream;
using std::exception;
using std::partition;
using std::pair;
using std::make_pair;
using std::move;
using std::ostream;
using std::istream;
using std::ios;
using std::cerr;


#endif // MYLIB_H
