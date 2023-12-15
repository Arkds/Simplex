#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>

using namespace std;

void asignarValoresMatriz(vector<vector<double>>& matriz) {
    cout << "Ingresa el número de filas de la matriz: ";
    size_t filas;
    cin >> filas;
    cout << "Ingresa el número de columnas de la matriz: ";
    size_t columnas;
    cin >> columnas;
    matriz.resize(filas, vector<double>(columnas));
    cout << "Ingresa los valores de la matriz:" << endl;
    for (size_t i = 0; i < filas; ++i) {
        for (size_t j = 0; j < columnas; ++j) {
            cin >> matriz[i][j];
        }
    }
}
void imprimirMatriz(const vector<vector<double>>& matriz){
    for(size_t i= 0; i<matriz.size(); ++i){
        for(size_t j= 0; j<matriz[i].size(); ++j){
            cout<<fixed<<setprecision(2)<<setw(9)<<matriz[i][j]<<" ";
        }
        cout<<endl;
    }
}
double encontrarmasnegativo(const vector <vector<double>>& matriz){
    double columnaPivote = -1;
    double valorMenor = numeric_limits<double>::max();
    
    for(size_t j=0; j<matriz[0].size(); ++j){
        if(matriz[0][j] <valorMenor){
            valorMenor = matriz[0][j];
            columnaPivote = j;
        }
    }
    return columnaPivote;
}
double encontrarmenorcociente(const vector<vector<double>>& matriz, size_t columnaPivote) {
    double filaPivote = -1;
    double menorCociente = numeric_limits<double>::max();

    for (size_t i = 1; i < matriz.size(); ++i) {
        if (matriz[i][columnaPivote] > 0) {
            double cociente = matriz[i][matriz[i].size() - 1] / matriz[i][columnaPivote];
            if (cociente < menorCociente) {
                menorCociente = cociente;
                filaPivote = i;
            }
        }
    }
    return filaPivote;
}
double encontrarelemntopivote(const vector<vector<double>>& matriz, double filaPivote, double columnaPivote){
    double elementopivote = matriz [filaPivote][columnaPivote];
    return elementopivote;
}
void dividirFila(vector<vector<double>>& matriz, size_t fila, double columnaPivote) {
    double elementoPivote = matriz[fila][columnaPivote];
    for (size_t j = 0; j < matriz[fila].size(); ++j) {
        matriz[fila][j] /= elementoPivote;
    }
    imprimirMatriz(matriz);
    for (size_t i = 0; i < matriz.size(); ++i) {
        if (i != fila) {
            double factor = matriz[i][columnaPivote];
            for (size_t j = 0; j < matriz[i].size(); ++j) {
                matriz[i][j] -= factor * matriz[fila][j];
            }
        }
    }
    cout<<"Despues de dividir fila pivote: "<<endl;
    imprimirMatriz(matriz);
}
void anularElementosColumna(vector<vector<double>>& matriz, size_t filaPivote, size_t columnaPivote) {
    for (size_t i = 0; i < matriz.size(); ++i) {
        if (i != filaPivote) {
            double factor = matriz[i][columnaPivote];
            for (size_t j = 0; j < matriz[i].size(); ++j) {
                matriz[i][j] -= factor * matriz[filaPivote][j];
            }
        }
    }
}
bool verificarnegativosenfilacero(const vector<vector<double>>& matriz){
    for (size_t j=0; j<matriz[0].size(); ++j){
        if(matriz[0][j]<0){//-1e-10?
            return true;
        }
    }
    return false;
}
void algoritmosimplex(vector<vector<double>>& matriz){
    bool hayNegativos = true;
    while(hayNegativos){
        double columnaPivote = encontrarmasnegativo(matriz);
        double filaPivote = encontrarmenorcociente(matriz, columnaPivote);
        double elementopivote = encontrarelemntopivote(matriz, columnaPivote, filaPivote);
        cout<<"columnaPivote: "<<columnaPivote<<endl;
        cout<<"filaPivote: "<<filaPivote<<endl;
        cout<<"elementopivote: "<<elementopivote<<endl;
        
        dividirFila(matriz, filaPivote, columnaPivote);
        hayNegativos = verificarnegativosenfilacero(matriz);
    }
}
int main(){
    freopen("in.txt", "r", stdin);
    vector<vector<double>> matriz;
    asignarValoresMatriz(matriz);
    imprimirMatriz(matriz);
    algoritmosimplex(matriz);
}