/**
 * Created by gavan on 17-2-18.
 */

var PaintBrush = require('./mypaint/PaintBrush')

var BrushLib = {
  init: function(surface) {
    PaintBrush.init(surface)
  },

  stroke: function(x, y) {
    PaintBrush.stroke(x, y)
  },

  dispose: function() {
    PaintBrush.dispose()
  }
}

module.exports = BrushLib