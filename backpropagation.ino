// PARCIAL DE REDES NEURONALES
// Nombre: Iván Fernando Vargas Ochoa

// Para que solo se entrene una sola vez
int a = 1;

// Factor de aprendizaje
float n = 0.4;

// Valor de las entradas
int X1[4] = {0,0,1,1};
int X2[4] = {0,1,0,1};

// Valor de la salida
int Y[4] = {0,1,1,0};

void setup() {
  Serial.begin(9600);

}

void loop() {

  // Condición para que solo se entrene una vez
  if(a == 1){
    
  // Número de iteracciones
  int iteracciones = 0;
  
  // Inicialización aleatoria de los pesos
  float W[14] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1};

  for(int i=0; i<=13; i++){
    W[i] = random(4);
  }

  // Se declara el error global
  float errorglobal = 4;
  float error[4] = {1,1,1,1};

  int i = 0;

  while(errorglobal != 0){

    // Se encuentran las salidas de la primera capa
    float Y1 = (W[0]*X1[i]+W[1]*X2[i]);
    Y1 = tansig(Y1);
    float Y2 = (W[2]*X1[i]+W[3]*X2[i]);
    Y2 = tansig(Y2);
    float Y3 = (W[4]*X1[i]+W[5]*X2[i]);
    Y3 = tansig(Y3);

    // Se encuentran las salidas de la segunda capa
    float Y4 = (W[6]*Y1+W[7]*Y2+W[8]*Y3);
    Y4 = tansig(Y4);
    float Y5 = (W[9]*Y1+W[10]*Y2+W[11]*Y3);
    Y5 = tansig(Y5);

    // Se encuentran las salidas de la tercera capa
    float Y6 = (W[12]*Y4+W[13]*Y5);
    Y6 = tansig(Y6);

    // Calculamos el error
    error[i] = Y[i] - Y6;

    // Se sacan los gradientes locales de cada neurona
    float g4 = W[12]*error[i];
    float g5 = W[13]*error[i];

    float g1 = W[6]*g4 + W[9]*g5;
    float g2 = W[7]*g4 + W[10]*g5;
    float g3 = W[8]*g4 + W[11]*g5;

    // Se ajustan los pesos
    W[0] = W[0] + n*g1*((1-(pow(Y1,2))))*X1[i];
    W[1] = W[1] + n*g1*((1-(pow(Y1,2))))*X2[i];
    W[2] = W[2] + n*g2*((1-(pow(Y2,2))))*X1[i];
    W[3] = W[3] + n*g2*((1-(pow(Y2,2))))*X2[i];
    W[4] = W[4] + n*g3*((1-(pow(Y3,2))))*X1[i];
    W[5] = W[5] + n*g3*((1-(pow(Y3,2))))*X2[i];
    
    W[6] = W[6] + n*g4*((1-(pow(Y4,2))))*Y1;
    W[7] = W[7] + n*g4*((1-(pow(Y4,2))))*Y2;
    W[8] = W[8] + n*g4*((1-(pow(Y4,2))))*Y3;

    W[9] = W[9] + n*g5*((1-(pow(Y5,2))))*Y1;
    W[10] = W[10] + n*g5*((1-(pow(Y5,2))))*Y2;
    W[11] = W[11] + n*g5*((1-(pow(Y5,2))))*Y3;

    W[12] = W[12] + n*error[i]*((1-(pow(Y6,2))))*Y4;
    W[13] = W[13] + n*error[i]*((1-(pow(Y6,2))))*Y5;

    // Se calcula el error cuadratico medio
    error[i] = abs(error[i]);

    // Error global
    errorglobal = error[0] + error[1] + error[2] + error[3];

    // Error aceptable 
    if(errorglobal <= 0.09){
      Serial.print("Finish :");
      Serial.println(errorglobal);
      break;
    }

    // Iteracciones
    iteracciones = iteracciones + 1;

    if(i==4){
      i = 0;
    }

    // Se pasa al siguiente patrón
    i = i + 1;
    
    Serial.print("Iteracciones: ");
    Serial.println(iteracciones);
    Serial.print("Error global: ");
    Serial.println(errorglobal);
  }

  Serial.println("Entrenamiento terminado");

  // No se volvera a entrenar
  a = a +1 ;

  // Se comprueba el valor de salida de la red neuronal
  float salida[4] = {1,1,1,1};

  for(int i = 0; i<=3; i++){
    
    // Se encuentran las salidas de la primera capa
    float Y1 = (W[0]*X1[i]+W[1]*X2[i]);
    Y1 = tansig(Y1);
    float Y2 = (W[2]*X1[i]+W[3]*X2[i]);
    Y2 = tansig(Y2);
    float Y3 = (W[4]*X1[i]+W[5]*X2[i]);
    Y3 = tansig(Y3);

    // Se encuentran las salidas de la segunda capa
    float Y4 = (W[6]*Y1+W[7]*Y2+W[8]*Y3);
    Y4 = tansig(Y4);
    float Y5 = (W[9]*Y1+W[10]*Y2+W[11]*Y3);
    Y5 = tansig(Y5);

    // Se encuentran las salidas de la tercera capa
    float Y6 = (W[12]*Y4+W[13]*Y5);
    Y6 = tansig(Y6);

    // Calculamos el valor de salida de la red neuronal
    salida[i] = Y6;
  }

  Serial.println("El valor de la salida es: ");
  for(int i = 0; i<=3; i++){
    Serial.println(salida[i]);
  }

  }

}

// Función de activación tansig
float tansig(float n){
  
  float y = 2/(1 + (pow(2.7183,(-2*n)))) - 1;
  
  return y;
}

// Función de activación hardlim
float hardlim(float n){
  float y;

  if(n >= 0){
    y = 1;
  } else {
    y = 0;
  }

  return y;
}

// Función de activación logsig
float logsig(float n){
  float euler = 2.7183;
  
  float y = 1 /(1 + pow(euler,-n));
  
  return y;
}

// Función purelin
float purelin(float n){
  float y = n;

  return y;
}
