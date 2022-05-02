#include <LiquidCrystal_I2C.h>
 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);

#define sinal A0
#define pinoRele 8
#define LedVermelho 5
#define LedAmarelo 6
#define LedVerde 7
 
int valor = A0;

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("Irriga UNIFEB");
  pinMode(sinal, INPUT);
  pinMode(LedVermelho, OUTPUT);
  pinMode(LedAmarelo, OUTPUT);
  pinMode(LedVerde, OUTPUT);
  pinMode(pinoRele, OUTPUT);
}

void loop() {
//Limpa a tela do LCD
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(5, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("AGRO_UNIFEB");
  delay(1200);
  lcd.setCursor(1, 1);
  lcd.print("MEDIDOR de UMIDADE");
  delay(2000);
  lcd.setCursor(5, 3);
  lcd.print("IRRIGA_AGRO");
  delay(2000);

  valor = analogRead(sinal);
  valor = constrain(valor, 592, 0);

Serial.println(valor);

  lcd.clear();
  lcd.setCursor(3, 1);
  lcd.print("Lendo Umidade");
  delay(300);
  lcd.setCursor(16, 1);
  lcd.print(".");
  delay(300);
  lcd.setCursor(16, 1);
  lcd.print("..");
  delay(300);
  lcd.setCursor(16, 1);
  lcd.print("...");
  delay(300);
  lcd.setCursor(10, 2);
  lcd.print(valor);
  lcd.setCursor(13, 2);
  lcd.print("%");
  delay(1500);

  if (valor < 65) {
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("Umidade Baixa");
    delay(500);
    lcd.setCursor(7, 2);
    lcd.print("REGAR");
    delay(300);
    lcd.setCursor(12, 2);
    lcd.print("!");
  } else   {
    lcd.clear();
    lcd.setCursor(4, 1);
    lcd.print("Umidade Boa");
    delay(500);
    lcd.setCursor(3, 2);
    lcd.print("PARAR DE REGAR");
    delay(300);
    lcd.setCursor(17, 2);
    lcd.print("!");
  }
  delay(2600);

  valor = analogRead(sinal);
  int Porcento = map(valor, 1020, 428, 0, 100);

  Serial.print("Porta analogica: ");
  Serial.print(valor);
  Serial.print(Porcento);
  Serial.println("%");

  if (Porcento >= 65) {
  Serial.println("Irrigando a planta ...");
  digitalWrite(pinoRele, HIGH);
  }
 
else {
  Serial.println(" Planta Irrigada ...");
  digitalWrite(pinoRele, LOW);
  }
 
  if (valor > 0 && valor < 428)
  {
    Serial.println(" Status: Solo umido");
    apagaleds();
    digitalWrite(LedVerde, HIGH);
  }
 
  if (valor > 500 && valor < 800)
  {
    Serial.println(" Status: Umidade moderada");
    apagaleds();
    digitalWrite(LedAmarelo, HIGH);
  }
 
  if (valor > 800 && valor < 1020)
  {
    Serial.println(" Status: Solo seco");
    apagaleds();
    digitalWrite(LedVermelho, HIGH);
    
  }
  delay(100);
}
 
void apagaleds()
{
  digitalWrite(LedVermelho, LOW);
  digitalWrite(LedAmarelo, LOW);
  digitalWrite(LedVerde, LOW);
}
