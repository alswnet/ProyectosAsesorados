// A function to be called when the model has been loaded
function modelLoaded() {
  select('#loading').html('Modelo cargado neurona lista');
  //knn.load('KNN-preload.json', updateExampleCounts); //AQUI PONER EL MODELO DESCARGADO EN LA PAGINA WEB,LA GUARDAMOS EN ESTA CARPETA Y DESCOMENTAMOS ESTALINEA PARA QUE SE EJECUTE
  //CARGA EL MODELO ANTERIOR.
}

const client = new Paho.MQTT.Client("ws://iot.eclipse.org/ws", "myClientId" + new Date().getTime());
const myTopic = "itx/entrada";
client.onConnectionLost = onConnectionLost;


function onConnect() {
  console.log("onConnect");
  client.subscribe(myTopic);
}

function onConnectionLost(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:" + responseObject.errorMessage);
  }
  client.connect({
    onSuccess: onConnect
  });
}

let knn;
let video;
client.connect({
  onSuccess: onConnect
});

function setup() {
  noCanvas();
  video = createCapture(VIDEO).parent('videoContainer');
  // Create a KNN Image Classifier
  knn = new ml5.KNNImageClassifier(2, 1, modelLoaded, video.elt);
  createButtons();
}

function createButtons() {
  // Save and Load buttons
  save = select('#save');
  save.mousePressed(() => {
    knn.save('test');
  });


  // Train buttons
  Botonvidrio = select('#Botonvidrio');
  Botonvidrio.mousePressed(function() {
    knn.addImageFromVideo(1);
    updateExampleCounts();
  });


  // Reset buttons
  resetvidrio = select('#Resetvidrio');
  resetvidrio.mousePressed(function() {
    knn.clearClass(1);
    updateExampleCounts();
  });

  // Train buttons
  Botonplastico = select('#Botonplastico');
  Botonplastico.mousePressed(function() {
    knn.addImageFromVideo(2);
    updateExampleCounts();
  });


  // Reset buttons
  resetplastico = select('#Resetplastico');
  resetplastico.mousePressed(function() {
    knn.clearClass(2);
    updateExampleCounts();
  });

  // Train buttons
  Botonlata = select('#Botonlata');
  Botonlata.mousePressed(function() {
    knn.addImageFromVideo(3);
    updateExampleCounts();
  });


  // Reset buttons
  resetlata = select('#Resetlata');
  resetlata.mousePressed(function() {
    knn.clearClass(3);
    updateExampleCounts();
  });

  // Train buttons
  Botonvacio = select('#Botonvacio');
  Botonvacio.mousePressed(function() {
    knn.addImageFromVideo(4);
    updateExampleCounts();
  });


  // Reset buttons
  resetvacio = select('#Resetvacio');
  resetvacio.mousePressed(function() {
    knn.clearClass(4);
    updateExampleCounts();
  });

  // Predict Button
  buttonPredict = select('#buttonPredict');
  buttonPredict.mousePressed(predict);
}



// Train the Classifier on a frame from the video.
function train(category) {
  let msg;
  if (category == 1) {
    msg = 'A';
  } else if (category == 2) {
    msg = 'B';
  }
  select('#training').html(msg);
  knn.addImageFromVideo(category);
  updateExampleCounts();
}

// Predict the current frame.
function predict() {
  knn.predictFromVideo(gotResults);
}

// Show the results
function gotResults(results) {
  let msg;

  if (results.classIndex == 1) {
    msg = 'vidrio';

  } else if (results.classIndex == 2) {
    msg = 'plastico';
  } else if (results.classIndex == 3) {
    msg = 'lata';
  } else if (results.classIndex == 4) {
    msg = 'vacio';
  }
  let message = new Paho.MQTT.Message(msg);
  message.destinationName = myTopic;
  client.send(message);



  select('#result').html(msg);

  // Update confidence
  select('#Confianzavidrio').html(results.confidences[1]);
  select('#Confianzaplastico').html(results.confidences[2]);
  select('#Confianzalata').html(results.confidences[3]);
  select('#Confianzavacio').html(results.confidences[4]);

  setTimeout(function() {
    predict();
  }, 50);
}

// Clear the data in one class
function clearClass(classIndex) {
  knn.clearClass(classIndex);
}

// Update the example count for each class
function updateExampleCounts() {
  let counts = knn.getClassExampleCount();
  select('#Cantidadvidrio').html(counts[1]);
  select('#Cantidadplastico').html(counts[2]);
  select('#Cantidadlata').html(counts[3]);
  select('#Cantidadvacio').html(counts[4]);

}
