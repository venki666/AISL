// UUID
const SERVICE_UUID = "d5875408-fa51-4763-a75d-7d33cecebc31";
const RX_CHARACTERISTIC_UUID = "a4f01d8c-a037-43b6-9050-1876a8c23584";
const TX_CHARACTERISTIC_UUID = "a4f01d8c-a037-43b6-9050-1876a8c23584";

// Characteristic
let txCharacteristic;
let rxCharacteristic;

let searchButton;
let readButton;

let loading;

function init() {
  searchButton = document.querySelector("#search-button");
  searchButton.addEventListener("click", searchBLE);
}

// search & connect
function searchBLE() {

  // acceptAllDevicesの場合optionalServicesが必要みたい
  navigator.bluetooth.requestDevice({
    optionalServices:[SERVICE_UUID],
    acceptAllDevices:true
  })

    .then(device => { 
      console.log("devicename:" + device.name);
      console.log("id:" + device.id);

      // 選択したデバイスに接続
      return device.gatt.connect();
    })

    .then(server => {
      console.log("success:connect to device");

      // UUIDに合致するサービス(機能)を取得
      return server.getPrimaryService(SERVICE_UUID);
    })

    .then(service => {
      console.log("success:service");
      // UUIDに合致するキャラクタリスティック(サービスが扱うデータ)を取得
      // 配列で複数のキャラクタリスティックの取得が可能
      return Promise.all([
        service.getCharacteristic(RX_CHARACTERISTIC_UUID),
        service.getCharacteristic(TX_CHARACTERISTIC_UUID)
      ]);

    })
    .then(characteristic => {
      console.log("success:txcharacteristic");

      rxCharacteristic = characteristic[0];
      txCharacteristic = characteristic[1];

      console.log("success:connect BLE");      
      loading.className = "hide";
    })

    .catch(error => {
      console.log("Error : " + error);

      // loading非表示
      loading.className = "hide";
    });
}

//グローバル変数に変更した
let message;

function readValueBLE() {
  let message;

  try {
    rxCharacteristic.readValue()
      .then(value => {
        message = value.buffer;
        console.log(new Uint8Array(message));
        var value　=　new TextDecoder("utf-8").decode(message)
        var num = parseInt(value, 10);
        console.log(num);
        document.getElementById("data-form").value = new TextDecoder("utf-8").decode(message);
      });
  }
  catch (e) {
    console.log(e);
  }
}

function writeValueBLE() {
  var form_d = document.getElementById("data-form").value;
  var ary_u8 = new Uint8Array( new TextEncoder("utf-8").encode(form_d) );
  console.log(ary_u8);
  try {
    txCharacteristic.writeValue(ary_u8);
  }
  catch (e) {
    console.log(e);
  }
}

window.addEventListener("load", init);

window.onload = function(){
  var dps = []; //dataPoints
  var chart = new CanvasJS.Chart("chartContainer", {
    width: 450,
    height: 350,
    axisY:{
          includeZero: true
    },
    data:[{
      type: "line",
      dataPoints: dps,
    }]
  });


  var xVal = 0;
  var yVal = 255;
  //下記は2000[ms](2秒)ごとにグラフを更新するように変数を指定。
  //ESP32からも2秒ごとにデータを送信するようにしているので、intervalの時間を合わせておくとわかりやすい。
  var updateInterval = 2000; 
  var dataLength = 20;
  var updateChart = function(count){

    try {
      rxCharacteristic.readValue()
        .then(value => {
          message = value.buffer;
          console.log(new Uint8Array(message));
          document.getElementById("data-form").value = new TextDecoder("utf-8").decode(message);
        });
    }
    catch (e) {
      console.log(e);
    }

    count = count || 1;

    for (var j = 0; j < count; j++) {

      //ESP32からBLEで送られてきたデータをInt型に変換し、変数にnumに代入//
      var value　=　new TextDecoder("utf-8").decode(message)
      var num = parseInt(value, 10);
      console.log(num);
      ///////////////////////////////////////////////////////////

      yVal = num;
      dps.push({
        x: xVal*2, //intervalが2秒なのでこうした
        y: yVal
      });
      xVal++;
    }

    if (dps.length > dataLength) {
      dps.shift();
    }

    chart.render();
  }

  updateChart(dataLength);
  setInterval(function(){updateChart()}, updateInterval);

}

///////////////////////////////////////////////////////////
var chartColors = {
    red: 'rgb(255, 99, 132)',
    orange: 'rgb(255, 159, 64)',
    yellow: 'rgb(255, 205, 86)',
    green: 'rgb(75, 192, 192)',
    blue: 'rgb(54, 162, 235)',
    purple: 'rgb(153, 102, 255)',
    grey: 'rgb(201, 203, 207)'
};

function randomScalingFactor() {
    return (Math.random() > 0.5 ? 1.0 : -1.0) * Math.round(Math.random() * 100);
}

function onRefresh(chart) {

  try {
    rxCharacteristic.readValue()
      .then(value => {
        message = value.buffer;
        console.log(new Uint8Array(message));
        document.getElementById("data-form").value = new TextDecoder("utf-8").decode(message);
      });
  }
  catch (e) {
    console.log(e);
  }

  var value　=　new TextDecoder("utf-8").decode(message)
  var num = parseInt(value, 10);
  console.log(num);

    chart.config.data.datasets.forEach(function(dataset) {
        dataset.data.push({
      x: Date.now(),
      y: num //y軸の値はESP32から送られてくるデータ
        });
    });
}

var color = Chart.helpers.color;
var config = {
    type: 'line',
    data: {
        datasets: [{
            label: 'Dataset 1 (linear interpolation)',
            backgroundColor: color(chartColors.red).alpha(0.5).rgbString(),
            borderColor: chartColors.red,
            fill: false,
            lineTension: 0,
            borderDash: [8, 4],
            data: []
        }]
    },
    options: {
        title: {
            display: true,
            text: 'Line chart (hotizontal scroll) sample'
        },
        scales: {
            xAxes: [{
                type: 'realtime',
                realtime: {
                    duration: 20000,
                    refresh: 2000,
                    delay: 2000,
                    onRefresh: onRefresh
                }
            }],
            yAxes: [{
                scaleLabel: {
                    display: true,
                    labelString: 'value'
                }
            }]
        },
        tooltips: {
            mode: 'nearest',
            intersect: false
        },
        hover: {
            mode: 'nearest',
            intersect: false
        }
    }
};

window.onload = function() {
    var ctx = document.getElementById('myChart').getContext('2d');
    window.myChart = new Chart(ctx, config);
};
