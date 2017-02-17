

var c = '74, 144, 226'
var a = c.split(', ').map(function (i) {
    return (parseInt(i) / 255).toFixed(4)
})
console.log(a)