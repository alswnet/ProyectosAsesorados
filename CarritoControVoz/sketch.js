// Daniel Shiffman
// http://codingtra.in
// http://patreon.com/codingtrain
// Code for: https://youtu.be/q_bXBcmfTJM

function setup() {
  noCanvas();
  let lang = navigator.language || 'en-US';
  let RECONOCIMIENTO = new p5.SpeechRec(lang, gotSpeech);

  let interim = true;
  let continuous = true;
  RECONOCIMIENTO.start(continuous, interim);

  function gotSpeech() {
    if (RECONOCIMIENTO.resultValue) {
      var palabra=RECONOCIMIENTO.resultString.split(' ').pop();
      if(palabra.indexOf("parquearse")!== -1){
        console.log("parquear el carrito");
      }
      if(palabra.indexOf("adelantar")!== -1){
        console.log("adelantarr");
      }
      if(palabra.indexOf("retroceder")!== -1){
        console.log("retroceder");
      }
      createP(RECONOCIMIENTO.resultString);
    }
  }
}
