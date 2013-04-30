node-kbstroke
=============

``` js
exports.on("keydown",function(key,numLock,capsLock,scrollLock){
    console.log("keydown",arguments);
});
exports.on("keyup",function(key,numLock,capsLock,scrollLock){
    console.log("keyup",arguments);
    if(key == 27){//esc
      exports.disable();  
    }
});
exports.enable();

```