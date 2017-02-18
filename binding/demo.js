var demo = require('./brush.node')

var cf = document.getElementById('canvas')
var cbg = document.getElementById('canvas_bg')
var s = 1
cf.width = 1024 * s
cf.height = 768 * s

function rect(c) {
  var ctx = c.getContext("2d");
  ctx.fillStyle = "#F5F5F5";
  // ctx.fillStyle = 'white'
  ctx.fillRect(10, 10, 800, 800);
}

rect(cbg)

function copy(c) {
  var ctx = c.getContext("2d");
  var imgData = ctx.getImageData(10, 10, 20, 20);
  console.log('imgData', imgData)
  ctx.putImageData(imgData, 10, 70);
}

copy(cbg)

function put(c) {
  var ctx = c.getContext("2d");
  var imgData = ctx.createImageData(300, 300);
  for (var i = 0; i < imgData.data.length; i += 4) {
    imgData.data[i + 0] = 255;
    imgData.data[i + 1] = 0;
    imgData.data[i + 2] = 0;
    imgData.data[i + 3] = 255;
  }
  ctx.putImageData(imgData, 10, 100);
}

// put(cbg)

function draw(c) {
  var ctx = c.getContext("2d");
  ctx.arc(500, 500, 100, 0, 180);
  ctx.strokeText('abc', 700, 200);
}
draw(cbg)

// rect(cf)
// copy(cf)
// put(cf)
// draw(cf)

var btn = document.getElementById('btn_save')
btn.onclick = function() {
  console.log('btn_save')
  var image = cf.toDataURL("image/png").replace("image/png", "image/octet-stream");
  window.location.href = image; // it will save locally
}
btn = document.getElementById('btn_demo')
btn.onclick = function() {
  demo.demo(function(data, x, y, size) {
    var ctx = cf.getContext("2d")
    putData(ctx, data, x, y, size)
  })
}
btn = document.getElementById('btn_brush')
btn.onclick = function() {
  BrushLib.stroke()
}

var BrushLib = require('../brush/BrushLib')
BrushLib.init()


// var _canvas = new fabric.Canvas(cf, {
//     isDrawingMode: true,
//     selection: false,
//     skipTargetFind: true,
//     width: cf.width,
//     height: cf.height,
//     // backgroundColor: this._options.backgroundColor,
//     // transparentCorners: false
// })
// _canvas.setZoom(cf.width / 1024)


function putData(ctx, data, x, y, size) {
  // if(true)return
  console.log('xxxxxxxxxx', x, y, size)
  console.log('data', data)
  var imgData = ctx.createImageData(size, size);
  // var imgData = ctx.getImageData(x, y, size, size);
  console.log('createimagedata', imgData)
  for (var i = 0; i < data.length; i += 4) {
    imgData.data[i + 0] = data[i + 0]
    imgData.data[i + 1] = data[i + 1]
    imgData.data[i + 2] = data[i + 2]
    imgData.data[i + 3] = data[i + 3]
  }
  // ctx.putImageData(imgData, 0, 0, x * s, y * s, size * s, size * s);
  // ctx.putImageData(imgData, x, y)

  var c = document.createElement('canvas')
  c.width = size
  c.height = size
  c.getContext('2d').putImageData(imgData, 0, 0)
  var img = new Image()
  img.onload = function() {
    console.log('xxxxxx img onload', x, y)
    ctx.scale(s, s)
    ctx.drawImage(img, x, y)
    ctx.scale(1 / s, 1 / s)
  }
  img.src = c.toDataURL()
}