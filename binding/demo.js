var demo = require('./demo.node')

var cf = document.getElementById('canvas')
var cbg = document.getElementById('canvas_bg')

function rect(c) {
    var ctx = c.getContext("2d");
    ctx.fillStyle = "#F5F5F5";
    ctx.fillStyle = 'white'
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

// rect(cf)
// copy(cf)
// put(cf)

var btn = document.getElementById('btn')
btn.onclick = function () {
    console.log('btn')
    var image = cf.toDataURL("image/png").replace("image/png", "image/octet-stream");
    window.location.href=image; // it will save locally
}

demo.demo(function (data, x, y, size) {
    // if(true)return
    console.log('xxxxxxxxxx', x, y, size)
    console.log('data', data)
    var ctx = cf.getContext("2d");
    var imgData = ctx.createImageData(size, size);
    // var imgData = ctx.getImageData(x, y, size, size);
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