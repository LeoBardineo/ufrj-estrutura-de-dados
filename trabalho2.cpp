/**
 * Nome: Leonardo de Melo Soares
 * DRE: 120314414
 * Disciplina: Estrutura de Dados
 * Programa: Calcular uma expressão matemática com operadores + - * / utilizando pilha
 * */

#include <iostream>
#include <string>

using namespace std;

#define MAX 1000

class Pilha {
    public:
        int topo = -1;
        float pilha[MAX];

        Pilha();
        bool push(float x);
        float pop();
        float peek();
        bool isFull();
        bool isEmpty();
        void showPilha();
        bool isInPilha(char c);
        void pushNumeros(string entrada);
        void pushOperadores(string entrada);
        float resolver(Pilha num, Pilha operadores);
        Pilha revert();
};

Pilha::Pilha(){}

bool Pilha::isEmpty() { return topo < 0; }
bool Pilha::isFull() { return topo >= MAX - 1; }
bool Pilha::isInPilha(char c) {
    for (int i = 0; i < topo; i++) 
        if(pilha[i] == c) return true;
    return false;
}

bool Pilha::push(float x) {
    if (isFull()) return false;

    topo += 1;
    pilha[topo] = x;
    return true;
}

float Pilha::pop() {
    if (isEmpty()) return 0;

    float valor = pilha[topo];
    topo -= 1;
    return valor;
}

float Pilha::peek() {
    if (isEmpty()) return 0;

    return pilha[topo];
}

Pilha Pilha::revert(){
    Pilha pilha;
    while(!isEmpty()) pilha.push(pop());
    return pilha;
}

bool isOperador(char c){
    const string operadores = "+-*/";
    if(operadores.find(c) != string::npos) return true;
    return false;
}

// Percorre a expressão e coloca na pilha os operadores,
// com exceção dos que estão dentro de parenteses.
void Pilha::pushOperadores(string entrada){
    // Percorre a expressão
    for(int i = 0; i < entrada.length(); i++){
        // Pula o que estiver entre parênteses
        if(entrada[i] == '(')
            while(entrada[i] != ')') {
                i++;
            }
        // Se for um operador, coloca na pilha
        if(isOperador(entrada[i])) push(entrada[i]);
    }
};

float Pilha::resolver(Pilha num, Pilha operadores){
    num = num.revert();
    operadores = operadores.revert();

    int operador = 0;
    float resultado = 0, a = 0, b = 0;
    Pilha auxPilha, auxOp;

    while(num.isEmpty() == 0){
        if(num.topo == 0){
            auxPilha.push(num.pop());
            auxOp.push(operadores.pop());
        } else {
            a = num.pop();
            b = num.pop();
            operador = operadores.pop();

            if(operador == 0) operador = operadores.pop();

            if(operador == 42 || operador == 47){
                if(operador == '*') auxPilha.push(a * b);
                if(operador == '/') auxPilha.push(a / b);
                auxOp.push(operadores.pop());
            } else {
                auxPilha.push(a);
                if (num.topo == -1) {
                    auxPilha.push(b);
                } else {
                    num.push(b);
                }
                auxOp.push((char) operador);
            }
        }
    }

    auxPilha = auxPilha.revert();
    auxOp = auxOp.revert();

    if(auxOp.isInPilha('*') || auxOp.isInPilha('/')){
        auxPilha = auxPilha.revert();
        auxOp = auxOp.revert();
        return num.resolver(auxPilha, auxOp);
    }

    while(auxPilha.topo > 0){
        float a = auxPilha.pop();
        float b = auxPilha.pop();
        int operador = auxOp.pop();
        if(operador == '+') auxPilha.push(a + b);
        if(operador == '-') auxPilha.push(a - b);
        if(operador == '*') auxPilha.push(a * b);
        if(operador == '/') auxPilha.push(a / b);
    }

    return auxPilha.pop();
};

// Percore a expressão e se encontrar um parênteses,
// resolve a expressão dentro do parenteses primeiro,
// se não, adiciona na pilha os números
void Pilha::pushNumeros(string entrada){
    int arrOperadores[60], iOp = 0, inicioNumero = 0, comecoParenteses;
    float resultadoF;
    string expressao, resultadoS, str;

    // Percorre a expressão e ao encontrar um parênteses,
    // resolve a expressão de dentro do parênteses primeiro.
    for(int i = 0; i < entrada.length() + 1; i++){
        if(entrada[i] == ')'){
            // Acha o começo do parênteses
            comecoParenteses = i;
            while(entrada[comecoParenteses] != '('){
                 comecoParenteses--;
            }

            // Pega a expressao de dentro do parênteses
            expressao = entrada.substr(comecoParenteses + 1, i - comecoParenteses - 1);   

            Pilha expressaoNumero, expressaoOperador;
            expressaoNumero.pushNumeros(expressao);
            expressaoOperador.pushOperadores(expressao);

            // Pega o resultado e substitui na expressao original no lugar dos parênteses
            resultadoF = expressaoNumero.resolver(expressaoNumero, expressaoOperador);
            resultadoS = to_string(resultadoF);
            entrada.replace(comecoParenteses, i - comecoParenteses + 1, resultadoS);
            i += resultadoS.length();
        }
    }

    // Adiciona os operadores no array arrOperadores
    for(int i = 0; i < entrada.length(); i++){
        if(isOperador(entrada[i])){
            arrOperadores[iOp] = i;
            iOp++;
        }
    }

    if(entrada.find('(') != string::npos){
        return pushNumeros(entrada);
    }

    for(int i = 0; i <= iOp; i++){
        str = " ";
        if(arrOperadores[i] - inicioNumero > 1 || i == iOp){
            str = entrada.substr(inicioNumero, arrOperadores[i] - inicioNumero);
            push(stoi(str));
            inicioNumero = arrOperadores[i] + 1;
        }
    }

}

int main(void){
    // Entrada
    string entrada;
    cout << "Insira a expressão (com espaço entre os operadores): ";
    getline(cin, entrada);

    // Adicionando números na pilha
    Pilha num, operadores;
    num.pushNumeros(entrada);
    operadores.pushOperadores(entrada);

    // Saída
    cout << "Resultado = " << num.resolver(num, operadores) << endl;
    return 0;
}