var demo = require('./demo.node')

var c = document.getElementById('canvas')
var ctx = c.getContext("2d");
ctx.fillStyle = "green";
ctx.fillRect(10, 10, 50, 50);

function copy() {
    var imgData = ctx.getImageData(10, 10, 20, 20);
    console.log('imgData', imgData)
    ctx.putImageData(imgData, 10, 70);
}

copy()

function put() {
    var ctx = c.getContext("2d");
    var imgData = ctx.createImageData(100, 100);
    for (var i = 0; i < imgData.data.length; i += 4) {
        imgData.data[i + 0] = 255;
        imgData.data[i + 1] = 0;
        imgData.data[i + 2] = 0;
        imgData.data[i + 3] = 255;
    }
    ctx.putImageData(imgData, 10, 100);
}

put()

demo.demo(function (data, x, y, size) {
    console.log('xxxxxxxxxx', x, y, size)
    console.log('data', data)
    var ctx = c.getContext("2d");
    var imgData = ctx.createImageData(size, size);
    console.log('createimagedata', imgData)
    for (var i = 0; i < data.length; i++) {
        imgData.data[i] = data[i]
    }
    ctx.putImageData(imgData, x, y);
})