
var addon = require("./index.js");

addon.on("keydown",function(key,numLock,capsLock,scrollLock){
    console.log("keydown",arguments);
});
addon.on("keyup",function(key,numLock,capsLock,scrollLock){
    console.log("keyup",arguments);
    if(key == 27){//esc
      addon.disable();  
    }
});
addon.enable();
