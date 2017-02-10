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

demo.demo(function (data, x, y, size) {
    console.log('xxxxxxxxxx', x, y, size)
    console.log('data', data)
    for (var i = 0; i < data.length; i++) {
        // console.log(data[i])
    }
})