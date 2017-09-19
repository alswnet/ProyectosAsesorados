float A  = width;
float H  = height;
float VX = 0;
float VY = 0;

void setup() {
  //size(400, 600);
  fullScreen();
  A = width;
  H = height;
  textSize(60);
}

void draw() {
  background(100);
  fill(0, 100, 0);
  rect(A/2, 0, 10, H);
  rect(0, H/2, A, 10);
  fill(200);
  ellipse(mouseX, mouseY, 100, 100);
  text("MX:"+mouseX, 100, 100);
  text("MY:"+mouseY, 100, 150);
  VX = map(mouseX, 0, A, -100, 100);
  text("VX:"+int(VX), 100, 200);
  VY = map(mouseY, 0, H, 100, -100);
  text("VY:"+int(VY), 100, 250);
}

void mouseReleased() {
  println("Enviar");
}