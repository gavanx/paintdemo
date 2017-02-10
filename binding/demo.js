var demo = require('./demo.node')

var c = document.getElementById('canvas')
var cbg = document.getElementById('canvas_bg')

function rect(c) {
    var ctx = c.getContext("2d");
    ctx.fillStyle = "green";
    ctx.fillRect(10, 10, 500, 500);
}

rect(cbg)

function copy(c) {
    var ctx = c.getContext("2d");
    var imgData = ctx.getImageData(10, 10, 20, 20);
    console.log('imgData', imgData)
    ctx.putImageData(imgData, 10, 70);
}

copy(cbg)

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

put(cbg)

demo.demo(function (data, x, y, size) {
    console.log('xxxxxxxxxx', x, y, size)
    console.log('data', data)
    var ctx = c.getContext("2d");
    var imgData = ctx.createImageData(size, size);
    console.log('createimagedata', imgData)
    for (var i = 0; i < data.length; i+=4) {
        imgData.data[i + 0] = data[i + 0]
        imgData.data[i + 1] = data[i + 1]
        imgData.data[i + 2] = data[i + 2]
        imgData.data[i + 3] = data[i + 3]
        if(imgData.data[i] === 255 && imgData.data[i + 1] === 255 &&imgData.data[i + 2] === 255){
            // console.log('xxxxxx')
            // imgData.data[i + 3] = 0
        }
        // imgData.data[i + 3] = 220;
    }
    ctx.putImageData(imgData, x, y);
})