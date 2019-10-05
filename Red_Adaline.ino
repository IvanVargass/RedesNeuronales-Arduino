/* RED NEURONAL ADALINE
 * 
 * NOMBRE: IVAN FERNANDO VARGAS OCHOA
 * C.C. : 1006558319
 */

// Valor para la ejecucion
  int a = 1;

// Tasa de aprendizaje
  float ta = 0.6;

// Se declara el valor de las entradas
  int x1[7] = {0,0,0,1,1,1,1};
  int x2[7] = {0,1,1,0,0,1,1};
  int x3[7] = {1,0,1,0,1,0,1};

// Se declara el valor de la salida
  int Y[7] = {1,2,3,4,5,6,7};

// Declaración de los pesos
  float w1 = random(1);
  float w2 = random(1);
  float w3 = random(1);


void setup() {
  Serial.begin(9600);

  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
}

void loop() {

  // En esta parte se hace el entrenamiento de la red Neuronal
  if( a == 1){

  // Numero de iteracciones
  int contador = 0;

  // Se declara el error
  float errorglobal = 1;
  float error[7] = {1,1,1,1,1,1,1};
  
  float y = 0;
  
  int i = 0;
  
  while(errorglobal != 0){
    
    y = w1*x1[i]+ w2*x2[i]+ w3*x3[i];

    error[i] = Y[i] - y;

    w1 = w1 + ta*error[i]*x1[i];
    w2 = w2 + ta*error[i]*x2[i];
    w3 = w3 + ta*error[i]*x3[i];

    error[i] = abs(error[i]);

    i = i + 1;

    if(i==7){
      i = 0;
    }

    errorglobal = error[0] + error[1] + error[2] + error[3] + error[4] + error[5] + error[6];

    contador = contador + 1;
  }

  // Se comprueba el entrenamiento de la red Neuronal
  int salida[7] = {0,0,0,0,0,0,0};

  Serial.println("Valor de la salida: ");
  for(int i = 0; i<=6; i++){
    float C = w1*x1[i] + w2*x2[i] + w3*x3[i];
    salida[i] = C;
    Serial.println(salida[i]);
  }
  Serial.println("Valor de los Pesos: ");
  Serial.println(w1);
  Serial.println(w2);
  Serial.println(w3);

  // Se finaliza el entrenamiento
  a = 2;
  }

  // Aqui comienza la comprobacion en tiempo real de la red neuronal
  int x1 = digitalRead(3);
  int x2 = digitalRead(4);
  int x3 = digitalRead(5);
  
  float salida;

  Serial.println("Valor de la salida: ");
  
    float C = w1*x1 + w2*x2 + w3*x3;
    salida = C;
    Serial.println(salida);
    delay(1000);
}
