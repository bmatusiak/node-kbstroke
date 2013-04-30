node-kbstroke
=============

This detects window keyboard strokes

``` js

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
kbstroke.enable();

```

Copyright 2013 Bradley Matusiak