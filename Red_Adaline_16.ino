/* RED NEURONAL ADALINE CON ENTRADA DE 16
 * 
 * NOMBRE: IVAN FERNANDO VARGAS OCHOA
 * C.C. : 1006558319
 */

// Valor para la ejecucion
  int a = 1;

// Tasa de aprendizaje
  float ta = 0.99;

// Se declara el valor de las entradas
  int x1[16] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
  int x2[16] = {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1};
  int x3[16] = {0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1};
  int x4[16] = {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1};

// Se declara el valor de la salida
  int Y[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

// Declaración de los pesos
  float w1 = random(4);
  float w2 = random(4);
  float w3 = random(4);
  float w4 = random(4);


void setup() {
  Serial.begin(9600);

  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
}

void loop() {

  // En esta parte se hace el entrenamiento de la red Neuronal
  if( a == 1){

  // Numero de iteracciones
  int contador = 0;

  // Se declara el error
  float errorglobal = 1;
  float error[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
  
  int i = 0;
  
  while(errorglobal != 0){
    
    float y = w1*x1[i]+ w2*x2[i]+ w3*x3[i] +w4*x4[i];

    error[i] = Y[i] - y;

    w1 = w1 + ta*error[i]*x1[i];
    w2 = w2 + ta*error[i]*x2[i];
    w3 = w3 + ta*error[i]*x3[i];
    w4 = w4 + ta*error[i]*x4[i];

    error[i] = abs(error[i]);

    i = i + 1;

    if(i==16){
      i = 0;
    }

    errorglobal = error[0] + error[1] + error[2] + error[3] + error[4] + error[5] + error[7] + error[8] + error[9] + error[10] + error[11] + error[12] + error[13] + error[14] + error[15];

    //Serial.println(contador);
    contador = contador + 1;
    
  }

  // Se comprueba el entrenamiento de la red Neuronal
  int salida[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  Serial.println("Valor de la salida: ");
  for(int i = 0; i<=15; i++){
    float C = w1*x1[i] + w2*x2[i] + w3*x3[i] + w4*x4[i];
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
  int x4 = digitalRead(6);

  float salida;

  Serial.println("Valor de la salida: ");

    float C = w1*x1 + w2*x2 + w3*x3 + w4*x4;
    salida = C;
    Serial.println(salida);
    delay(1000);
}
