// Copyright 2013 Bradley Matusiak

var events = require('events');

var bindings = require('./build/Release/binding');

exports = module.exports = new events.EventEmitter();

var enabled = false;
var currentKeyMap = [];

bindings.KeyMap(function(err,keymap,numLock,capsLock,scrollLock){
    currentKeyMap = keymap;
});

var checkKeyMap = function (app) {
    if(enabled){
        bindings.KeyMap(function(err,keymap,numLock,capsLock,scrollLock){
            processKeyMap(keymap,numLock,capsLock,scrollLock);
        });
        process.nextTick(checkKeyMap);
    }
};

function processKeyMap(keymap,numLock,capsLock,scrollLock){
    for(var i = 0; i <= 256 ; i++){
        if(keymap[i] === 0 && currentKeyMap[i] === 1){
            exports.emit("keyup",i,numLock,capsLock,scrollLock);
        }
        
        if(keymap[i] === 1 && currentKeyMap[i] === 0){
            exports.emit("keydown",i,numLock,capsLock,scrollLock);
        }
        
        currentKeyMap[i] = keymap[i];
    }
}

exports.enable = function(){
    enabled = true;
};
exports.disable = function(){
    enabled = false;
};

process.nextTick(checkKeyMap);

//tests

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
