node-kbstroke
=============

c++ addon for nodejs

This detects keyboard strokes and mouse movement

(Windows Only,
sorry linux,
untested on mac)

```js
var kbstroke = require("kbstroke");

kbstroke.on("keydown",function(key,numLock,capsLock,scrollLock){
    console.log("keydown",arguments);
});
kbstroke.on("keyup",function(key,numLock,capsLock,scrollLock){
    console.log("keyup",arguments);
    if(key == 27){//esc
      kbstroke.disable();  
    }
});
kbstroke.on("mousemove",function(pos){
    console.log(pos)
});
kbstroke.enable();
```

works with node webkit:
https://github.com/rogerwang/node-webkit/wiki/Build-native-modules-with-nw-gyp

Copyright 2013 Bradley Matusiak
