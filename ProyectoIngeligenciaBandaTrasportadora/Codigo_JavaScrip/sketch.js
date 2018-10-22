
// A function to be called when the model has been loaded
function modelLoaded() {
  select('#loading').html('Modelo cargado neurona lista');
  console.log("Modelo Cargado");
//knn.load('test.json', updateExampleCounts); //AQUI PONER EL MODELO DESCARGADO EN LA PAGINA WEB,LA GUARDAMOS EN ESTA CARPETA Y DESCOMENTAMOS ESTALINEA PARA QUE SE EJECUTE
  //CARGA EL MODELO ANTERIOR.
}


let knn;
let video;
var client;
const myTopic = "itx/entrada";

function setup() {
  console.log("iniciando programa");
  noCanvas();
  video = createCapture(VIDEO).parent('videoContainer');
  // Create a KNN Image Classifier
  knn = new ml5.KNNImageClassifier(2, 1, modelLoaded, video.elt);
  client = new Paho.Client("broker.hivemq.com", 8000,"clientId-zPq1iZ3WW3");
  // set callback handlers
  client.onConnectionLost = onConnectionLost;
  client.onMessageArrived = onMessageArrived;
  // connect the client
  client.connect({onSuccess:onConnect});


  createButtons();
}

// called when the client connects
function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("onConnect con Mqtt");
  client.subscribe(myTopic);
  var message = new Paho.MQTT.Message("vacio prueva");
  message.destinationName = topic;
  client.send(message);
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
  console.log("enviando mensaje" + msg);
  let message = new Paho.Message(msg);
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

//
//mqtt



// called when the client connects
function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("onConnect");
  client.subscribe("World");
  message = new Paho.Message("vacio");
  message.destinationName = "itx/entrada";
  client.send(message);
}

// called when the client loses its connection
function onConnectionLost(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:"+responseObject.errorMessage);
  }
}

// called when a message arrives
function onMessageArrived(message) {
  console.log("onMessageArrived:"+message.payloadString);
}
