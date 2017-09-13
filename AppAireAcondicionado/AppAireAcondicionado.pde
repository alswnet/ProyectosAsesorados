boolean EstadoBoton = false;
int Temperatura = 17;
void setup() {
  size(400, 600);
  //fullScreen();
}

void draw() {
  background(0);
  if ( EstadoBoton ) {
    fill(0, 200, 0);
    ellipse(width/2, height/8, height/4-20, height/4-20);
    fill(0);
    textAlign(CENTER, CENTER);
    textSize(30);
    text("Encendido", width/2, height/8);
  } else {
    fill(200, 0, 0);
    ellipse(width/2, height/8, height/4-20, height/4-20);
    fill(0);
    textAlign(CENTER, CENTER);
    textSize(30);
    text("Apagado", width/2, height/8);
  }
  textSize(60);
  fill(0, 200, 0);
  text(Temperatura + "° C", width/2, (3*height)/4);
  triangle(width/2, height/4, , 75);
}
void mouseReleased() {
  float Distancia = dist(mouseX, mouseY, width/2, height/8);
  if (Distancia < (height/4-20)/2) {
    EstadoBoton = !EstadoBoton;
  }
}